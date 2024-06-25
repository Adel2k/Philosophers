#include "philo.h"

int main(int ac, char **av)
{
    t_data *data;

	data = malloc(sizeof(t_data));
    if (!ac || !av[0] || !av[1])
    {
        write(1, "Error!\n", 8);
        return (1);
    }
    validation(ac, av, data);
    philos(data);
	free(data);
}