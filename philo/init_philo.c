/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:48:55 by weijian           #+#    #+#             */
/*   Updated: 2025/07/26 22:39:45 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(t_data *ph_data, int index)
{
	ph_data->philos[index] = malloc(sizeof(t_philosopher));
	if (!ph_data->philos[index])
		return (0);
	ph_data->philos[index]->index = index;
	ph_data->philos[index]->parity = index % 2;
	ph_data->philos[index]->times_eaten = 0;
	ph_data->philos[index]->last_ate = 0;
	ph_data->philos[index]->last_slept = 0;
	ph_data->philos[index]->state = WAITING;
	ph_data->philos[index]->fork.left = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(ph_data->philos[index]->fork.left, NULL)) //idk if i want to force a recursive
		return (perror("make philo"), 0);
	if (index == 0)
		ph_data->philos[index]->left = ph_data->philos[ph_data->philo_count - 1];
	else
		ph_data->philos[index]->left = ph_data->philos[(index + ph_data->philo_count - 1) % ph_data->philo_count];
	ph_data->philos[index]->right = ph_data->philos[(index + 1) % ph_data->philo_count];
	return (1);
}

int	init_philosophers(t_data *ph_data)
{
	int	i;

	i = 0;
	ph_data->philos = malloc(sizeof(*(ph_data->philos)) * ph_data->philo_count);
	if (!ph_data->philos)
		return (0);
	while (i < ph_data->philo_count)
	{
		if(!make_philo(ph_data, i))
		{
			printf("make philo failed??\n");
			return(0); // need to destroy all the mutexes here
		}
		ph_data->philos[0]->left = ph_data->philos[ph_data->philo_count - 1];
		i++;
	}
	return (1);
}
