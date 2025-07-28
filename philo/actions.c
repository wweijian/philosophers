/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:26:17 by weijian           #+#    #+#             */
/*   Updated: 2025/07/28 10:08:12 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_sleep(t_philosopher *philo)
{
	long	sleep_time;

	(void) sleep_time;
	(void) philo;
	pthread_detach(philo->thread);
	return (0);
}

int	ph_eat(t_philosopher *philo)
{
	long	eat_time;
	
	if (philo->data->max_eat >= 0 && philo->times_eaten == philo->data->max_eat)
		return (1);
	if (pthread_mutex_lock(&philo->fork.left) || pthread_mutex_lock(philo->fork.right))
		return (philo->data->philo_ended = 1, error_msg(ERRMUT), 0);
	eat_time = time_now();
	philo->data->max_eat++;
	print_state(time_elapsed(eat_time, philo->start_time), philo, EATING);
	printf("eating...");
	usleep(philo->data->time_to_eat * 1000);
	printf("ate\n");
	if (pthread_mutex_unlock(&philo->fork.left) || pthread_mutex_unlock(philo->fork.right))
		return (philo->data->philo_ended = 1, error_msg(ERRUNMUT), 0);
	ph_sleep(philo);
	return (0);
}


// only condition for philosopher to die: not eating in time
// not eating is eat_time - last_eat > time_to_die
// so when does a philo want to eat? it wants to eat when it's done sleeping
// how can i what time its starting to wait