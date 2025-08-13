/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:39:00 by weijian           #+#    #+#             */
/*   Updated: 2025/08/13 13:00:38 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_max_eat(t_data *ph)
{
	if (ph->max_eat_count == ph->count)
		return (1);
	return (0);
}

void	*ph_monitoring(void *data)
{
	t_data			*ph;
	unsigned int	i;

	i = 0;
	ph = (t_data *) data;
	while (1)
	{
		lock(&ph->end_check);
		if (ph->philo_died == 1 || ph_max_eat(ph) == 1 || ph->philo_ended == 1)
			break ;
		unlock(&ph->end_check);
	}
	unlock(&ph->end_check);
	usleep(1000000);
	while (i < ph->count)
	{
		pthread_join(ph->ph[i]->thread, NULL);
		i++;
	}
	return (NULL);
}

int	check_any_death(t_philosopher *philo)
{
	int	death;

	death = 0;
	lock(&philo->data->end_check);
	if (philo->data->philo_ended || philo->data->philo_died)
		death = 1;
	unlock(&philo->data->end_check);
	return (death);
}

int	check_individual_death(t_philosopher *philo, t_state state,
							long action_time)
{
	if (state == EATING)
		philo->last_ate = philo->timer;
	if (philo->timer + action_time > philo->last_ate + philo->data->time_to_die)
	{
		usleep((philo->data->time_to_die + philo->last_ate - philo->timer)
			* 1000);
		philo->timer = philo->data->time_to_die + philo->last_ate;
		return (0);
	}
	usleep(action_time * 1000);
	philo->timer += action_time;
	return (1);
}

void	add_max_eat(t_philosopher *philo)
{
	lock(&philo->data->end_check);
	philo->data->max_eat_count++;
	unlock(&philo->data->end_check);
}
