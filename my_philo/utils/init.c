# include "philo.h"

int init_data(t_data *data, t_philo *philo, char **av)
{
	int i;

	i = 0;
    data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo <= 0)
	{
		fprintf(stderr, "Error: Invalid number of philosophers\n");
		return (0);
	}
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	data->nb_eat = ft_atoi(av[5]);
    data->time_to_think = 0;
	data->simulation_active = 1;
	data->start_time = get_time();
	data->philo = philo;
	pthread_mutex_init(&data->print_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		error("Error: Failed to allocate memory for forks\n", data);
		return (0);
	}
	while(i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (1);
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
		philo[i].last_meal_time = data->start_time;
		i++;
	}
}