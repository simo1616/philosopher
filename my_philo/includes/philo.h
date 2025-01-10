/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:12:13 by mbendidi          #+#    #+#             */
/*   Updated: 2025/01/10 21:42:51 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include "libft.h"


typedef struct s_data
{
	int			id;
	long		start_time;
	pthread_t	thread;
} t_data;

typedef struct s_args
{
	int	think_time;
	int	eat_time;
	int sleep_time;
	int	time_to_die;
	int nb_philo;
} t_args;

long	get_timestamp();
long	get_relative_timestamp(long start_time);
void	display_state(t_data *data, char *state, char *color);

#endif