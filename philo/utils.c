/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:41:01 by weijian           #+#    #+#             */
/*   Updated: 2025/08/07 03:05:23 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(long time, t_philosopher *philo, t_state state)
{
	static long	last = 0;
	
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->philo_died == 1 || philo->data->philo_ended == 1)
		return (pthread_mutex_unlock(&philo->data->print), (void) 0);
	if (time < last)
		time = last;
	printf("%ld %d ", time, philo->index);
	if (state == WAITING)
		printf("is waiting\n");
	if (state == EATING)
		printf("is eating\n");
	if (state == SLEEPING)
		printf("is sleeping\n");
	if (state == THINKING)
		printf("is thinking\n");
	if (state == DEAD)
		printf("died\n");
	if (state == TAKE_FORK)
		printf("has taken a fork\n");
	last = time;
	pthread_mutex_unlock(&philo->data->print);
}

int	update_timer(t_philosopher *philo, t_state state, long action_time)
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
	if (philo->data->count > 100)
		usleep(DELAY);
	philo->timer += action_time;
	return (1);
}

int	check_death(t_philosopher *philo)
{
	int	death;

	death = 0;
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->philo_died)
		death = 1;
	pthread_mutex_unlock(&philo->data->death);
	return (death);
}

long	count_think_time(t_philosopher *philo)
{
	if (philo->data->parity == EVEN)
	{
		if (philo->times_eaten == 0)
			return (philo->data->time_to_eat);
		else if (philo->data->time_to_eat <= philo->data->time_to_sleep)
			return (0);
		else
			return (philo->data->time_to_eat - philo->data->time_to_sleep);
	}
	else
	{
		if (philo->times_eaten == 0)
		{
			if (philo->index == 0)
				return (philo->data->time_to_eat * 2);
			else
				return (philo->data->time_to_eat);
		}
		else
			return (philo->data->time_to_eat * 2 - philo->data->time_to_sleep);
	}
}
