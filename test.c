/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:44:54 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/21 22:54:43 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	check_die_or_not(philo_t *a, details_t *p, int lock1, long int lock)
{
	int	x;

	x = 0;
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
			printf("%ld %d died\n",
				(ft_time_get() - p[x].time), p[x].philo_number);
			break ;
		}
		x++;
	}
}
