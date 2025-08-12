/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:16:02 by weijian           #+#    #+#             */
/*   Updated: 2025/08/12 11:30:36 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data			data;
	t_philosopher	**philo;
	
	if (ac != 5 && ac != 6)
		return (1);
	if (!ph_init_data(ac, av, &data) || !ph_init_shared_mutexes(&data)
		|| !ph_init_philo(&philo, &data))
		return (1);
	printf("\n------\ndata.count: %u\ndata.time_to_die: %u\ndata.time_to_eat: %u\ndata.time_to_sleep: %u\ndata.max_eat: %d\n", data.count, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.max_eat);
	puts("------\n");
	data.philo = philo;
	start_philo(philo, &data);
	puts("[start philo]");
	free_philosophers(philo, data.count);
}
