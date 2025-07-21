/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:31:16 by wjhoe             #+#    #+#             */
/*   Updated: 2025/07/21 20:44:35 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	convert_arguments(int ac, char **av, t_data *ph_data)
{
	if (!check_digits(av))
		return (0);
	if (!ft_atou(av[1], &(ph_data->philo_count)))
		return (0);
	if (!ft_atou(av[2], &(ph_data->time_to_die)))
		return (0);
	if (!ft_atou(av[3], &(ph_data->time_to_eat)))
		return (0);
	if (!ft_atou(av[4], &(ph_data->time_to_sleep)))
		return (0);
	if (ac == 6)
		if (!ft_atou(av[5], &(ph_data->max_eat)))
			return (0);
	return (1);
}
