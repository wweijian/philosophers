/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:17:28 by weijian           #+#    #+#             */
/*   Updated: 2025/08/12 10:35:51 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* --- LIBRARIES --- */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/* --- ERROR MESSAGES --- */
# define ERRMUT "mutex failed to be locked"
# define ERRINTMUT "mutex failed to be initialized"
# define ERRUNMUT "mutex failed to be unlocked"
# define ERRMEM "malloc failed"

/* DEFINE DELAY */
# define DELAY 1000

/* --- ENUM --- */
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

/* --- DATA STRUCTURES --- */

struct	s_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
}	t_fork;

typedef struct s_mutex
{
	pthread_mutex_t	print;
	pthread_mutex_t	end;
	pthread_mutex_t	start;
}	t_mutex;

typedef struct s_data
{
	int						count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						max_eat;
	int						finish_eating;
	int						sim_end;
	int						start_time;
	t_parity				parity;
	struct s_philosopher	**philo;
	t_mutex					mutex;
}	t_data;

typedef struct s_philosopher
{
	int			index;
	pthread_t	thread;
	int			times_eaten;
	int			last_ate;
	int			start_time;
	int			timer;
	t_fork		fork;
	t_data		*data;
}	t_philosopher;

/* --- PROTOTYPES --- */

/* --- INITIALIZATION --- */
int		ph_init_data(int ac, char **av, t_data *ph);
int		ph_init_philo(t_philosopher ***philo, t_data *data);
int		ph_init_shared_mutexes(t_data *data);
void	start_philo(t_philosopher **philo, t_data *data);

/* ACTIONS */
void	ph_eat(t_philosopher *philo);
void	ph_sleep(t_philosopher *philo);
void	ph_think(t_philosopher *philo);
void	ph_test(t_philosopher *philo);
void	*ph_start(void *arg);

/* DEATH */
int check_death(t_philosopher *philo, t_state action, int action_time);

/* PRINT */
void	print_state(t_philosopher *philo, t_state state);

/* UTILS */

/* PHILO->DATA */

int		count(t_philosopher *philo);
int		time_to_die(t_philosopher *philo);
int		time_to_eat(t_philosopher *philo);
int		time_to_sleep(t_philosopher *philo);
int		max_eat(t_philosopher *philo);

/* THINK */

int	count_think_time(t_philosopher *philo);

/* MUTEX */

int		lock(pthread_mutex_t *mutex);
int		unlock(pthread_mutex_t *mutex);
int		destroy(pthread_mutex_t *mutex);
int		init_mutex(pthread_mutex_t *mutex);

/* ACTIONS */
void	*ph_start(void *arg);

/* CLEANUP */

/* destroy frees the memory given to the mutex */
void	free_philosophers(t_philosopher **philo, int count);
void	detach_all(t_philosopher **philo, int count);
void	destroy_data_mutexes(t_data *data);

/* TIME */
int		time_now(void);
int		time_elapsed(t_philosopher *philo);


#endif