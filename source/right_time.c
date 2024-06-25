#include "philo.h"

long long	get_time(void)
{
	static long long	start;
	struct timeval		time;

	if (start == 0)
	{
		gettimeofday(&time, NULL);
		start = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start);
}

void    get_last_eat_time(t_philo *philos)
{
    pthread_mutex_lock(&philos->last_meal_mutex);
    philos->last_meal = get_time();
    pthread_mutex_unlock(&philos->last_meal_mutex);
}