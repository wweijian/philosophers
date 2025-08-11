/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:16:02 by weijian           #+#    #+#             */
/*   Updated: 2025/08/11 10:32:10 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	t_data			data;
	t_philosopher	**philo;

	if (ac != 5 && ac != 6)
		return (1);
	if (!ph_init_data(ac, av, &data) || )
		return (1);
	
}