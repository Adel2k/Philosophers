#include "philo.h"

int	p_error(char *str)
{
	printf("%s\n", str);
	return (-1);
}

void	pmessage(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->is_dead_mutex);
	if (philo->data->is_dead != 1)
	{
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		pthread_mutex_lock(&philo->data->message);
		printf("%lld %d %s\n", get_time(), philo->index + 1, str);
		pthread_mutex_unlock(&philo->data->message);
	}
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
}

void	free_destroy(t_data *data)
{
	pthread_mutex_destroy(&data->message);
	pthread_mutex_destroy(&data->is_dead_mutex);
	free(data->philo);
	free(data->forks);
}

void	usleep_alt(t_philo *philo, long long time)
{
	long long	t2;

	t2 = get_time();
	while (get_time() - t2 <= time)
	{
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		if (philo->data->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->data->is_dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		usleep(500);
	}
}
