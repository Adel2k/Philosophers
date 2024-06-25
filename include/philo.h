# ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

typedef struct s_philo t_philo;

typedef struct s_data
{
    int				philos;
	int 			eating_t;
	int				sleeping_t;
	int				die_t;
	int				round;
	pthread_mutex_t	*forks;
	pthread_mutex_t message;
	t_philo			*philo;
} t_data;

typedef struct s_philo
{
	int				dead;
	int				eaten;
	int				index;
	int				last_meal;
	pthread_t		thread_id;
	t_data			*data;
	pthread_mutex_t *left;
	pthread_mutex_t	*right;
	pthread_mutex_t	last_meal_mutex;
} t_philo;


int    	p_error(char *str);
int			ft_atoi(char *str);
void		validation(int ac, char **av, t_data *data);
long long	get_time(void);
void		get_last_eat_time(t_philo *philos);
void		philos(t_data *data);
void		pmessage(char *str, t_philo *philo);
void		*eat(t_philo *philos);
void		check(char *str);



# endif