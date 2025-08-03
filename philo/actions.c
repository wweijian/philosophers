/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:26:17 by weijian           #+#    #+#             */
/*   Updated: 2025/08/03 08:01:05 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ph_die(void *data)
{
	t_philosopher	*philo;
	
	philo = (t_philosopher *)data;
	philo->data->philo_died = 1;
	print_state(philo->timer, philo, DEAD);
	return (NULL);
}

void *ph_sleep(void *data)
{
	t_philosopher	*philo;
	
	philo = (t_philosopher *)data;
	print_state(philo->timer, philo, SLEEPING);
	update_time_and_sleep(philo, SLEEPING);
	ph_think(philo);
	return (NULL);
}

void *ph_think(void *data)
{
	t_philosopher	*philo;
	
	philo = (t_philosopher *)data;
	print_state(philo->timer, philo, THINKING);
	update_time_and_sleep(philo, THINKING);
	pthread_detach(philo->thread);
	pthread_create(&philo->thread, NULL, ph_eat, philo); // then maybe i shouldn't try to eat again. here
	return (NULL);
}

void *ph_eat(void *data)
{
	t_philosopher	*philo;
	
	philo = (t_philosopher *)data;
	if (philo->data->max_eat > 0 && philo->times_eaten == philo->data->max_eat)
		return (NULL);
	if (pthread_mutex_lock(&philo->fork.left) > 0 || pthread_mutex_lock(philo->fork.right) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRMUT), NULL);
	print_state(philo->timer, philo, TAKE_FORK);
	print_state(philo->timer, philo, EATING);
	philo->times_eaten++;
	update_time_and_sleep(philo, EATING);
	if (pthread_mutex_unlock(&philo->fork.left) > 0 || pthread_mutex_unlock(philo->fork.right) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRUNMUT), NULL);
	ph_sleep(philo);
	// i should call another eat here for the next guy
	return (0);
}

// only condition for philosopher to die: not eating in time
// not eating is eat_time - last_eat > time_to_die
// so when does a philo want to eat? it wants to eat when it's done sleeping
// how can i what time its starting to wait
// we need to check every time whether an operation can be done
