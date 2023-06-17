/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:42:13 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/06/17 18:52:39 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

struct philo_t
{
	int philo;
	int die;
	int eat;
	int sleep;
	int must_eat;
	int die_or_not;
	long int time;
	struct details_t *dtls;
};

struct details_t
{
	int philo_number;
	long int time;
	int last_meal;
	pthread_mutex_t *fork;
};



#endif