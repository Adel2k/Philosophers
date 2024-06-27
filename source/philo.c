#include "philo.h"

void	*lonely(t_philo *philos)
{
	pthread_mutex_unlock(philos->left);
	pthread_mutex_lock(&philos->die_mutex);
	philos->dead = 1;
	pthread_mutex_unlock(&philos->die_mutex);
	return (NULL);
}

void	*eat(t_philo *philos)
{
	if (philos->index % 2 == 0)
		usleep(philos->data->eating_t - 10);
	while (is_died(philos) != 1)
	{
		pthread_mutex_lock(philos->left);
		pmessage("has taken a fork", philos);
		if (philos->data->philos == 1)
			lonely(philos);
		pthread_mutex_lock(philos->right);
		pmessage("has taken a fork", philos);
		pmessage("is eating", philos);
		usleep_alt(philos, philos->data->eating_t);
		pthread_mutex_unlock(philos->left);
		pthread_mutex_unlock(philos->right);
		pmessage("is sleeping", philos);
		get_last_eat_time(philos);
		usleep_alt(philos, philos->data->sleeping_t);
		pmessage("is thinking", philos);
	}
	return (NULL);
}

void	forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos);
	while (i < data->philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	philos_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->philo[i].die_mutex, NULL);
		data->philo[i].dead = 0;
		data->philo[i].eaten = 0;
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		data->philo[i].last_meal = 0;
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		data->philo[i].index = i;
		data->philo[i].data = data;
		get_last_eat_time(&data->philo[i]);
		if (data->philo[i].index == 0)
			data->philo[i].right = &data->forks[data->philos];
		else
			data->philo[i].right = &data->forks[i - 1];
		data->philo[i].left = &data->forks[i];
	}
	i = -1;
	while (++i < data->philos)
		pthread_create(&data->philo[i].thread_id, NULL, (void *)&eat,
			&data->philo[i]);
}

void	creating_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philos);
	pthread_mutex_init(&data->message, NULL);
	pthread_mutex_init(&data->is_dead_mutex, NULL);
	data->is_dead = 0;
	forks(data);
	philos_init(data);
	while (1)
	{
		if (check_if_dead(data) == 1)
			break ;
	}
	while (i < data->philos)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
		pthread_mutex_destroy(&data->philo[i].die_mutex);
		i++;
	}
	free_destroy(data);
}
