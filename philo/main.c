/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:28:40 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/12 23:17:09 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	Need to flip the fork unlock order 

	whenever philo exits eat, needs to release forks
*/

int	init_data_mutexes(pthread_mutex_t *start, pthread_mutex_t *print,
						pthread_mutex_t *end_check)
{
	if (pthread_mutex_init(start, NULL) > 0)
		return (0);
	if (pthread_mutex_init(print, NULL) > 0)
		return (destroy(start), 0);
	if (pthread_mutex_init(end_check, NULL) > 0)
		return (destroy(start), destroy(print), 0);
	return (1);
}

void	destroy_data_mutexes(pthread_mutex_t *start, pthread_mutex_t *print,
								pthread_mutex_t *end_check)
{
	destroy(end_check);
	destroy(print);
	destroy(start);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philosopher	**philo;

	if (!(ac == 5 || ac == 6))
		return (1);
	if (av[1][0] == '0' && av[1][1] == 0)
		return (1);
	if (!ph_init_data(ac, av, &data))
		return (1);
	init_data_mutexes(&data.start, &data.print, &data.end_check);
	if (!init_philosophers(&philo, data.count, &data))
		return (1);
	data.ph = philo;
	ph_start_philo(philo, data.count, &data);
	free_philosophers(philo, data.count);
	free(philo);
	printf("\nSIMULATION COMPLETE\n");
	return (0);
}
