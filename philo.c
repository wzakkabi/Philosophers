/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:42:03 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/17 21:30:18 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



long int ft_time_get()
{
	struct timeval a;
	long int tm;
	if((gettimeofday(&a, NULL)) != 0)
	{
		printf("error can't get time ");
		exit(1);
	}
	tm = (a.tv_sec * 1000) + (a.tv_usec / 1000);
	return tm;
}

void full_the_format(int ac, char **av, struct philo_t *a)
{
	a->philo = atoi(av[1]);
	a->die = atoi(av[2]);
	a->eat = atoi(av[3]);
	a->sleep = atoi(av[4]);

	if(ac == 6)
		a->must_eat = atoi(av[5]);
	else
		a->must_eat = 2147483647;
}

void *how_I_live(void *pp)
{
	struct details_t *p = (struct details_t *)pp;

	printf("time = %ld philo = %d\n", p->time, p->philo_number);

	return (void *)p;
}


void	philo(struct philo_t *a)
{
	pthread_t philo[a->philo];
	pthread_mutex_t fork[a->philo];
	struct details_t p[a->philo];
	int x = 0;
	while(x < a->philo)
	{
		if(pthread_mutex_init(&fork[x], NULL) != 0)
		{
			printf("Error mutex");
			return ;
		}
		x++;
	}
	x = 0;
	a->time = ft_time_get();
	while(x < a->philo)
	{
		p[x].philo_number = x + 1;
		p[x].time = a->time;
		p[x].fork = fork;
		p[x].last_meal = 0;
		if(pthread_create(&philo[x], NULL, how_I_live, (void *)&p[x]) != 0)
		{
			printf("Error pthread");
			return ;
		}
		x++;
	}
	x = 0;
	while(x < a->philo)
	{
		if(pthread_join(philo[x], NULL)!= 0)
		{
			printf("Error join pthread");
			return ;
		}
		x++;
	}
}

int main(int ac, char **av)
{
	struct philo_t a;
	int x = 0, y = 1;
	if(ac == 5 || ac == 6)
	{
	    while(av[y])
	    {
	        if(av[y][x] == '+')
	                x++;
	        while(av[y][x])
	        {
	            if(av[y][x] < '0' || av[y][x] > '9')
	            {
	                printf("error\n");
	                return 0;
	            }
	            x++;
	        }
	        y++;
	        x = 0;
	    }
		full_the_format(ac, av, &a);
		philo(&a);
	}
	return 0;
}
