/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:45:33 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/11 13:58:31 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_init_shared_mutexes(t_data *data)
{
	if (init_mutex(&data->mutex.print) > 0)
		return (0);
	if (init_mutex(&data->mutex.end) > 0)
		return (destroy(&data->mutex.print), 0);
	if (init_mutex(&data->mutex.start) > 0)
		return (destroy(&data->mutex.print), destroy(&data->mutex.end), 0);
	return (1);
}
