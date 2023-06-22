/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:42:03 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/22 18:10:57 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int			i;

	i = 0;
	p = (t_details *)pp;
	while (p->test->meal[p->philo_number - 1] < p->test->must_eat)
	{
		if (i != 0 || p->philo_number - 1 != 0)
			x_print("is thinking", p, 0);
		ft_eat(p);
		x_print("is sleeping", p, 0);
		ft_usleep(p->test->sleep);
		i++;
	}
	return ((void *)p);
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
