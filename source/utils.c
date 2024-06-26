#include "philo.h"

int	p_error(char *str)
{
    printf("%s\n", str);
    return (-1);
}
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

void	pmessage(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->die_mutex);
	if (philo->dead != 1)
	{
		pthread_mutex_unlock(&philo->die_mutex);
		pthread_mutex_lock(&philo->data->message);
		printf("%lld %d %s\n", get_time(), philo->index + 1, str);
		pthread_mutex_unlock(&philo->data->message);
	}
	pthread_mutex_unlock(&philo->die_mutex);	
}

void	adels_usleep(t_philo *philo, long long time)
{
	long long	t2;

	t2 = get_time();
	while (get_time() - t2 <= time)
	{
		if (philo->data->is_dead == 1)
			break ;
		usleep(500);
	}
}

int	is_died(t_philo *philo)
{
	int	is_died;

	pthread_mutex_lock(&philo->data->is_dead_mutex);
	is_died = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	return (is_died);
}