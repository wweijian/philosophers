/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:17:28 by weijian           #+#    #+#             */
/*   Updated: 2025/08/11 10:23:17 by weijian          ###   ########.fr       */
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

struct s_philosopher;

typedef struct s_fork
{
	pthread_mutex_t	left;
	pthread_mutex_t *right;
}	t_fork;

typedef struct s_data
{
	unsigned int			count;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	unsigned int			max_eat;
	unsigned int			max_eat_count;
	unsigned int			sim_end;
	t_parity				parity;
	struct s_philosopher	**philo;
}	t_data;

typedef struct s_philosopher
{
	t_data	*				data;
}	t_philosopher;

/* --- PROTOTYPES --- */

/* --- INITIALIZATION --- */
int	ph_init_data(int ac, char **av, t_data *ph);

#endif