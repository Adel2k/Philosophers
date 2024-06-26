#include "philo.h"

int	is_dead(t_data *data)
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
            pthread_mutex_lock(&data->message);
            printf("%lld %d is dead\n", get_time(), data->philo[i].index);
            pthread_mutex_unlock(&data->message);
            pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			return (1);
		}
        pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
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
        i++;
    }
	i = -1;
    while(++i < data->philos)
        pthread_create(&data->philo[i].thread_id, NULL, (void *)&eat, &data->philo[i]);
}
void    philos(t_data *data)
{
    int i;

    i = 0;
    data->philo = malloc(sizeof(t_philo) * data->philos);
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
		pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
		pthread_mutex_destroy(&data->philo[i].die_mutex);
		i++;
    }
	free(data->philo);
	free(data->forks);
}
