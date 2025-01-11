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

int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        fprintf(stderr, "Usage: ./philo [# Philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ([nb_eat])\n");
        return (1);
    }

    t_data data;
    t_philo *philo;

    philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    if (!philo)
    {
        fprintf(stderr, "Error: Failed to allocate memory for philosophers\n");
        return (1);
    }

    if (!init_data(&data, philo, av))
    {
        free(philo);
        return (1);
    }

    init_philo(philo, &data);

    if (!ft_thread(philo, &data, ac))
    {
        free_resources(&data, philo);
        return (1);
    }

    free_resources(&data, philo);
    return (0);
}

