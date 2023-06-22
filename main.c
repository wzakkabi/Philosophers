/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:07:06 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/22 19:47:41 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	full_the_format(int ac, char **av, t_philo *a)
{
	a->philo = ft_atoi(av[1]);
	a->die = ft_atoi(av[2]);
	a->eat = ft_atoi(av[3]);
	a->sleep = ft_atoi(av[4]);
	if (ac == 6)
		a->must_eat = ft_atoi(av[5]);
	else
		a->must_eat = 2147483000;
}

int	ft_atoi(const char *str)
{
	int	x;
	int	a;
	int	y;

	y = 1;
	a = 0;
	x = 0;
	while ((str[x] >= 9 && str[x] <= 13) || str[x] == 32)
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			y = -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		a = a * 10 + (str[x] - 48);
		x++;
	}
	return (a * y);
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
	int			x;

	x = -1;
	if (check_arg(ac, av) == 0)
	{
		a = (t_philo *)malloc(sizeof(t_philo) * 1);
		full_the_format(ac, av, a);
		if (a->philo <= 0 || a->must_eat == 0)
			return (0);
		a->must_eat += 1;
		a->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * a->philo);
		a->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		a->last_meal = malloc(sizeof(long int) * a->philo);
		a->meal = malloc(sizeof(int) * a->philo);
		while (++x < a->philo)
			a->meal[x] = 0;
		p = (t_details *)malloc(sizeof(t_details) * a->philo);
		philo(a, p);
		ft_free(a, p);
	}
	return (0);
}
