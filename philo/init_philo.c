/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:48:55 by weijian           #+#    #+#             */
/*   Updated: 2025/08/06 16:12:34 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(t_philosopher **philo, int index, t_data *data)
{
	philo[index] = malloc(sizeof(t_philosopher));
	if (!philo[index])
		return (0);
	philo[index]->index = index;
	philo[index]->times_eaten = 0;
	philo[index]->last_ate = 0;
	philo[index]->state = WAITING;
	if (pthread_mutex_init(&(philo[index]->fork.left), NULL))
		return (0);
	philo[index]->data = data;
	return (1);
}

int	init_philosophers(t_philosopher ***philo, int count, t_data *data)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(**philo) * count);
	if (!*philo)
		return (0);
	while (i < count)
	{
		if (!make_philo(*philo, i, data))
			return (0); // need to destroy all the mutexes here
		i++;
	}
	while (i-- > 0)
	{
		if (i == 0 && count == 1)
			return ((*philo[i])->fork.right = NULL, 1);
		(*philo)[i]->fork.right = &(*philo)[(i + 1) % count]->fork.left;
	}
	return (1);
}
