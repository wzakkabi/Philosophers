/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:42:03 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/22 17:57:26 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



long int	ft_time_get(void)
{
	struct timeval	a;
	long int		tm;

	if ((gettimeofday(&a, NULL)) != 0)
	{
		printf("error can't get time ");
		exit(1);
	}
	tm = (a.tv_sec * 1000) + (a.tv_usec / 1000);
	return (tm);
}

void	ft_usleep(int t)
{
	long int	aa;

	aa = ft_time_get();
	while (1)
	{
		if (ft_time_get() - aa >= t)
			break ;
		usleep(60);
	}
}

void	full_the_format(int ac, char **av, t_philo *a)
{
	a->philo = atoi(av[1]);
	a->die = atoi(av[2]);
	a->eat = atoi(av[3]);
	a->sleep = atoi(av[4]);
	if (ac == 6)
		a->must_eat = atoi(av[5]);
	else
		a->must_eat = 2147483647;
}

void	x_print(char *s, t_details *p, int i)
{
	pthread_mutex_lock(&p->test->print[0]);
	if (i == 1)
	{
		p->test->meal[p->philo_number - 1] += 1;
		p->test->last_meal[p->philo_number - 1] = ft_time_get();
	}
	printf("%ld %d %s\n", (ft_time_get() - p->time), p->philo_number, s);
	pthread_mutex_unlock(&p->test->print[0]);
}


void	ft_eat(t_details *p)
{
	if (p->philo_number < p->test->philo)
	{
		pthread_mutex_lock(&p->fork[p->philo_number - 1]);
		x_print("has taken a fork", p, 0);
		pthread_mutex_lock(&p->fork[p->philo_number]);
		x_print("has taken a fork", p, 0);
		x_print("is eating", p, 1);
		ft_usleep(p->test->eat);
		pthread_mutex_unlock(&p->fork[p->philo_number - 1]);
		pthread_mutex_unlock(&p->fork[p->philo_number]);
	}
	else
	{
		pthread_mutex_lock(&p->fork[p->philo_number - 1]);
		x_print("has taken a fork", p, 0);
		pthread_mutex_lock(&p->fork[0]);
		x_print("has taken a fork", p, 0);
		x_print("is eating", p, 1);
		ft_usleep(p->test->eat);
		pthread_mutex_unlock(&p->fork[p->philo_number - 1]);
		pthread_mutex_unlock(&p->fork[0]);
	}
}

void	*how_i_live(void *pp)
{
	t_details	*p;
	int i;

	i = 0;
	p = (t_details *)pp;
	while (p->test->meal[p->philo_number - 1] < p->test->must_eat)
	{
		if(i != 0 || p->philo_number - 1 != 0)
			x_print("is thinking", p, 0);
		ft_eat(p);
		x_print("is sleeping", p, 0);
		ft_usleep(p->test->sleep);
		i++;
	}
	return ((void *)p);
}

void	creat_thread_modulo(t_philo *a, t_details *p)
{
	int	x;

	a->tread = (pthread_t *)malloc(sizeof(pthread_t) * a->philo);
	x = -1;
	a->time = ft_time_get();
	while (++x < a->philo)
	{
		p[x].time = ((p[x].fork = a->fork), a->time);
		p[x].test = (a);
		a->meal[x] = ((p[x].philo_number = x + 1), 0);
		p->test->last_meal[x] = ft_time_get();
		if (x % 2 == 0)
			if (pthread_create(&a->tread[x], NULL,
					how_i_live, (void *)&p[x]) != 0)
				return ;
		usleep(1);
	}
	ft_usleep(1);
	x = (-1);
	while (++x < a->philo)
	{
		if (x % 2 == 1)
			if (pthread_create(&a->tread[x], NULL,
					how_i_live, (void *)&p[x]) != 0)
				return ;
	}
}

void	ft_free(t_philo *a, t_details *p)
{
	int	x;

	x = 0;
	while (x < a->philo)
	{
		pthread_detach(a->tread[x]);
		x++;
	}
	x = 0;
	while (x < a->philo)
	{
		pthread_mutex_destroy(&a->fork[x]);
		x++;
	}
	pthread_mutex_destroy(&a->print[0]);
	free(a->fork);
	free(a->print);
	free(a->last_meal);
	free(a->meal);
	free(a->tread);
	free(p);
	free(a);
}


void	check_die(t_philo *a, t_details *p, int lock1, long int lock)
{
	int	x;

	x = ((ft_usleep(a->die)), 0);
	while (1)
	{
		if (x == a->philo - 1)
			x = 0;
		pthread_mutex_lock(&a->print[0]);
		lock1 = a->meal[x];
		lock = ft_time_get() - a->last_meal[x];
		pthread_mutex_unlock(&a->print[0]);
		if (lock1 == a->must_eat)
		{
			ft_usleep(a->die);
			break ;
		}
		if (lock > a->die)
		{
			pthread_mutex_lock(&a->print[0]);
			ft_usleep(1);
			printf("%ld %d died\n",
				(ft_time_get() - p[x].time), p[x].philo_number);
			break ;
		}
		x++;
	}
}

void	philo(t_philo *a, t_details	*p)
{
	int	x;

	x = -1;
	if (pthread_mutex_init(&a->print[0], NULL) != 0)
		return ;
	while (++x < a->philo)
		if (pthread_mutex_init(&a->fork[x], NULL) != 0)
			return ;
	creat_thread_modulo(a, p);
	check_die(a, p, 0, 0);
}


int	check_arg(int ac, char **av)
{
	int	x;
	int	y;

	x = ((y = 1), 0);
	if (ac == 5 || ac == 6)
	{
		while (av[y])
		{
			if (av[y][x] == '+')
					x++;
			while (av[y][x])
			{
				if (av[y][x] < '0' || av[y][x] > '9')
				{
					printf("error\n");
					return (1);
				}
				x++;
			}
			y++;
			x = 0;
		}
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo		*a;
	t_details	*p;

	if (check_arg(ac, av) == 0)
	{
		a = (t_philo *)malloc(sizeof(t_philo) * 1);
		full_the_format(ac, av, a);
		if (a->philo <= 0)
			return (0);
		a->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * a->philo);
		a->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		a->last_meal = malloc(sizeof(long int) * a->philo);
		a->meal = malloc(sizeof(int) * a->philo);
		p = (t_details *)malloc(sizeof(t_details) * a->philo);
		philo(a, p);
		ft_free(a, p);
	}
	return (0);
}

