/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:41:01 by weijian           #+#    #+#             */
/*   Updated: 2025/08/03 23:56:03 by weijian          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->print); // if philo die or exit, it should block print
	if (philo->data->philo_died == 1 || philo->data->philo_ended == 1)
		return (pthread_mutex_unlock(&philo->data->print), (void) 0);
	printf("[%5ld ms] philosopher %d ", time, philo->index);
	if (state == WAITING)
		printf("is WAITING\n");
	if (state == EATING)
		printf("is EATING\n");
	if (state == SLEEPING)
		printf("is SLEEPING\n");
	if (state == THINKING)
		printf("is THINKING\n");
	if (state == DEAD)
		printf("is DEAD ):\n");
	if (state == TAKE_FORK)
		printf("has TAKEN A FORK\n");
	pthread_mutex_unlock(&philo->data->print);
}

int	update_timer(t_philosopher *philo, t_state state, long action_time)
{
	// TOCHECK: check if will die, need to verify the = too 
	if (philo->timer + action_time >= philo->last_ate + philo->data->time_to_die)
	{
		usleep((philo->data->time_to_die + philo->last_ate - philo->timer) * 1000);
		philo->timer = philo->data->time_to_die + philo->last_ate;
		return (0);
	}
	usleep(action_time * 1000);
	philo->timer += action_time;
	if (state == EATING)
		philo->last_ate = philo->timer;
	return (1);
}

/* void	update_time_and_sleep(t_philosopher *philo, t_state state)
{
	if (state == EATING)
	{
		philo->last_ate = philo->timer;
		usleep(philo->data->time_to_eat * 1000);
		if (philo->data->time_to_eat > philo->data->time_to_die)
			philo->timer += philo->data->time_to_die - philo->last_ate;
		else
			philo->timer += philo->data->time_to_eat;
		return ;
	}
	if (state == SLEEPING)
	{
		usleep(philo->data->time_to_sleep * 1000);
		philo->timer += philo->data->time_to_sleep;
		return ;
	}
	if (state == THINKING)
	{
		usleep(philo->data->time_to_eat * 1000);
		philo->timer += philo->data->time_to_eat;
		return ;
	}
} */