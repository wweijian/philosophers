/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:39:35 by weijian           #+#    #+#             */
/*   Updated: 2025/07/27 01:07:21 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philosophers(t_philosopher **philo)
{
	int	i;
	
	i = 0;
	while (philo[i])
	{
		pthread_mutex_destroy(philo[i]->fork.left); // mutex destroy frees memory allocated to mutex
		free(philo[i]);
		i++;
	}
}
