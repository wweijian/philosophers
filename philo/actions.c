/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:26:17 by weijian           #+#    #+#             */
/*   Updated: 2025/08/12 23:38:04 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
		actions:
		print
		check time (die or no die)
		sleep and increment time
*/

void	ph_end(t_philosopher *philo, t_end end)
{
	usleep(DELAY);
	lock(&philo->data->print);
	if (check_any_death(philo))
		return (unlock(&philo->data->print), (void) 0);
	lock(&philo->data->end_check);
	if (end == DIE)
	{
		printf("%ld %d died\n", philo->timer, philo->index);
		philo->data->philo_died = 1;
	}
	else
		philo->data->philo_died = 1;
	unlock(&philo->data->end_check);
	unlock(&philo->data->print);
}

void	ph_sleep(t_philosopher *philo)
{
	print_state(philo, SLEEPING, philo->data->time_to_sleep);
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
	print_state(philo, THINKING, think_time);
	if (!check_individual_death(philo, THINKING, think_time))
		return (ph_end(philo, DIE));
	if (check_any_death(philo))
		return ;
	ph_eat(philo);
}

void	ph_eat(t_philosopher *philo)
{
	if (philo->data->max_eat > 0 && philo->times_eaten == philo->data->max_eat)
		return (add_max_eat(philo));
	if ((lock(&philo->fork.left) > 0 || lock(philo->fork.right) > 0))
		return (ph_end(philo, END), error_msg(ERRMUT), (void) 0);
	print_state(philo, TAKE_FORK, 0);
	print_state(philo, EATING, philo->data->time_to_eat);
	philo->times_eaten++;
	if (!check_individual_death(philo, EATING, philo->data->time_to_eat))
	{
		if ((unlock(philo->fork.right) > 0 || unlock(&philo->fork.left) > 0))
			return (ph_end(philo, END), error_msg(ERRUNMUT), (void) 0);
		return (ph_end(philo, DIE));
	}
	if ((unlock(philo->fork.right) > 0 || unlock(&philo->fork.left) > 0))
		return (ph_end(philo, END), error_msg(ERRUNMUT), (void) 0);
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
	if (philo->index % 2 == 1)
		ph_eat(philo);
	if (philo->index % 2 == 0)
		ph_think(philo);
	return (NULL);
}
