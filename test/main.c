#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void	*ft_routine1(void *arg)
{
	int i;
	char *msg = (char *)arg;

	i = 0;
	while (i < 10)
	{
		printf("\033[091m%s\033[0m\n", msg);
		i++;
	}
	usleep(10000);
	pthread_exit(arg);
}

void	*ft_routine2(void *arg)
{
	int i;
	char *msg = (char *)arg;

	i = 0;
	while (i < 10)
	{
		printf("\033[092m%s\033[0m\n", msg);
		i++;
		
	}
	usleep(10000);
	pthread_exit(arg);
}

int main ()
{
	pthread_t t1;
	pthread_t t2;
	int	i;
	char	*s1;
	char	*s2;
	char *msg1 = strdup("Bonjour 1");
    char *msg2 = strdup("Au revoir 2");

	pthread_create(&t1, NULL, ft_routine1, msg1);
    pthread_create(&t2, NULL, ft_routine2, msg2);

    pthread_join(t1, (void **)&s1);
    pthread_join(t2, (void **)&s2);

    printf("%s %s\n", s1, s2);

    // Libérer la mémoire dynamique
    free(msg1);
    free(msg2);

    return 0;
}