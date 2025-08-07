/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:26:17 by weijian           #+#    #+#             */
/*   Updated: 2025/08/08 00:18:54 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_end(t_philosopher *philo, t_end end)
{
	usleep(DELAY);
	lock(&philo->data->end_check);
	if (end == DIE)
		philo->data->philo_died = 1;
	if (end == END)
		philo->data->philo_died = 1;
	unlock(&philo->data->end_check);
	print_state(philo->timer, philo, DEAD);
}

void	ph_sleep(t_philosopher *philo)
{
	print_state(philo->timer, philo, SLEEPING);
	if (!check_individual_death(philo, SLEEPING, philo->data->time_to_sleep))
		return (ph_end(philo, DIE));
	if (check_any_death(philo))
		return ;
	ph_think(philo);
}

void	ph_think(t_philosopher *philo)
{
	long			think_time;

	think_time = count_think_time(philo);
	if (think_time == 0)
		return (ph_eat(philo));
	print_state(philo->timer, philo, THINKING);
	if (!check_individual_death(philo, THINKING, think_time))
		return (ph_end(philo, DIE));
	if (check_any_death(philo))
		return ;
	ph_eat(philo);
}

void	ph_eat(t_philosopher *philo)
{
	if (philo->data->max_eat > 0 && philo->times_eaten == philo->data->max_eat)
		return add_max_eat(philo);
	if (philo->parity == ODD && (lock(&philo->fork.left) > 0 || lock(philo->fork.right) > 0))
		return (ph_end(philo, END), error_msg(ERRMUT), (void) 0);
	if (philo->parity == EVEN && (lock(philo->fork.right) > 0 || lock(&philo->fork.left) > 0))
		return (ph_end(philo, END), error_msg(ERRMUT), (void) 0);
	print_state(philo->timer, philo, TAKE_FORK);
	print_state(philo->timer, philo, EATING);
	philo->times_eaten++;
	if (!check_individual_death(philo, EATING, philo->data->time_to_eat))
		return (ph_end(philo, DIE));
	if (philo->parity == ODD && (unlock(&philo->fork.left) > 0 || unlock(philo->fork.right) > 0))
		return (ph_end(philo, END), error_msg(ERRUNMUT), (void) 0);
	if (philo->parity == EVEN && (unlock(philo->fork.right) > 0 || unlock(&philo->fork.left) > 0))
		return (ph_end(philo, END), error_msg(ERRMUT), (void) 0);
	if (check_any_death(philo))
		return ;
	ph_sleep(philo);
}

void	*ph_thread(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	lock(&philo->data->start);
	unlock(&philo->data->start);
	usleep(DELAY);
	philo->start_time = time_now();
	if (philo->index % 2 == 1)
		ph_eat(philo);
	if (philo->index % 2 == 0)
		ph_think(philo);
	return (NULL);
}