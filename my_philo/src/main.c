# include "philo.h"

void	init_data(t_data *data, char **av)
{
	data = (t_data *)malloc(av[5])
	data.id = 1;
	data.start_time = get_timestamp();
}

int main (int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philos [# Philosophers] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep] ([times_each_philosopher_must_eat])\n");
		return(0);
	}

	t_args	args;
	t_data *data;
	int i;
	

	init_data(data, av);
	init_arg()
	
	i = 0;
	if
	while(i < atoi(av[5]))
	{
		display_state(data, "thinking", "\033[095m");
		usleep(THINK_TIME);
		display_state(data, "eating", "\033[032m");
		usleep(EAT_TIME);
		display_state(data, "sleeping", "\033[033m");
		usleep(SLEEP_TIME);
		i++;
	}
	return(0);
}