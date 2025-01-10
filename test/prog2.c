#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>



/*
Précautions à Prendre
Annulation asynchrone peut être risquée :

Le thread peut être annulé à tout moment, ce qui peut laisser
 des ressources partagées dans un état incohérent.
Privilégiez l'annulation différée avec pthread_testcancel 
et routines de nettoyage.
Nettoyage :

Si le thread utilise des ressources dynamiques 
(malloc, fichiers, etc.), utilisez une routine de 
nettoyage avec pthread_cleanup_push et pthread_cleanup_pop.
*/

void *ft_routine1(void *arg)
{
    // Active l'annulation asynchrone
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    while (1)
    {
        // Boucle infinie, annulable immédiatement
    }
    pthread_exit(arg);
}

int main()
{
    pthread_t t1;

    // Crée un thread
    pthread_create(&t1, NULL, ft_routine1, NULL);

    // Annule le thread
    pthread_cancel(t1);

    // Attend que le thread se termine
    pthread_join(t1, NULL);

    printf("Thread annulé et terminé correctement.\n");

    return 0;
}
