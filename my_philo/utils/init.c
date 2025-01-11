# include "philo.h"

void init_data(t_data *data, char **av)
{
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	data->nb_eat = ft_atoi(av[5]);
    data->time_to_think = 0;
	data->start_time = get_time();
	pthread_mutex_init(&data->print_mutex, NULL);
}

void init_philo(t_philo *philo, t_data *data)
{
    int i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].meals_eaten = 0;
		i++;
	}
}