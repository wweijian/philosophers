/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:05:48 by weijian           #+#    #+#             */
/*   Updated: 2025/08/11 13:42:23 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_atoi(const char *nptr, int *res)
{
	int	i;

	i = 0;
	*res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (*res > INT_MAX / 10 && (nptr[i] - '0') <= ((char) INT_MAX % 10))
			return (0);
		*res = (nptr[i] - '0') + (*res * 10);
		i++;
	}
	return (1);
}

int	check_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ph_init_data(int ac, char **av, t_data *ph)
{
	ph->sim_end = 0;
	ph->max_eat = 0;
	if (!check_digits(av))
		return (0);
	if (!ft_atoi(av[1], &(ph->count)) || ph->count < 1)
		return (0);
	ph->parity = ph->count % 2;
	if (!ft_atoi(av[2], &(ph->time_to_die)))
		return (0);
	if (!ft_atoi(av[3], &(ph->time_to_eat)))
		return (0);
	if (!ft_atoi(av[4], &(ph->time_to_sleep)))
		return (0);
	if (ac == 6)
	{
		if (!ft_atoi(av[5], &(ph->max_eat)))
			return (0);
	}
	else
		ph->max_eat = -1;
	return (1);
}
