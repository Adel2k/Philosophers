#include "philo.h"

void	check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			p_error("Enter just number!");
		i++;
	}
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long long	numb;

	i = 0;
	numb = 0;
	sign = 1;
	check(str);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '+' || str[i] == '-'))
	{
		if (str[i + 1] == 0)
			p_error("Error");
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		numb = (numb * 10) + (str[i++] - '0');
	numb = numb * sign;
	if (numb > INT_MAX || numb < INT_MIN)
		p_error("Error");
	return (numb);
}

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
	if (data->die_t <= 0 || data->eating_t <= 0 || data->philos <= 0
		|| data->round <= 0 || data->sleeping_t <= 0)
		p_error("Wrong numbers!");
}
