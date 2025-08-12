/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:49:00 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/12 10:31:36 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philosopher *philo, t_state state)
{	
	lock(&philo->data->mutex.print);
	printf("%d philo %d ", time_elapsed(philo), philo->index);
	if (state == WAITING)
		printf("is waiting\n");
	if (state == EATING)
		printf("is eating\n");
	if (state == SLEEPING)
		printf("is sleeping\n");
	if (state == THINKING)
		printf("is thinking\n");
	if (state == TAKE_FORK)
		printf("has taken a fork\n");
	unlock(&philo->data->mutex.print);
}
