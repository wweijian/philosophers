

#include "philo.h"

int	ph_max_eat(t_data *ph)
{
	if (ph->max_eat_count == ph->max_eat)
		return (1);
	return (0);
}

void	*ph_monitoring(void *data)
{
	t_data			*ph;
	unsigned int	i;

	i = 0;
	ph = (t_data *) data;
	// printf("[philo.c: ph_monitoring] monitoring started\n");
	while (1)
	{
		lock(&ph->end_check);
		if (ph->philo_died == 1 || ph_max_eat(ph) == 1 || ph->philo_ended == 1)
			break ;
		unlock(&ph->end_check);
	}
	unlock(&ph->end_check);
	usleep(1000000);
	while (i < ph->count)
	{
		pthread_join(ph->ph[i]->thread, NULL);
		i++;
	}
	return (NULL);
}

int	check_any_death(t_philosopher *philo)
{
	int	death;

	death = 0;
	lock(&philo->data->end_check);
	if (philo->data->philo_ended || philo->data->philo_died)
		death = 1;
	unlock(&philo->data->end_check);
	return (death);
}

int	check_individual_death(t_philosopher *philo, t_state state, long action_time)
{
	if (state == EATING)
		philo->last_ate = philo->timer;
	if (philo->timer + action_time > philo->last_ate + philo->data->time_to_die)
	{
		usleep((philo->data->time_to_die + philo->last_ate - philo->timer)
			* 1000);
		philo->timer = philo->data->time_to_die + philo->last_ate;
		return (0);
	}
	usleep(action_time * 1000);
	// if (philo->timer < philo->last_print)
	// {
	// 	// puts("monitoring.c : check_individual_death");
	// 	lock(&philo->data->start);
	// 	philo->data->start_time++;
	// 	unlock(&philo->data->start);
	// }
	philo->timer += action_time;
	// fprintf(stdout, "[monitoring.c : check_individual_death] philo[%d]->timer: %ld  philo->last_print: %ld\n", philo->index, philo->timer, philo->last_print);
	return (1);
}

void add_max_eat(t_philosopher *philo)
{
	lock(&philo->data->end_check);
	philo->data->max_eat_count++;
	unlock(&philo->data->end_check);
}