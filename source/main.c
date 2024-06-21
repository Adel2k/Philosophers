#include "philo.h"



void validation(int ac, char **av, t_data *data)
{
    if (ac < 5 && ac > 6)
    {
        write(1, "Wrong arguments!\n", 18);
        return ;
    }
    data->philos = atoi(av[1]);
    data->die_t = atoi(av[2]);
    data->eating_t = atoi(av[3]);
    data->sleeping_t = atoi(av[4]);
    data->round = atoi(av[5]);
    if (data->die_t <= 0 || data->eating_t <= 0 || data->philos <= 0 || data->round <= 0 || data->sleeping_t <= 0)
        write(1, "Wrong numbers\n", 15);
}
void    *routine()
{
    write(1, "philo\n", 7);
    return (NULL);
}

void    philos(int n)
{
    int i;
    pthread_t   philo[n - 1];

    i = 0;
    while (i < n)
    {
        pthread_create(&philo[i], NULL, &routine, NULL);
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
    philos(atoi(av[1]));
}