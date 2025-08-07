

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

int	check_death(t_philosopher *philo)
{
	int	death;

	death = 0;
	lock(&philo->data->end_check);
	if (philo->data->philo_ended || philo->data->philo_died)
		death = 1;
	unlock(&philo->data->end_check);
	return (death);
}

void add_max_eat(t_philosopher *philo)
{
	lock(&philo->data->end_check);
	philo->data->max_eat_count++;
	unlock(&philo->data->end_check);
}