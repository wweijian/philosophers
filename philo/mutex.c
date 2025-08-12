/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:13:00 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/12 23:18:19 by weijian          ###   ########.fr       */
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
