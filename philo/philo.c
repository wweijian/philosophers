/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:27:49 by weijian           #+#    #+#             */
/*   Updated: 2025/07/28 09:51:57 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_individual(t_philosopher *philo)
{
	printf("[%ld ms] philo%d\n", time_now() - philo->start_time, philo->index);
	ph_eat(philo);
	return (NULL);
}

int	ph_start_philo(t_philosopher **philo, int count)
{
	int		i; 

	i = 0;
	printf("COUNT: %d\n", count);
	while(i < count)
	{
		philo[i]->start_time = time_now();
		if (pthread_create(&(philo[i]->thread), NULL, (void *(*)(void *))ph_individual, philo[i]) > 0)
			return (0);
		i++;
	}
	// while (i-- > 0)
		// pthread_join(philo[i]->thread, NULL);
	return (1);
}

// if i can only run 8 threads
// then i must close the threads when i'm done using it
// and open up again
// how do i use join and detach to help me solve that? 

// i think the issue is that the program ends too quickly for the threads to form
