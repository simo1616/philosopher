# include "philo.h"

void	ft_exit(t_data *data)
{
	free(data);
	exit(1);
}

int error(char *str, t_data *data)
{
	printf("%s", str);
	if (data)
		ft_exit(data);
	return (1);
}

void init_data(t_data *data, char **av)
{
    data->nb_philo = atoi(av[1]);
    data->time_to_die = atoi(av[2]);
    data->time_to_eat = atoi(av[3]);
    data->time_to_sleep = atoi(av[4]);
	data->nb_eat = atoi(av[5]);
    data->time_to_think = 0;
	data->start_time = get_time();
}

void init_philo(t_philo *philo, char **av)
{
    int i;
	int j;

    
	j = 0;
	if(av[5])
	{
		while (j < atoi(av[5]))
		{
			i = 0;
			while (i < atoi(av[1]))
			{
				philo[i].id = i + 1;
				i++;
			}
			j++;
		}
	}
	else
	{
		i = 0;
		while (i < atoi(av[1]))
		{
			philo[i].id = i + 1;
			i++;
		}
	}
}

int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        printf("Usage: ./philos [# Philosophers] [time_to_die] ");
        printf("[time_to_eat] [time_to_sleep] ([times_each_philosopher_must_eat] *fac ([nb_eat]))\n");
        return (0);
    }

    t_data  data;
    t_philo *philo;
    int i;
	int j;

    philo = malloc(sizeof(t_philo) * atoi(av[1]));
    if (!philo)
        return (1);
    init_philo(philo, av);
    init_data(&data, av);

    i = 0;
	
    if (ac == 6)
    {
		j = 0;
		while (j < data.nb_eat)
		{
			i = 0;
			printf("\n**************iteration = %d****************\n", j + 1);
			while (i < data.nb_philo)
			{
				printf("\n-----Philo  #%d------\n", i + 1);
				display_state(philo, "thinking", "\033[095m", i, data.start_time);
				usleep(data.time_to_think * 1000);
				display_state(philo, "eating", "\033[032m", i, data.start_time);
				usleep(data.time_to_eat * 1000);
				display_state(philo, "sleeping", "\033[033m", i, data.start_time);
				usleep(data.time_to_sleep * 1000);
				i++;
			}
			j++;
		}
    }
	else
	{
		i = 0;
		while (i < data.nb_philo)
		{
			printf("\n-----Philo  #%d------\n", i + 1);
			display_state(philo, "thinking", "\033[095m", i, data.start_time);
			usleep(data.time_to_think * 1000);
			display_state(philo, "eating", "\033[032m", i, data.start_time);
			usleep(data.time_to_eat * 1000);
			display_state(philo, "sleeping", "\033[033m", i, data.start_time);
			usleep(data.time_to_sleep * 1000);
			i++;
		}
	}
    free(philo);
	//free(data);
    return (0);
}
