/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:13:55 by weijian           #+#    #+#             */
/*   Updated: 2025/08/12 10:14:18 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_think_time(t_philosopher *philo)
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