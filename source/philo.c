#include "philo.h"

int	is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (get_time() > data->philo[i].last_meal + data->die_t)
		{
			pmessage("is dead", data->philo);
			data->philo->dead = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
void    *eat(t_philo *philos)
{
	if (philos->index + 1 % 2 == 0)
        usleep(philos->data->eating_t - 10);
	while (is_dead(philos->data) != 1)
    {
        pthread_mutex_lock(philos->right);
        pmessage("has taken a fork", philos);
        pthread_mutex_lock(philos->left);
        if (philos->data->philos == 1)
        {
            pthread_mutex_unlock(philos->left);
            p_error("Lonely philo will starve:(");
			philos->dead = 1;
        }
        pmessage("has taken a fork", philos);
    	pmessage("is eating", philos);
    	usleep(philos->data->sleeping_t);
        pthread_mutex_unlock(philos->right);
        pthread_mutex_unlock(philos->left);
        get_last_eat_time(philos);
		pmessage("is sleeping", philos);
		usleep(philos->data->sleeping_t);
		pmessage("is thinking", philos);
    }
    return (NULL);
}

void    forks(t_data *data)
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->philos);
    while (i < data->philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
}

void    philos_init(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philos)
    {
        data->philo[i].dead = 0;        
        data->philo[i].eaten = 0;
        data->philo[i].last_meal = 0;
        data->philo[i].index = i;
        data->philo[i].data = data;
        get_last_eat_time(&data->philo[i]);
        if (data->philo[i].index == 0)
            data->philo[i].right = &data->forks[data->philos];
        else
            data->philo[i].right = &data->forks[i - 1];
        data->philo[i].left = &data->forks[i];
        pthread_create(&data->philo[i].thread_id, NULL, (void *)&eat, &data->philo[i]);
        i++;
    }
}
void    philos(t_data *data)
{
    int i;

    i = 0;
    data->philo = malloc(sizeof(t_philo) * data->philos);
    get_time();
    pthread_mutex_init(&data->message, NULL);
    forks(data);
    philos_init(data);
	while (1)
	{
		if (is_dead(data) == 1 || data->philo->dead == 1)
			break;
	}
    while (i < data->philos)
    {
        pthread_join(data->philo[i].thread_id, NULL);
		pthread_mutex_destroy(&data->message);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
    }
	free(data->philo);
	free(data->forks);
}
