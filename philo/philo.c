/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:27:49 by weijian           #+#    #+#             */
/*   Updated: 2025/08/07 03:10:58 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	ph_max_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		if (data->ph[i]->times_eaten != data->max_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*ph_monitoring(void *data)
{
	t_data	*ph;

	ph = (t_data *) data;
	// printf("[philo.c: ph_monitoring] monitoring started\n");
	while (ph->philo_died == 0 && ph_max_eat(ph) == 0 && ph->philo_ended == 0)
		;
	usleep(1000000);
	return (NULL);
}

void	*ph_solo_philo(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if (pthread_mutex_lock(&philo->fork.left) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRMUT), NULL);
	print_state(philo->timer, philo, THINKING);
	print_state(philo->timer, philo, TAKE_FORK);
	philo->timer += philo->data->time_to_die;
	return (ph_die(philo));
}

int	ph_start_philo(t_philosopher **philo, int count, t_data *ph)
{
	int	i;

	i = 0;
	pthread_create(&ph->monitoring, NULL, ph_monitoring, ph);
	usleep(1000000);
	while (i < count)
	{
		if (count == 1)
		{
			if (pthread_create(&(philo[i]->thread), NULL, ph_solo_philo,
					philo[i]) > 0)
				return (0);
		}
		else if (i % 2 == 1)
		{
			if (pthread_create(&(philo[i]->thread), NULL, ph_eat, philo[i]) > 0)
				return (0);
		}
		else if (i % 2 == 0)
		{
			if (pthread_create(&(philo[i]->thread), NULL, ph_think,
					philo[i]) > 0)
				return (0);
		}
		i++;
	}
	pthread_join(ph->monitoring, NULL);
	return (1);
}
