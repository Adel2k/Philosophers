#include "philo.h"

void validation(int ac, char **av, t_data *data)
{
    if (ac != 5 && ac != 6)
    {
        write(1, "Wrong arguments!\n", 18);
        exit(1);
    }
    data->philos = atoi(av[1]);
    data->die_t = atoi(av[2]);
    data->eating_t = atoi(av[3]);
    data->sleeping_t = atoi(av[4]);
	data->round = 1;
	if (av[5])
    	data->round = atoi(av[5]);
    if (data->die_t <= 0 || data->eating_t <= 0 || data->philos <= 0 || data->round <= 0 || data->sleeping_t <= 0)
    {
        write(1, "Wrong numbers!\n", 16);
        exit(1) ;
    }
}
void	even(t_data *data)
{
	int	i;

	i = 0;
			printf("%d is sleeping.\n", i);
	while (i < data->philos)
	{
		if (i % 2 == 0)
		{
			usleep(data->sleeping_t);
		}
		i++;
	}
}
void    *routine(t_data *data)
{
	if (data->philos / 2 == 0)
	{
		if (data->die_t == data->eating_t + data->sleeping_t + 10)
		{
		printf("%d is dead.\n", data->philos);
				even(data);
		}
	}
	// else if (data->philos / 2 != 0)
	// {
	// 	if (data->die_t = data->eating_t + data->sleeping_t + 10)
	// 	{
	// 			odd(data);
	// 	}
	// 	printf("%d is dead.\n", data->philos);
	// }
    // printf("%d is thinking.\n", data->philos);
    return (NULL);
}

void    philos(int n, t_data *data)
{
    int i;
    pthread_t   philo[n - 1];

	pthread_mutex_init(&data->mutex, NULL);
    i = 0;
    while (i < n)
    {
        pthread_create(&philo[i], NULL, (void *)&routine, data);
        i++;
    }
    i = 0;
    while(i < n)
    {
        pthread_join(philo[i], NULL);
        i++;
    }
}
int main(int ac, char **av)
{
    t_data data;

    if (!ac || !av[0] || !av[1])
    {
        write(1, "Error!\n", 8);
        return (1);
    }
    validation(ac, av, &data);
    philos(atoi(av[1]), &data);
}