/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:26:17 by weijian           #+#    #+#             */
/*   Updated: 2025/08/13 13:42:25 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_end(t_philosopher *philo, t_end end)
{
	usleep(DELAY);
	lock(&philo->data->print);
	if (check_any_death(philo))
		return (unlock(&philo->data->print), (void) 0);
	unlock(&philo->data->print);
	if (end == DIE)
	{
		print_state(philo, DEAD, philo->timer);
		lock(&philo->data->print);
		lock(&philo->data->end_check);
		philo->data->philo_died = 1;
		unlock(&philo->data->print);
		unlock(&philo->data->end_check);
	}
	else
	{
		lock(&philo->data->end_check);
		philo->data->philo_died = 1;
		unlock(&philo->data->end_check);
	}
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
	long	think_time;

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
	if (!take_forks(philo))
		return (ph_end(philo, END));
	print_state(philo, TAKE_FORK, 0);
	print_state(philo, EATING, philo->data->time_to_eat);
	philo->times_eaten++;
	if (!check_individual_death(philo, EATING, philo->data->time_to_eat))
	{
		if ((unlock(philo->fork.right) > 0 || unlock(&philo->fork.left) > 0))
			return (ph_end(philo, END), error_msg(ERRUNMUT), (void) 0);
		return (ph_end(philo, DIE));
	}
	if (!drop_forks(philo))
		return (ph_end(philo, END));
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
