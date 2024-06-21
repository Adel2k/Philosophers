#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>

typedef struct s_data
{
    int	philos;
	int eating_t;
	int	sleeping_t;
	int die_t;
	int round;
} t_data;


#endif