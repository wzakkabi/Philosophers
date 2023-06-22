/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:42:13 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/22 19:45:07 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_details	t_details;
typedef struct s_philo
{
	int				philo;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	int				die_or_not;
	long int		time;
	long int		*last_meal;
	t_details		*dtls;
	pthread_t		*tread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	int				*meal;
}t_philo;

typedef struct s_details
{
	int				philo_number;
	long int		time;
	long int		prnt_time;
	t_philo			*test;
	pthread_mutex_t	*fork;
	int				*d;
}t_details;

long int	ft_time_get(void);
void		ft_usleep(int t);
void		full_the_format(int ac, char **av, t_philo *a);
void		x_print(char *s, t_details *p, int i);
void		ft_eat(t_details *p);
void		*how_i_live(void *pp);
void		creat_thread_modulo(t_philo *a, t_details *p);
void		ft_free(t_philo *a, t_details *p);
void		check_die(t_philo *a, t_details *p, int lock1, long int lock);
void		philo(t_philo *a, t_details	*p);
int			check_arg(int ac, char **av);
int			ft_atoi(const char *str);

#endif