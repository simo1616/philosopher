#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void	*ft_routine1(void *arg)
{
	int i;

	i = 0;
	printf("fonction ft_routine1 a commencer.\n");
	while (1)
	{
		printf("iteration #%d\n", i+1);
		pthread_testcancel();
		i++;
		usleep(1000);
	}
	printf("fonction ft_routine1 a fini.\n");
	pthread_exit(arg);
}

int main ()
{
	pthread_t t1;

	pthread_create(&t1, NULL, ft_routine1, NULL);
	pthread_cancel(t1);
    pthread_join(t1, NULL);
	printf("Thread annulé et terminé correctement.\n");
    return 0;
}