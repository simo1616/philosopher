/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:09:14 by mbendidi          #+#    #+#             */
/*   Updated: 2025/01/11 20:30:44 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	get_relative_timestamp(uint64_t start_time)
{
	uint64_t	cur_time;

	cur_time = get_time();
	return (cur_time - start_time);
}

void	display_state(t_philo *philo, char *state, char *color, uint64_t start_time)
{
	uint64_t time;

	time = get_relative_timestamp(start_time);
	printf("%04lu #%d %s%s%s\n", time, philo->id, color, state, "\033[0m");
}

void free_resources(t_data *data, t_philo *philo)
{
    for (int i = 0; i < data->nb_philo; i++)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print_mutex);
    free(data->forks);
    free(philo);
}
