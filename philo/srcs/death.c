/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:08:55 by weijian           #+#    #+#             */
/*   Updated: 2025/08/12 10:35:28 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_philosopher *philo, t_state action, int action_time)
{
	if (philo->timer + action_time <= time_to_die(philo) + time_to_die(philo))
	{
		usleep(time_to_die(philo) + philo->last_ate - philo->timer);
		print_state(philo, DEAD);
		lock(&philo->data->mutex.end);
		philo->data->sim_end = 1;
		unlock(&philo->data->mutex.end);
		return (1);
	}
	lock(&philo->data->mutex.end);
	if (philo->data->sim_end == 1)
		return (unlock(&philo->data->mutex.end), 1);
	unlock(&philo->data->mutex.end);
	return (0);
	(void) action; // 
}