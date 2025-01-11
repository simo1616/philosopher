/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:12:13 by mbendidi          #+#    #+#             */
/*   Updated: 2025/01/11 10:56:25 by mbendidi         ###   ########.fr       */
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
# include <stdint.h>
# include "libft.h"

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo
{
	int			id;
	uint64_t		start_time;
	pthread_t	thread;
} t_philo;

typedef struct s_data
{
	int		time_to_think;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_to_die;
	int		nb_philo;
	int		nb_eat;
} t_data;

uint64_t	get_time(void);
uint64_t	get_relative_timestamp(uint64_t start_time);
void	display_state(t_philo *philo, char *state, char *color, int i);
int 	error(char *str, t_data *data);
void	ft_exit(t_data *data);
void	init_data(t_data *data, char **av);
void	init_philo(t_philo *philo, char **av);

#endif