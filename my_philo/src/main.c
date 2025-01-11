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
        printf("Usage: ./philos [# Philosophers] [time_to_die] ");
        printf("[time_to_eat] [time_to_sleep] ([times_each_philosopher_must_eat] *fac ([nb_eat]))\n");
        return (0);
    }

    t_data  data;
    t_philo *philo;

    philo = malloc(sizeof(t_philo) * ft_atoi(av[1]) + 1);
    if (!philo)
    {
        printf("Error: Failed to allocate memory for philosophers\n");
        return (1);
    }
    init_data(&data, av);
    init_philo(philo, &data);
    ft_thread(philo, &data, ac);
    free(philo);
    return (0);
}
