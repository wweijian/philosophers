/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:31:00 by wjhoe             #+#    #+#             */
/*   Updated: 2025/07/21 20:37:12 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// SYS LIBS
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

// STRUCT
typedef struct s_data
{
	unsigned int	philo_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	max_eat;
	int				error;
}	t_data;

// VALIDATE
int		validate_arguments(int ac, char	**av);
int		check_digits(char **av);


// UTILS
int		ft_isdigit(char c);
int		ft_atou(const char *nptr, unsigned int *res);


#endif