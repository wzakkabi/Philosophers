/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:07:06 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/22 18:28:24 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	full_the_format(int ac, char **av, t_philo *a)
{
	a->philo = atoi(av[1]);
	a->die = atoi(av[2]);
	a->eat = atoi(av[3]);
	a->sleep = atoi(av[4]);
	if (ac == 6)
		a->must_eat = atoi(av[5]) + 2;
	else
		a->must_eat = 2147483647;
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
