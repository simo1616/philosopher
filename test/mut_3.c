#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
int signal = 0;

pthread_t main_thread; // Identifiant du thread principal

void *ft_routine1(void *data)
{
    printf("Thread 1 ID: %lu is starting\n", pthread_self());

    pthread_mutex_lock(&mutex);
    while (signal != 2)
        pthread_cond_wait(&cond2, &mutex);
    pthread_mutex_unlock(&mutex);

    char *msg = "Hello world!";
    int i = 0;
    while (i < 13) // Boucle while à la place de for
    {
        printf("%c", msg[i]);
        usleep(10000);
        i++;
    }
    printf("\n");

    if (pthread_equal(pthread_self(), main_thread))
    {
        printf("Thread 1 is the main thread\n");
    }
    else
    {
        printf("Thread 1 is NOT the main thread\n");
    }

    pthread_exit(data);
}

void *ft_routine2(void *data)
{
    printf("Thread 2 ID: %lu is starting\n", pthread_self());

    char *msg = "Good Bye!";
    int i = 0;
    while (i < 10) // Boucle while à la place de for
    {
        printf("%c", msg[i]);
        usleep(10000);
        i++;
    }
    printf("\n");

    pthread_mutex_lock(&mutex);
    signal = 1;
    pthread_cond_signal(&cond1);
    pthread_mutex_unlock(&mutex);

    pthread_exit(data);
}

void *ft_routine3(void *data)
{
    printf("Thread 3 ID: %lu is starting\n", pthread_self());

    pthread_mutex_lock(&mutex);
    while (signal != 1)
        pthread_cond_wait(&cond1, &mutex);
    pthread_mutex_unlock(&mutex);

    char *msg = "Deuxieme pos";
    int i = 0;
    while (i < 13) // Boucle while à la place de for
    {
        printf("%c", msg[i]);
        usleep(10000);
        i++;
    }
    printf("\n");

    pthread_mutex_lock(&mutex);
    signal = 2;
    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&mutex);

    pthread_exit(data);
}

int main()
{
    pthread_t t1, t2, t3;

    main_thread = pthread_self(); // Stocke l'identifiant du thread principal

    pthread_create(&t1, NULL, ft_routine1, NULL);
    pthread_create(&t2, NULL, ft_routine2, NULL);
    pthread_create(&t3, NULL, ft_routine3, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);

    return 0;
}
