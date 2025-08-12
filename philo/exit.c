/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:39:35 by weijian           #+#    #+#             */
/*   Updated: 2025/08/12 23:14:57 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philosophers(t_philosopher **philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philo[i]->fork.left);
		free(philo[i]);
		i++;
	}
}

void	error_msg(char *message)
{
	printf("%s\n", message);
}
