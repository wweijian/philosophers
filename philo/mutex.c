/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:13:00 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/13 13:13:35 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock(pthread_mutex_t *mutex)
{
	return (pthread_mutex_lock(mutex));
}

int	unlock(pthread_mutex_t *mutex)
{
	return (pthread_mutex_unlock(mutex));
}

int	destroy(pthread_mutex_t *mutex)
{
	return (pthread_mutex_destroy(mutex));
}

int	take_forks(t_philosopher *philo)
{
	if (philo->parity == ODD && (lock(&philo->fork.left) > 0
			|| lock(philo->fork.right) > 0))
		return (error_msg(ERRMUT), 0);
	if (philo->parity == EVEN && (lock(philo->fork.right) > 0
			|| lock(&philo->fork.left) > 0))
		return (error_msg(ERRMUT), 0);
	return (1);
}

int	drop_forks(t_philosopher *philo)
{
	if (philo->parity == ODD && (unlock(philo->fork.right) > 0
			|| unlock(&philo->fork.left) > 0))
		return (error_msg(ERRUNMUT), 0);
	if (philo->parity == EVEN && (unlock(&philo->fork.left) > 0
			|| unlock(philo->fork.right) > 0))
		return (error_msg(ERRUNMUT), 0);
	return (1);
}
