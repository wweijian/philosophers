/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:26:17 by weijian           #+#    #+#             */
/*   Updated: 2025/08/05 18:57:56 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ph_die(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	usleep(DELAY);
	print_state(philo->timer, philo, DEAD);
	pthread_mutex_lock(&philo->data->death);
	philo->data->philo_died = 1;
	pthread_mutex_unlock(&philo->data->death);
	return (NULL);
}

void *ph_sleep(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	print_state(philo->timer, philo, SLEEPING);
	if (!update_timer(philo, SLEEPING, philo->data->time_to_sleep)) // then what if philo ended? 
		return (ph_die(philo));
	if (check_death(philo))
		return (NULL);
	ph_think(philo);
	return (NULL);
}

/* 
	i should make some chanes to the time for ph_think to account for the following facts: 
		first think should really just be 1 meal time -- after the first eat,
		the thikning philo can just reach for the fork already
	the second think should be waiting for 2 eats ... right??
		yes, cos need to wait for 2 people to eat
		but, should i pick up a fork first? because technically i can
		i dont' have to 
*/

void	*ph_think(void *data)
{
	t_philosopher	*philo;
	long	think_time;

	philo = (t_philosopher *)data;
	think_time = count_think_time(philo);
	if (think_time == 0)
		return (ph_eat(philo));
	print_state(philo->timer, philo, THINKING);
	// printf("philo: %d think time: %ld\n",philo->index, count_think_time(philo));
	if (!update_timer(philo, THINKING, think_time))
		return (ph_die(philo));
	if (check_death(philo))
		return (NULL);
	ph_eat(philo);
	return (NULL);
}

/* if philo die exactly when it eats how? */
void *ph_eat(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if (philo->data->max_eat > 0 && philo->times_eaten == philo->data->max_eat)
		return (NULL); // simulation has to end here anyway
	if (pthread_mutex_lock(&philo->fork.left) > 0 || pthread_mutex_lock(philo->fork.right) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRMUT), NULL);
	print_state(philo->timer, philo, TAKE_FORK);
	print_state(philo->timer, philo, EATING);
	philo->times_eaten++;
	if (!update_timer(philo, EATING, philo->data->time_to_eat))
		return (ph_die(philo)); // need to unlock the mutexes properly 
	if (pthread_mutex_unlock(&philo->fork.left) > 0 || pthread_mutex_unlock(philo->fork.right) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRUNMUT), NULL);
	if (check_death(philo))
		return (NULL);
	ph_sleep(philo);
	return (NULL);
}

// only condition for philosopher to die: not eating in time
// not eating is eat_time - last_eat > time_to_die
// so when does a philo want to eat? it wants to eat when it's done sleeping
// how can i what time its starting to wait
// we need to check every time whether an operation can be done

/* 02.08.25 */
/* 
	it should also include the checks and exit for death end and simul 
	and it should sleep after eating max too 
*/