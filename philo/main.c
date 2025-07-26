/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:28:40 by wjhoe             #+#    #+#             */
/*   Updated: 2025/07/26 22:41:30 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	ph;

	if (!(ac == 5 || ac == 6))
		return (1);
	if (av[1][0] == '0' && av[1][1] == 0)
		return (1);
	if (!convert_arguments(ac, av, &ph))
		return (1);
	printf(" ph.philo_count: %u\n ph.time_to_die: %u\n ph.time_to_eat: %u\n ph.time_to_sleep: %u\n", ph.philo_count, ph.time_to_die, ph.time_to_eat, ph.time_to_sleep);
	if (ac == 6)
		printf("ph.max_eat: %u\n", ph.max_eat);
	if (!init_philosophers(&ph))
		return (1);
	printf("conversion SUCCESS!\n");
}
