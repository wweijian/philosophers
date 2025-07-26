/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:31:00 by wjhoe             #+#    #+#             */
/*   Updated: 2025/07/27 01:10:00 by weijian          ###   ########.fr       */
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

/* ENUM */
typedef enum s_parity
{
	EVEN,
	ODD
}	t_parity;

typedef enum s_state
{
	WAITING,
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FORK,
	DEAD
}	t_state;

/* STRUCT */

struct	s_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	*left;
	pthread_mutex_t *(*right)(struct s_philosopher *);
} t_fork;

typedef struct s_data
{
	int				count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	max_eat;
	int				philo_died;
	int				philo_ended;
	time_t			start_time;
}	t_data;

typedef struct s_philosopher
{
	unsigned int			index;
	pthread_t				thread;
	t_parity				parity;
	unsigned int			times_eaten;
	unsigned int			last_ate;
	unsigned int			last_slept;
	t_state					state;
	t_fork					fork;
	struct s_philosopher	*left;
	struct s_philosopher	*right;
}	t_philosopher;

/* INITIALIZING */
int		ph_init_data(int ac, char **av, t_data *ph_data);
int		init_philosophers(t_philosopher ***philo, int count);
void	init_data(t_data *ph);

/* CLEAN UP */
void	free_philosophers(t_philosopher **philo);

/* SIMULATION */
// int	ph_start_philo(t_philosopher **philo, t_data *ph);

#endif