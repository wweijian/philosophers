/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:13:00 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/07 21:14:17 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int lock (pthread_mutex_t *mutex)
{
	return (pthread_mutex_lock(mutex));
}

int unlock (pthread_mutex_t *mutex)
{
	return (pthread_mutex_unlock(mutex));
}

int destroy (pthread_mutex_t *mutex)
{
	return (pthread_mutex_destroy(mutex));
}