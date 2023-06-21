/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:28:48 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/21 20:57:51 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	philo(philo_t *a)
{
	details_t	*p;
	int			x;
	int		lock1;
	long int lock;
	a->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * a->philo);
	a->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	a->last_meal = malloc(sizeof(long int) * a->philo);
	a->meal = malloc(sizeof(int) * a->philo);
	p = (details_t *)malloc(sizeof(details_t) * a->philo);
	x = -1;
	if (pthread_mutex_init(&a->print[0], NULL) != 0)
			return ;
	while (++x < a->philo)
		if (pthread_mutex_init(&a->fork[x], NULL) != 0)
			return ;
	creat_thread_modulo(a, p);
	x = 0;
	while (1)
	{
		if (x == a->philo - 1)
		{
			x = 0;
		}
		pthread_mutex_lock(&a->print[0]);
		lock1 = a->meal[x];
		pthread_mutex_unlock(&a->print[0]);
		if(lock1 == a->must_eat)
		{
			ft_usleep(a->die);
			break;
		}
		pthread_mutex_lock(&a->print[0]);
		lock = ft_time_get() - a->last_meal[x];
		pthread_mutex_unlock(&a->print[0]);
		if ( lock > a->die)
		{
			pthread_mutex_lock(&a->print[0]);
			printf("%ld %d died\n",
				(ft_time_get() - p[x].time), p[x].philo_number);
				break;
		}
		x++;
	}
	ft_free(a, p);
}
