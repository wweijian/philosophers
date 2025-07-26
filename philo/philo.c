/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:27:49 by weijian           #+#    #+#             */
/*   Updated: 2025/07/27 01:19:49 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_individual()
{
	
}

int	ph_start_philo(t_philosopher **philo, t_data *ph)
{
	int		i; 

	i = 0;
	ph->start_time = time_now();
	while(i < ph->count)
	{
		if (pthread_create(philo[i]->thread, NULL, ph_individual, philo[i]))
			return (0);
	}
	return (1);
}