/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:11:39 by weijian           #+#    #+#             */
/*   Updated: 2025/08/12 23:18:04 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long) time.tv_sec * 1000 + (long) time.tv_usec / 1000);
}

long	time_elapsed(t_philosopher *philo)
{
	long	res;

	lock(&philo->data->start);
	res = time_now() - philo->data->start_time;
	unlock(&philo->data->start);
	return (res);
}

/* void	add_delay(t_philosopher *philo)
{
	static int	i = 0;

	if (philo->data->count < 2)
		return ;
	i++;
	lock(&philo->data->start);
	if (i % (philo->data->count * 3) == 0)
	{
		philo->data->start_time += 2;
		i = 0;
	}
	unlock(&philo->data->start);
} */