/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:28:30 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/11 22:53:40 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philosophers(t_philosopher **philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		destroy(&philo[i]->fork.left);
		free(philo[i]);
		philo[i] = NULL;
		i++;
	}
}

void	destroy_data_mutexes(t_data *data)
{
	destroy(&data->mutex.end);
	destroy(&data->mutex.print);
	destroy(&data->mutex.start);
}

void	detach_all(t_philosopher **philo, int count)
{
	while (count >= 0)
	{
		pthread_detach(philo[count]->thread);
		count--;
	}
}
