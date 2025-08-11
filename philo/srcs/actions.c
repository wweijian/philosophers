/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:30:20 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/11 22:50:15 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_start(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	lock(&philo->data->mutex.start);
	unlock(&philo->data->mutex.start);
	printf("thread %d started\n", philo->index);
	// if (philo->index % 2 == 1)
	// 	ph_eat(philo);
	// if (philo->index % 2 == 0)
	// 	ph_think(philo);
	return (NULL);
}
