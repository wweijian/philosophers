/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:26:17 by weijian           #+#    #+#             */
/*   Updated: 2025/08/07 17:37:07 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_die(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	philo->expected_print = -1;
	usleep(DELAY);
	print_state(philo->timer, philo, DEAD);
	pthread_mutex_lock(&philo->data->death);
	philo->data->philo_died = 1;
	pthread_mutex_unlock(&philo->data->death);
	return (NULL);
}

void	*ph_sleep(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	print_state(philo->timer, philo, SLEEPING);
	if (!update_timer(philo, SLEEPING, philo->data->time_to_sleep))
		return (ph_die(philo));
	if (check_death(philo))
		return (NULL);
	ph_think(philo);
	return (NULL);
}

void	*ph_think(void *data)
{
	t_philosopher	*philo;
	long			think_time;

	philo = (t_philosopher *)data;
	think_time = count_think_time(philo);
	if (think_time == 0)
		return (ph_eat(philo));
	print_state(philo->timer, philo, THINKING);
	if (!update_timer(philo, THINKING, think_time))
		return (ph_die(philo));
	if (check_death(philo))
		return (NULL);
	ph_eat(philo);
	return (NULL);
}

void	*ph_eat(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if (philo->data->max_eat > 0 && philo->times_eaten == philo->data->max_eat)
		return (philo->expected_print = -1, NULL);
	if (pthread_mutex_lock(&philo->fork.left) > 0
		|| pthread_mutex_lock(philo->fork.right) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRMUT), NULL);
	print_state(philo->timer, philo, TAKE_FORK);
	print_state(philo->timer, philo, EATING);
	philo->times_eaten++;
	if (!update_timer(philo, EATING, philo->data->time_to_eat))
		return (ph_die(philo));
	if (pthread_mutex_unlock(&philo->fork.left) > 0
		|| pthread_mutex_unlock(philo->fork.right) > 0)
		return (philo->data->philo_ended = 1, error_msg(ERRUNMUT), NULL);
	if (check_death(philo))
		return (NULL);
	ph_sleep(philo);
	return (NULL);
}
