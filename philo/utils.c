/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:41:01 by weijian           #+#    #+#             */
/*   Updated: 2025/07/29 19:17:56 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((long) time.tv_sec * 1000 + (long) time.tv_usec / 1000);
}

long	time_elapsed(long time, long start)
{
	if (!time)
		return (time_now() - start);
	return (time - start);
}

void	print_state(long time, t_philosopher *philo, t_state state)
{
	pthread_mutex_lock(&philo->data->print);
	printf("[%5ld ms] philosopher %d ", time, philo->index);
	if (state == WAITING)
		return ((void) printf("is WAITING\n"));
	if (state == EATING)
		return ((void) printf("is EATING\n"));
	if (state == SLEEPING)
		return ((void) printf("is SLEEPING\n"));
	if (state == THINKING)
		return ((void) printf("is THINKING\n"));
	if (state == DEAD)
		return ((void) printf("is DEAD ):\n"));
	if (state == TAKE_FORK)
		return ((void) printf("has TAKEN A FORK\n"));
	pthread_mutex_unlock(&philo->data->print);
}

void	update_time_and_sleep(t_philosopher *philo, t_state state)
{
	if (state == SLEEPING)
	{
		usleep(philo->data->time_to_sleep * 1000);
		philo->timer += philo->data->time_to_sleep;
		return ;
	}
	if (state == EATING)
	{
		philo->last_ate = philo->timer;
		usleep(philo->data->time_to_eat * 1000);
		philo->timer += philo->data->time_to_eat;
		return ;
	}
	if (state == THINKING)
	{
		usleep(philo->data->time_to_eat * 1000);
		philo->timer += philo->data->time_to_eat;
		return ;
	}
}