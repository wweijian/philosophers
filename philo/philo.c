/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:27:49 by weijian           #+#    #+#             */
/*   Updated: 2025/08/02 16:25:41 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	ph_max_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		if (data->ph[i]->times_eaten != data->max_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*ph_monitoring(void *data)
{
	t_data	*ph;

	ph = (t_data *) data;
	printf("[philo.c: ph_monitoring] monitoring started\n");
	while (ph->philo_died == 0 && ph_max_eat(ph))
	usleep(1000000); // wait 1 second
	return (NULL);
}

int	ph_solo_philo(t_philosopher **philo, t_data *ph)
{
	(void) philo;
	(void) ph;
	return (0);
}

int	ph_start_philo(t_philosopher **philo, int count, t_data *ph)
{
	int	i;

	i = 0;
	pthread_create(&ph->monitoring, NULL, ph_monitoring, ph);
	usleep(1000000); // wait 1 second
	if (count == 1)
		return (ph_solo_philo(philo, ph));
	while(i < count)
	{
		if (i % 2 == 1)
			if (pthread_create(&(philo[i]->thread), NULL, ph_eat, philo[i]) > 0)
				return (0);
		if (i % 2 == 0)
			if (pthread_create(&(philo[i]->thread), NULL, ph_think, philo[i]) > 0)
				return (0);
		i++;
	}
	usleep((useconds_t) LONG_MAX);
	ph->philo_died = 1;
	pthread_join(ph->monitoring, NULL);
	return (1);
}

// if i can only run 8 threads
// then i must close the threads when i'm done using it
// and open up again
// how do i use join and detach to help me solve that? 

// i think the issue is that the program ends too quickly for the threads to form
