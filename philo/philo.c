/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:27:49 by weijian           #+#    #+#             */
/*   Updated: 2025/08/13 14:16:00 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

void	*ph_solo_philo(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	pthread_mutex_lock(&philo->data->start);
	philo->data->start_time = time_now();
	pthread_mutex_unlock(&philo->data->start);
	if (lock(&philo->fork.left) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRMUT), NULL);
	print_state(philo, THINKING, 0);
	print_state(philo, TAKE_FORK, philo->data->time_to_eat);
	philo->timer += philo->data->time_to_die;
	usleep(philo->data->time_to_die * 1000);
	if (unlock(&philo->fork.left) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRUNMUT), NULL);
	ph_end(philo, DIE);
	return (NULL);
}

int	ph_start_philo(t_philosopher **philo, int count, t_data *ph)
{
	int	i;

	i = 0;
	pthread_create(&ph->monitoring, NULL, ph_monitoring, ph);
	if (count == 1)
	{
		if (pthread_create(&(philo[i]->thread), NULL, ph_solo_philo,
				philo[i]) > 0)
			return (0);
		pthread_join(philo[i]->thread, NULL);
		return (1);
	}
	pthread_mutex_lock(&ph->start);
	while (i < count)
	{
		if (pthread_create(&(philo[i]->thread), NULL, ph_thread, philo[i]) > 0)
			return (detach_all(philo, i), 0);
		i++;
	}
	ph->start_time = time_now();
	pthread_mutex_unlock(&ph->start);
	pthread_join(ph->monitoring, NULL);
	return (1);
}
