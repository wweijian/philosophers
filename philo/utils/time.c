/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:24:35 by weijian           #+#    #+#             */
/*   Updated: 2025/08/12 10:30:42 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_now(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((int) time.tv_sec * 1000 + (int) time.tv_usec / 1000);
}

int	time_elapsed(t_philosopher *philo)
{
	return (time_now() - philo->start_time);
}

/* void	add_delay(t_philosopher *philo)
{
	static	int i = 0;;

	if (philo->data->count < 2)
		return ;
	i++;
	lock(&philo->data->mutex.start);
	if (i % (philo->data->count * 3) == 0)
	{
		philo->data->start_time += 2;
		i = 0;
	}
	unlock(&philo->data->mutex.start);
} */