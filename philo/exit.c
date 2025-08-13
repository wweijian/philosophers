/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:39:35 by weijian           #+#    #+#             */
/*   Updated: 2025/08/13 13:07:18 by wjhoe            ###   ########.fr       */
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

void	detach_all(t_philosopher **philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_detach(philo[i]->thread);
		i++;
	}
}
