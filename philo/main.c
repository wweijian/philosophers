/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:28:40 by wjhoe             #+#    #+#             */
/*   Updated: 2025/07/27 11:40:48 by weijian          ###   ########.fr       */
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
	printf(" data.count: %u\n data.time_to_die: %u\n data.time_to_eat: %u\n data.time_to_sleep: %u\n", data.count, data.time_to_die, data.time_to_eat, data.time_to_sleep);
	if (ac == 6)
		printf("data.max_eat: %u\n", data.max_eat);
	if (!init_philosophers(&philo, data.count, &data))
		return (1);
	ph_start_philo(philo, data.count);
	free_philosophers(philo, data.count);
	printf("OPERATION SUCCESS!\n");
}
