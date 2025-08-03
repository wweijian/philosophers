/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:31:00 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/03 10:45:23 by weijian          ###   ########.fr       */
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

/* ERROR MESSAGES */
# define ERRMUT "mutex failed to be locked"
# define ERRUNMUT "mutex failed to be unlocked"
# define ERRMEM "malloc failed"

/* DEFINE DELAY */
# define DELAY 1000000

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

struct s_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	left;
	pthread_mutex_t *right;
}	t_fork;

typedef struct s_data
{
	int						count;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	unsigned int			max_eat;
	long					philo_died;
	int						philo_ended;
	t_parity				parity;
	pthread_mutex_t			print;
	pthread_t				monitoring;
	struct s_philosopher	**ph;
}	t_data;

typedef struct s_philosopher
{
	unsigned int	index;
	pthread_t		thread;
	time_t			timer;
	t_data			*data;
	unsigned int	times_eaten;
	unsigned int	last_ate;
	t_state			state;
	t_fork			fork;
}	t_philosopher;

/* INITIALIZING */
int		ph_init_data(int ac, char **av, t_data *ph_data);
int		init_philosophers(t_philosopher ***philo, int count, t_data *data);
void	init_data(t_data *ph);

/* CLEAN UP */
void	free_philosophers(t_philosopher **philo, int count);
void	error_msg(char *message);

/* SIMULATION */
void	ph_monitoring_thread(t_data *ph);
int		ph_start_philo(t_philosopher **philo, int count, t_data *ph);

void	*ph_sleep(void *data);
void	*ph_eat(void *data);
void	*ph_think(void *data);
void	*ph_eat_sleep_think(void *data);
void	*ph_think_eat_sleep(void *data);


/* UTILS */
long	time_now(void);
long	time_elapsed(long time, long start);
void	print_state(long time, t_philosopher *philo, t_state state);
void	update_time_and_sleep(t_philosopher *philo, t_state state);


#endif