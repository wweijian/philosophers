/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:41:01 by weijian           #+#    #+#             */
/*   Updated: 2025/07/27 01:07:14 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	ph->start_time = (long) time.tv_sec * 1000 + (long) time.tv_usec / 1000;	
}