/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:17:37 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/12 11:26:46 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	What's the actual point of having the monitoring script? is it just to
	stop the thread from finishing? 
*/

void	*ph_monitoring(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *) arg;
	while (1)
	{
		lock(&data->mutex.end);
		if (data->sim_end)
			break ;
		unlock(&data->mutex.end);
	}
	unlock(&data->mutex.end);
	while (i < data->count)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
	return (NULL);
}

void	start_philo(t_philosopher **philo, t_data *data)
{
	int			i;
	pthread_t	monitoring;

	i = 0;
	pthread_create(&monitoring, NULL, ph_monitoring, data);
	lock(&data->mutex.start);
	while (i < data->count)
	{
		if (pthread_create(&(philo[i]->thread), NULL, ph_start, philo[i]) > 0)
			return (detach_all(philo, i));
		i++;
	}
	data->start_time = time_now();
	unlock(&data->mutex.start);
	pthread_join(monitoring, NULL);
}
