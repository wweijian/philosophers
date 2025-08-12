/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:30:20 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/12 11:25:21 by weijian          ###   ########.fr       */
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
	usleep(time_to_eat(philo));
	philo->timer += time_to_eat(philo);
	(unlock(philo->fork.right) && unlock(&philo->fork.left));
	ph_sleep(philo);
}

/*
	there's still a few missing logic for this one:
	what happens if they die while eating?
	what happens when someone dies while they're eating? 
*/

void	ph_sleep(t_philosopher *philo)
{
	// print_state(philo, SLEEPING);
	if (check_death(philo, SLEEPING, time_to_sleep(philo)))
		return ;
	usleep(time_to_sleep(philo));
	philo->timer += time_to_sleep(philo);
	ph_think(philo);
}

void	ph_think(t_philosopher *philo)
{
	int	think_time;

	think_time = count_think_time(philo);
	if (think_time == 0)
		return (ph_eat(philo));
	// print_state(philo, THINKING);
	if (!check_death(philo, THINKING, think_time))
		return ;
	ph_eat(philo);
}

void	ph_test(t_philosopher *philo)
{
	printf("[srcs/actions.c : ph_test] philo %d\n", philo->index);
}

void	*ph_start(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	lock(&philo->data->mutex.start);
	philo->start_time = philo->data->start_time;
	unlock(&philo->data->mutex.start);
	usleep(DELAY);
	printf("thread %d started\n", philo->index);
	if (philo->index % 2 == 1)
		ph_test(philo);
		// ph_eat(philo);
	if (philo->index % 2 == 0)
		ph_test(philo);
		// ph_think(philo);
	return (NULL);
}
