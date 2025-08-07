/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:28:40 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/07 16:27:06 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (pthread_mutex_init(&data.print, NULL) > 0)
		return (0);
	if (pthread_mutex_init(&data.death, NULL) > 0)
		return (0);
	printf(" data.count: %u\n data.time_to_die: %u\n data.time_to_eat: %u\n data.time_to_sleep: %u\n", data.count, data.time_to_die, data.time_to_eat, data.time_to_sleep);
	if (!init_philosophers(&philo, data.count, &data))
		return (1);
	data.ph = philo;
	ph_start_philo(philo, data.count, &data);
	free_philosophers(philo, data.count);
	printf("\nSIMULATION COMPLETE\n");
}

/*	NOTES:
	 not sure if i accounted for the fact if any of the numbers being 0
	 and how does that matter? 

	 check memleaks as well as any other allocation failures

	 need to check everything for when philo has ended
*/