#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t	cond2 = PTHREAD_COND_INITIALIZER;
int	signal = 0;

void	*ft_routine1(void *data)
{
	int i;
	char *msg = "Hello world!";
	pthread_mutex_lock(&mutex); // Verrouille le mutex avant d'attendre
    while (signal != 2)
		pthread_cond_wait(&cond2, &mutex); // Attend le signal de routine2
    pthread_mutex_unlock(&mutex); // Déverrouille le mutex après avoir reçu le signal

	i = 0;
	while (i < 13)
	{
		printf("%c", msg[i]);
		usleep(10000);
		i++;
	}
	printf("\n");
	//usleep(10000);
	pthread_exit(data);
}

void	*ft_routine2(void *data)
{
	int i;
	char *msg = "Good Bye!";

	i = 0;
	while (i < 10)
	{
		printf("%c", msg[i]);
		usleep(10000);
		i++;
	}
	printf("\n");
	//usleep(10000);
	pthread_mutex_lock(&mutex); // Verrouille le mutex avant d'envoyer le signal
    signal = 1;
	pthread_cond_signal(&cond1); // Réveille routine1
    pthread_mutex_unlock(&mutex); // Déverrouille le mutex
	pthread_exit(data);
}

void	*ft_routine3(void *data)
{
	int i;
	char *msg = "Deuxieme pos";
	pthread_mutex_lock(&mutex); // Verrouille le mutex avant d'attendre
    while(signal != 1)
		pthread_cond_wait(&cond1, &mutex); // Attend le signal de routine2
    pthread_mutex_unlock(&mutex); // Déverrouille le mutex après avoir reçu le signal

	i = 0;
	while (i < 13)
	{
		printf("%c", msg[i]);
		usleep(10000);
		i++;
	}
	printf("\n");
	//usleep(10000);
	pthread_mutex_lock(&mutex);
	signal = 2;
	pthread_cond_signal(&cond2);
	pthread_mutex_unlock(&mutex);
	pthread_exit(data);
}

int main ()
{
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	int	i;
	pthread_create(&t1, NULL, ft_routine1, NULL);
    pthread_create(&t2, NULL, ft_routine2, NULL);
	pthread_create(&t3, NULL, ft_routine3, NULL);
	//pthread_mutex_destroy(&mutex);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	printf("\n");
	pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    return 0;
}