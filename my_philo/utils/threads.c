# include "philo.h"

void *supervisor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (data->simulation_active)
    {
        int all_meals_eaten = 1;

        for (i = 0; i < data->nb_philo; i++)
        {
            t_philo *philo = &data->philo[i];

            // Vérifie si un philosophe est mort
            if (!data->death_reported && get_time() - philo->last_meal_time > (uint64_t)data->time_to_die)
            {
                pthread_mutex_lock(&data->print_mutex);
                display_state(philo, DIED, "\033[031m", data->start_time);
                data->death_reported = 1;
				data->simulation_active = 0;
                pthread_mutex_unlock(&data->print_mutex);
                return NULL; // Arrête la supervision immédiatement
            }

            // Vérifie si tous les philosophes ont mangé le nombre requis de repas
            if (data->nb_eat != -1 && philo->meals_eaten < data->nb_eat)
            {
                all_meals_eaten = 0; // Tous les repas ne sont pas encore terminés
            }
        }

        // Si tous les philosophes ont fini leurs repas
        if (all_meals_eaten)
        {
            data->simulation_active = 0;
            return NULL;
        }

        usleep(1000); // Pause courte pour éviter une surcharge CPU
    }

    return NULL;
}

void *philo_routine(void *arg)
{
	t_philo *philo;
	t_data *data;
	int left_fork;
	int right_fork;


	philo = (t_philo *)arg;
	data = philo->data;

	left_fork = philo->id - 1;
	//printf("left_fork = %d\n", left_fork); // debug
	right_fork = philo->id % data->nb_philo;
	//printf("right_fork = %d\n", right_fork); // debug
	
	if (left_fork < 0 || left_fork >= data->nb_philo || right_fork < 0 || right_fork >= data->nb_philo)
	{
		fprintf(stderr, "Invalid fork index for philosopher %d\n", philo->id);
		pthread_exit(NULL);
	}
	if (data->nb_philo == 1)
    {
        usleep(data->time_to_die * 1000); // Attendre jusqu'à ce qu'il meure
        pthread_mutex_lock(&data->print_mutex);
        display_state(philo, DIED, "\033[031m", data->start_time);
        pthread_mutex_unlock(&data->print_mutex);
        return NULL;
    }
	while (data->simulation_active)
	{
		//printf("-------philo->id = %d---------\n", philo->id);
		if (get_time() - philo->last_meal_time > (uint64_t)data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			if (!data->death_reported) // Vérifie si la mort a déjà été signalée
			{
				display_state(philo, DIED, "\033[031m", data->start_time);
				data->death_reported = 1;
				data->simulation_active = 0;
			}
			pthread_mutex_unlock(&data->print_mutex);
			break;
		}

		if(philo->id % 2 == 0)
		{
			pthread_mutex_lock(&data->forks[right_fork]);
			pthread_mutex_lock(&data->forks[left_fork]);
		}
		else
		{
			pthread_mutex_lock(&data->forks[left_fork]);
			pthread_mutex_lock(&data->forks[right_fork]);
		}
		if (!data->simulation_active) // Vérifie avant de manger
        	break;
		if(get_time() - philo->last_meal_time > (uint64_t)data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			display_state(philo, DIED, "\033[031m", data->start_time);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_unlock(&data->forks[left_fork]);
			pthread_mutex_unlock(&data->forks[right_fork]);
			break;
		}
		pthread_mutex_lock(&data->print_mutex);
		display_state(philo, TAKE_FORKS, "\033[036m", data->start_time);
		display_state(philo, TAKE_FORKS, "\033[036m", data->start_time);
		display_state(philo, EATING, "\033[032m", data->start_time);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&data->print_mutex);

		usleep(data->time_to_think * 1000);

		pthread_mutex_unlock(&data->forks[left_fork]);
		pthread_mutex_unlock(&data->forks[right_fork]);

		if (!data->simulation_active) // Vérifie avant de dormir
        	break;
		pthread_mutex_lock(&data->print_mutex);
		display_state(philo, SLEEPING, "\033[033m", data->start_time);
		pthread_mutex_unlock(&data->print_mutex);

		usleep(data->time_to_eat * 1000);

		if (!data->simulation_active) // Vérifie avant de penser
        	break;
		pthread_mutex_lock(&data->print_mutex);
		display_state(philo, THINKING, "\033[095m", data->start_time);
		pthread_mutex_unlock(&data->print_mutex);

		philo->meals_eaten++;
		if(philo->meals_eaten >= data->nb_eat)
			break;
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
		printf("\n\033[030m******life of %d philos*****\033[0m\n\n", data->nb_philo);
		while (i < data->nb_philo)
		{
			if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
			{
				fprintf(stderr, "Error creating thread for philosopher %d\n", philo[i].id);
				return (0);
			}
			i++;
		}
		if (pthread_create(&data->supv_thr, NULL, supervisor_routine, data) != 0)
        {
            printf("Error creating supervisor thread\n");
            return (0);
        }
		if(pthread_join(data->supv_thr, NULL) != 0)
		{
			fprintf(stderr, "Error joining supervisor thread\n");
			return (0);
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
