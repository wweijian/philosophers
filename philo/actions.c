/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:26:17 by weijian           #+#    #+#             */
/*   Updated: 2025/08/03 16:40:29 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ph_die(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	print_state(philo->timer, philo, DEAD);
	philo->data->philo_died = 1;
	return (NULL);
}

void *ph_sleep(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	print_state(philo->timer, philo, SLEEPING);
	if (!update_timer(philo, EATING, philo->data->time_to_eat)) // then what if philo ended? 
		return (ph_die(philo)); 
	ph_think(philo);
}

void *ph_think(void *data)
{
	// how should i deal with the thinking? 
	t_philosopher	*philo;

	print_state(philo->timer, philo, THINKING);
	// either i think for extra time, or i wait for extra time
	
}

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