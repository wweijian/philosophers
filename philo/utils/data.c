/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:20:32 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/11 22:46:55 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count(t_philosopher *philo)
{
	return (philo->data->count);
}

int	time_to_die(t_philosopher *philo)
{
	return (philo->data->time_to_die);
}

int	time_to_eat(t_philosopher *philo)
{
	return (philo->data->time_to_eat);
}

int	time_to_sleep(t_philosopher *philo)
{
	return (philo->data->time_to_sleep);
}

int	max_eat(t_philosopher *philo)
{
	return (philo->data->max_eat);
}
