/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:17:45 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/11 13:37:57 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	make_philo(t_philosopher **philo, int index, t_data *data)
{
	philo[index] = malloc(sizeof(**philo));
	if (philo[index] == NULL)
		return (free_philosophers(philo, index), 0);
	memset(*philo, 0, sizeof(**philo));
	philo[index]->index = index;
	if (pthread_mutex_init(&(philo[index]->fork.left), NULL))
		return (free_philosophers(philo, index), free(philo[index]), 0);
	philo[index]->data = data;
	return (1);
}

int	ph_init_philo(t_philosopher ***philo, t_data *data)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(**philo) * data->count);
	if (!*philo)
		return (0);
	while (i < data->count)
	{
		if (!make_philo(*philo, i, data))
			return (free(philo), 0);
		i++;
	}
	while (i-- > 0)
	{
		if (i == 0 && data->count == 1)
			return ((*philo[i])->fork.right = NULL, 1);
		(*philo)[i]->fork.right = &(*philo)[(i + 1) % data->count]->fork.left;
	}
	return (1);
}
