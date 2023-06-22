/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:07:16 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/22 19:31:15 by wzakkabi         ###   ########.fr       */
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
	x = ((ft_usleep(1)), -1);
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

	x = (-1);
	while (1)
	{
		if (x++ == a->philo - 1)
			x = 0;
		pthread_mutex_lock(&a->print[0]);
		lock1 = a->meal[0];
		lock = ft_time_get() - a->last_meal[x];
		pthread_mutex_unlock(&a->print[0]);
		if (lock1 == a->must_eat)
		{
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
	}
}
