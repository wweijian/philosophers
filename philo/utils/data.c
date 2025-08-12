/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:20:32 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/12 09:52:16 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count(t_philosopher *philo)
{
	return (philo->data->count * 1000);
}

int	time_to_die(t_philosopher *philo)
{
	return (philo->data->time_to_die * 1000);
}

int	time_to_eat(t_philosopher *philo)
{
	return (philo->data->time_to_eat * 1000);
}

int	time_to_sleep(t_philosopher *philo)
{
	return (philo->data->time_to_sleep * 1000);
}

int	max_eat(t_philosopher *philo)
{
	return (philo->data->max_eat * 1000);
}
