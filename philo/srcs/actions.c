/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:30:20 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/12 01:11:43 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eat(t_philosopher *philo)
{
	if (philo->times_eaten == philo->data->max_eat && philo->data->max_eat > 0)
		return ; //might want to change how this is implemented
	(lock(&philo->fork.left) && lock(philo->fork.right));
	// print_state(philo, TAKE_FORK);
	// print_state(philo, EATING);
	philo->times_eaten++;
	(unlock(philo->fork.right) && unlock(&philo->fork.left));
	ph_sleep(philo);
}

/*
	there's still a few missing logic for this one:
	what happens if they die while eating?
	what happens when someone dies while they're eating? 
*/

// void	ph_sleep(t_philosopher *philo)
// void	ph_think(t_philosopher *philo)
// void	ph_end(t_philosopher *philo)


void	*ph_start(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	lock(&philo->data->mutex.start);
	unlock(&philo->data->mutex.start);
	usleep(DELAY);
	printf("thread %d started\n", philo->index);
	// if (philo->index % 2 == 1)
	// 	ph_eat(philo);
	// if (philo->index % 2 == 0)
	// 	ph_think(philo);
	return (NULL);
}
