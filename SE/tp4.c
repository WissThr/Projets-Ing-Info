/*#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> // for exit()

pthread_t pthread_id[3]; // Array to store pthread IDs

void f(int i) {
    int j = 0, k = 0;
    for (j = 0; j < 3; j++) {
        for (k = 0; k < 100000; k++);
        printf("pthread de numero %lu, j=%d\n", pthread_self(), j); // Using pthread_self() to get pthread ID
        fflush(stdout);
    }
}

int main() { // corrected: changed "main()" to "int main()"
    int i;
    for (i = 0; i < 3; i++) {
        if (pthread_create(&pthread_id[i], NULL, (void *)f, (void *)i) == -1) { // corrected: changed "&pthread_id+i" to "&pthread_id[i]"
            fprintf(stderr, "Erreur creation pthread numero %d\n", i);
            exit(2);
        }
    }
    printf("Je suis la pthread initiale du processus et j’ai comme numero %lu\n", pthread_self()); // Using pthread_self() to get pthread ID
    printf("Je suis la pthread initiale et je me termine \n");
    pthread_exit(NULL); // corrected: added pthread_exit(NULL) to wait for other threads to finish before main exits
    return 0;
}*/

/*#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // pour getpid()

void *thread_function(void *arg) {
    pthread_t tid = pthread_self(); // Récupérer l'ID du thread
    pid_t pid = getpid(); // Récupérer l'ID du processus

    printf("Thread ID: %lu, Process ID: %d\n", tid, pid);

    return NULL;
}

int main() {
    pthread_t thread_id[3];
    int i;

    // Créer les threads
    for (i = 0; i < 3; i++) {
        if (pthread_create(&thread_id[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    // Attendre que les threads se terminent
    for (i = 0; i < 3; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}*/

/*#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> // for exit()

#define NUM_THREADS 5

void *tache(void *arg) {
    if (arg == NULL) {
      //  fprintf(stderr, "Argument nul passé au thread.\n");
        pthread_exit(NULL);
    }

    int num_thread = *((int *)arg); // Cast du pointeur en int
    pthread_t tid = pthread_self(); // Récupérer l'ID du thread

    for (int i = 0; i < 10000; i++); // Boucle vide de 10000 étapes

    printf("Numéro : %d, ID du thread : %lu\n", num_thread, tid);

    free(arg); // Libérer la mémoire allouée dynamiquement pour l'argument du thread

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    // Créer les threads
    for (i = 0; i < NUM_THREADS; i++) {
        int *thread_arg = malloc(sizeof(int)); // Allouer de la mémoire pour l'argument du thread
        if (thread_arg == NULL) {
            perror("malloc");
            return 1;
        }
        *thread_arg = i + 1; // Assigner un argument unique à chaque thread
        if (pthread_create(&threads[i], NULL, tache, (void *)thread_arg) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    // Exécuter la tâche pour le thread initial
    tache((void *)0);

    // Attendre que tous les threads se terminent
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}*/

/*#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // pour fork()

void *lecture(void *arg) {
    char buffer[100];
    printf("Thread de lecture créé (TID : %lu, PID : %d)\n", pthread_self(), getpid());
    printf("Veuillez saisir quelque chose : ");
    fgets(buffer, sizeof(buffer), stdin);
    printf("Vous avez saisi : %s\n", buffer);
    return NULL;
}

void *forking(void *arg) {
    printf("Thread de fork créé (TID : %lu, PID : %d)\n", pthread_self(), getpid());
    printf("Création d'un nouveau processus par fork...\n");
    pid_t child_pid = fork();
    if (child_pid == 0) {
        printf("Processus fils créé (PID : %d)\n", getpid());
    } else if (child_pid > 0) {
        printf("Processus parent (PID : %d)\n", getpid());
    } else {
        printf("Erreur lors de la création du processus fils.\n");
    }
    return NULL;
}

int main() {
    pthread_t thread_lecture, thread_fork;
    pthread_create(&thread_lecture, NULL, lecture, NULL);
    pthread_create(&thread_fork, NULL, forking, NULL);
    pthread_join(thread_lecture, NULL);
    pthread_join(thread_fork, NULL);
    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3 // Nombre de lignes de la première matrice
#define M 3 // Nombre de colonnes de la première matrice (et de lignes de la deuxième matrice)
#define P 3 // Nombre de colonnes de la deuxième matrice

int A[N][M] = { {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9} };

int B[M][P] = { {1, 0, 0},
                {0, 1, 0},
                {0, 0, 1} };

int C[N][P]; // Matrice résultante

// Structure pour passer les arguments au thread
typedef struct {
    int row;
    int col;
} thread_args;

// Fonction exécutée par chaque thread
void *multiply(void *arg) {
    thread_args *args = (thread_args *)arg;
    int row = args->row;
    int col = args->col;

    int sum = 0;
    for (int i = 0; i < M; i++) {
        sum += A[row][i] * B[i][col];
    }

    C[row][col] = sum;

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N][P];
    thread_args args[N][P];
    printf("mat A\n");
for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", A[i][j]);
            
        }
        printf("\n");
    }
    printf("mat B\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", B[i][j]);
            
        }
        printf("\n");
    }
    // Créer un thread pour chaque élément de C
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            args[i][j].row = i;
            args[i][j].col = j;
            if (pthread_create(&threads[i][j], NULL, multiply, (void *)&args[i][j]) != 0) {
                perror("pthread_create");
                return 1;
            }
        }
    }

    // Attendre que tous les threads se terminent
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Afficher la matrice résultante
    printf("Matrice résultante C : \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}





