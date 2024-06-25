#include "philo.h"

void	validation(int ac, char **av, t_data *data)
{
    if (ac != 5 && ac != 6)
	{
	    p_error("Wrong arguments!");
		return ;
	}
    data->philos = ft_atoi(av[1]);
    data->die_t = ft_atoi(av[2]);
    data->eating_t = ft_atoi(av[3]);
    data->sleeping_t = ft_atoi(av[4]);
	data->round = 1;
	if (av[5])
    	data->round = ft_atoi(av[5]);
    if (data->die_t <= 0 || data->eating_t <= 0 || data->philos <= 0 || data->round <= 0 || data->sleeping_t <= 0)
        p_error("Wrong numbers!");
}