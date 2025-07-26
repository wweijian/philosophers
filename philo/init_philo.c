/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:48:55 by weijian           #+#    #+#             */
/*   Updated: 2025/07/27 01:03:24 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(t_philosopher **philo, int index, int count)
{
	philo[index] = malloc(sizeof(t_philosopher));
	if (!philo[index])
		return (0);
	philo[index]->index = index;
	philo[index]->parity = index % 2;
	philo[index]->times_eaten = 0;
	philo[index]->last_ate = 0;
	philo[index]->last_slept = 0;
	philo[index]->state = WAITING;
	philo[index]->fork.left = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(philo[index]->fork.left, NULL)) //idk if i want to force a recursive
		return (0);
	if (index == 0)
		philo[index]->left = philo[count - 1];
	else
		philo[index]->left = philo[(index + count - 1) % count];
	philo[index]->right = philo[(index + 1) % count];
	return (1);
}

int	init_philosophers(t_philosopher ***philo, int count)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(**philo) * count);
	if (!*philo)
		return (0);
	while (i < count)
	{
		if(!make_philo(*philo, i, count))
			return(0); // need to destroy all the mutexes here
		(*philo)[0]->left = (*philo)[count - 1];
		i++;
	} 
	return (1);
}
