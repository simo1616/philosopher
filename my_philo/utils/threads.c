# include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		printf("-------philo->id = %d---------\n", philo->id);

		pthread_mutex_lock(&data->print_mutex);
		display_state(philo, EATING, "\033[032m", data->start_time);
		pthread_mutex_unlock(&data->print_mutex);

		philo->meals_eaten++;
		if(philo->meals_eaten >= data->nb_eat)
			break;
		usleep(data->time_to_think * 1000);

		pthread_mutex_lock(&data->print_mutex);
		display_state(philo, SLEEPING, "\033[033m", data->start_time);
		pthread_mutex_unlock(&data->print_mutex);

		usleep(data->time_to_eat * 1000);

		pthread_mutex_lock(&data->print_mutex);
		display_state(philo, THINKING, "\033[095m", data->start_time);
		pthread_mutex_unlock(&data->print_mutex);

		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}

int ft_thread(t_philo *philo, t_data *data, int ac)
{
	int i;

	if (ac == 6)
    {
		i = 0;
		//printf("\n**************iteration = ****************\n");
		while (i < data->nb_philo)
		{
			if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
			{
				fprintf(stderr, "Error creating thread for philosopher %d\n", philo[i].id);
				return (0);
			}

			i++;
		}

		i = 0;
		while (i < data->nb_philo)
		{
			if (pthread_join(philo[i].thread, NULL) != 0)
			{
				fprintf(stderr, "Error joining thread for philosopher %d\n", philo[i].id);
				return (0);
			}
			i++;
		}
    }
	return (1);
}
