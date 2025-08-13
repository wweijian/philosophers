/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:31:00 by wjhoe             #+#    #+#             */
/*   Updated: 2025/08/13 13:12:43 by wjhoe            ###   ########.fr       */
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
# define DELAY 1000

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

typedef enum s_end
{
	DIE,
	END
}	t_end;

/* STRUCT */

struct	s_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
}	t_fork;

typedef struct s_data
{
	unsigned int			count;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	unsigned int			max_eat;
	unsigned int			max_eat_count;
	long					philo_died;
	int						philo_ended;
	t_parity				parity;
	time_t					start_time;
	pthread_mutex_t			print;
	pthread_mutex_t			end_check;
	pthread_mutex_t			start;
	pthread_t				monitoring;
	struct s_philosopher	**ph;
}	t_data;

typedef struct s_philosopher
{
	unsigned int	index;
	t_parity		parity;
	pthread_t		thread;
	unsigned int	times_eaten;
	unsigned int	last_ate;
	t_state			state;
	t_fork			fork;
	time_t			timer;
	time_t			elapsed_time;
	time_t			last_print;
	t_data			*data;
}	t_philosopher;

/* INITIALIZING */
int		ph_init_data(int ac, char **av, t_data *ph_data);
int		init_philosophers(t_philosopher ***philo, int count, t_data *data);
void	init_data(t_data *ph);

/* CLEAN UP */
void	free_philosophers(t_philosopher **philo, int count);
void	error_msg(char *message);
void	detach_all(t_philosopher **philo, int count);

/* SIMULATION */
void	ph_monitoring_thread(t_data *ph);
int		ph_start_philo(t_philosopher **philo, int count, t_data *ph);

void	ph_end(t_philosopher *data, t_end end);
void	ph_sleep(t_philosopher *data);
void	ph_eat(t_philosopher *data);
void	ph_think(t_philosopher *data);
void	*ph_thread(void *data);

/* MUTEX */
int		lock(pthread_mutex_t *mutex);
int		unlock(pthread_mutex_t *mutex);
int		destroy(pthread_mutex_t *mutex);
int		take_forks(t_philosopher *philo);
int		drop_forks(t_philosopher *philo);

/* TIME */
long	time_now(void);
long	time_elapsed(t_philosopher *philo);
void	add_delay(t_philosopher *philo);

/* MONITORING */
void	*ph_monitoring(void *data);
int		check_any_death(t_philosopher *philo);
int		check_individual_death(t_philosopher *philo, t_state state,
			long action_time);
void	add_max_eat(t_philosopher *philo);

/* UTILS */
void	print_state(t_philosopher *philo, t_state state, long action_time);
void	print_dead(long time, t_philosopher *philo);
int		update_timer(t_philosopher *philo, t_state state, long action_time);
long	count_think_time(t_philosopher *philo);

#endif