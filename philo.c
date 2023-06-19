/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:42:03 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/19 04:28:05 by wzakkabi         ###   ########.fr       */
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

void ft_usleep(int t)
{
	long int aa = ft_time_get();
	while(1)
	{
		if(ft_time_get() - aa >= t)
			break;
		usleep(60);
	}
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

void	ft_eat(struct details_t *p)
{
	if(p->philo_number < p->test->philo)
	{
		pthread_mutex_lock(&p->fork[p->philo_number - 1]);
		pthread_mutex_lock(&p->fork[p->philo_number]);
		printf("%ld %d has taken a fork\n",ft_time_get() - p->time, p->philo_number);
		p->last_meal = ft_time_get();
		printf("%ld %d is eating\n",ft_time_get() - p->time, p->philo_number);
		ft_usleep(p->test->eat);
		pthread_mutex_unlock(&p->fork[p->philo_number - 1]);
		pthread_mutex_unlock(&p->fork[p->philo_number]);
		printf("%ld %d is sleeping\n", (ft_time_get() - p->time) , p->philo_number);
		ft_usleep(p->test->sleep);
	}
	else
	{
		pthread_mutex_lock(&p->fork[p->philo_number - 1]);
		pthread_mutex_lock(&p->fork[0]);
		printf("%ld %d has taken a fork\n",ft_time_get() - p->time, p->philo_number);
		p->last_meal = ft_time_get();
		printf("%ld %d is eating\n",ft_time_get() - p->time, p->philo_number);
		ft_usleep(p->test->eat);
		pthread_mutex_unlock(&p->fork[p->philo_number - 1]);
		pthread_mutex_unlock(&p->fork[0]);
		printf("%ld %d is sleeping\n", (ft_time_get() - p->time) , p->philo_number);
		ft_usleep(p->test->sleep);
	}
}

void *how_I_live(void *pp)
{
	struct details_t *p = (struct details_t *)pp;
	while(p->meal < p->test->must_eat)
	{
		// if(p->philo_number % 2 == 0 && p->eat == 0)
		// {
		// 	ft_eat(p);
		// 	p->eat = 1;
		// }
		// else
		// {
			printf("%ld %d is thinking\n", (ft_time_get() - p->time) , p->philo_number);
			ft_eat(p);
		//}
		p->meal++;
	}
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
		p[x].eat = 0;
		p[x].philo_number = x + 1;
		p[x].time = a->time;
		p[x].fork = fork;
		p[x].last_meal = 0;
		p[x].meal = 0;
		p[x].test = a;
		if(x % 2 == 0)
		{
			if(pthread_create(&philo[x], NULL, how_I_live, (void *)&p[x]) != 0)
			{
				printf("Error pthread");
				return ;
			}
		}
		x++;
	}
	x = 0;
	while(x < a->philo)
	{
		if(x % 2 == 1)
		{
			if(pthread_create(&philo[x], NULL, how_I_live, (void *)&p[x]) != 0)
			{
				printf("Error pthread");
				return ;
			}
		}
		x++;
	}
	x = 0;
	ft_usleep(a->die);
	while(1)
	{
		if(ft_time_get() - p[x].last_meal > a->die)
		{
			printf("%ld %d died\n", (ft_time_get() - p[x].time),  p->philo_number);
			return ;
		}
		if(x == a->philo)
			x = 0;
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
