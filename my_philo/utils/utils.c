/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:09:14 by mbendidi          #+#    #+#             */
/*   Updated: 2025/01/10 21:42:51 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long	get_timestamp()
{
	long n;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	n = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return(n);
}

long	get_relative_timestamp(long start_time)
{
	long	cur_time;

	cur_time = get_timestamp();
	return (cur_time - start_time);
}

void	display_state(t_data *data, char *state, char *color)
{
	long time;

	time = get_relative_timestamp(data->start_time);
	printf("%.4ld #%d %sis %s%s\n", time, data->id, color, state, "\033[0m");

}
