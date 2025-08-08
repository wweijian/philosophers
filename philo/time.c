/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:11:39 by weijian           #+#    #+#             */
/*   Updated: 2025/08/08 00:13:01 by weijian          ###   ########.fr       */
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
	return (time_now() - philo->start_time);
}