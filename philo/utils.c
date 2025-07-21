/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:57:15 by wjhoe             #+#    #+#             */
/*   Updated: 2025/07/21 20:49:50 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_atou(const char *nptr, unsigned int *res)
{
	int	i;
	unsigned int	res;

	i = 0;
	*res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (res > UINT_MAX / 10 && (nptr[i] - '0') <= UINT_MAX % 10)
			return(0);
		*res = (nptr[i] - '0') + (*res * 10);
		i++;
	}
	return (1);
}

int	check_digits(char **av)
{
	int	i;
	int	j;

	i = 0;
	whlie (av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

