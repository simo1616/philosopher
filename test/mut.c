#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void	*ft_routine1(void *data)
{
	int i;
	char *msg = "Hello world!";

	i = 0;
	pthread_mutex_lock(&mutex);
	while (i < 13)
	{
		printf("%c", msg[i]);
		usleep(10000);
		i++;
	}
	pthread_mutex_unlock(&mutex);
	//usleep(10000);
	pthread_exit(data);
}

void	*ft_routine2(void *data)
{
	int i;
	char *msg = "Good Bye!";

	i = 0;
	pthread_mutex_lock(&mutex);
	while (i < 11)
	{
		printf("%c", msg[i]);
		usleep(10000);
		i++;
		
	}
	pthread_mutex_unlock(&mutex);
	//usleep(10000);
	pthread_exit(data);
}

int main ()
{
	pthread_t t1;
	pthread_t t2;
	int	i;

	pthread_create(&t1, NULL, ft_routine1, NULL);
    pthread_create(&t2, NULL, ft_routine2, NULL);
	pthread_mutex_destroy(&mutex);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
	printf("\n");
    return 0;
}