#include "philo.h"

int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		if (get_time() > data->philo[i].last_meal + data->die_t)
		{
			pthread_mutex_lock(&data->philo[i].die_mutex);
			data->philo[i].dead = 1;
			pthread_mutex_unlock(&data->philo[i].die_mutex);
			pthread_mutex_lock(&data->is_dead_mutex);
			data->is_dead = 1;
			pthread_mutex_lock(&data->message);
			printf("%lld %d is dead\n", get_time(), data->philo[i].index + 1);
			pthread_mutex_unlock(&data->message);
			pthread_mutex_unlock(&data->is_dead_mutex);
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		i++;
	}
	return (0);
}

int	is_died(t_philo *philo)
{
	int	is_died;

	pthread_mutex_lock(&philo->data->is_dead_mutex);
	is_died = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	return (is_died);
}
