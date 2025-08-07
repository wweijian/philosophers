/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:41:01 by weijian           #+#    #+#             */
/*   Updated: 2025/08/08 00:15:52 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	last_time(long time, int type)
{
	static long	last = 0;

	if (type == 0)
		return (last);
	else
	{
		last = time;
		return (last);
	}
}

void	print_state(long time, t_philosopher *philo, t_state state)
{

	lock(&philo->data->print);
	if (check_any_death(philo))
		return (unlock(&philo->data->print), (void) 0);
	if (time < last_time(0, 0))
		printf("ERROR IN PRINT\n");
	printf("%ld %d ", time, philo->index);
	if (state == WAITING)
		printf("is waiting\n");
	if (state == EATING)
		printf("is eating\n");
	if (state == SLEEPING)
		printf("is sleeping\n");
	if (state == THINKING)
		printf("is thinking\n");
	if (state == TAKE_FORK)
		printf("has taken a fork\n");
	last_time(time, 1);
	unlock(&philo->data->print);
}

void	print_dead(long time, t_philosopher *philo)
{
	lock(&philo->data->print);
	if (check_any_death(philo))
		return (unlock(&philo->data->print), (void) 0);
	printf("%ld %d ", time, philo->index);
	printf("died\n");
	unlock(&philo->data->print);
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
