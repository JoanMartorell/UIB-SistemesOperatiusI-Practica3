/**
 * Sistemas Operativos I - Práctica 3
 *
 *  - Oriol Arderiu Canal
 *  - Joan Català Mas
 *  - Joan Martorell Coll
 */

// Librerías
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_lib.h"

// Constantes
#define NUM_THREADS 10
#define N 1000000

//Funciones
struct my_stack *iniciar_stack(char *file);
void *worker(void *ptr);
void *mostrar_stack();

//Variables
static struct my_stack *stack;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int args, char *argv[]) {

    //Guardamos nombre del fichero
    char *nombre = argv[1];

    //Si hay nombre
    if(nombre) {

        printf("Threads: %i, Iterations: %i\n", NUM_THREADS, N);

        stack = iniciar_stack(nombre);

        //Identificadores de los hilos
        pthread_t hilos[NUM_THREADS];

        for(int i = 0; i < NUM_THREADS; i++) {
            pthread_create(&hilos[i], NULL, worker, NULL);
            printf("%i) Thread %lu created \n", i, hilos[i]);
        }

        //Esperar a que los hilos acaben
        for(int i = 0; i < NUM_THREADS; i++) {
            pthread_join(hilos[i], NULL);
        }

        printf("\nstack content after threads iterations:\n");
        mostrar_stack();
        printf("stack length: %d\n", my_stack_len(stack));

        //Guardar pila en fichero
        int elementos = my_stack_write(stack, argv[1]);
        int eliminados = my_stack_purge(stack);
        
        printf("\nWritten elements from stack to file: %d\n", elementos);
        printf("Released bytes: %d\n", eliminados);
        printf("Bye from main\n");

        pthread_exit(0);

    } else {
        fprintf(stderr, "USAGE: ./stack_counters <stack_file>\n");
    }

    return 1;
}

/**
 * Inicialización de la pila
 */
struct my_stack *iniciar_stack(char *file) {
    
    stack = my_stack_read(file);

    //Si la pila no existe
    if(stack == NULL) {
        stack = my_stack_init(sizeof(int));
        printf("stack->size: %ld\n", sizeof(int));
        printf("initial stack length: %i\n", my_stack_len(stack));
        printf("initial stack content:\n");
        printf("stack content for treatment:\n");

        int *data = malloc(sizeof(int));

        // Rellenamos la pila hasta NUM_THREADS
        while(my_stack_len(stack) < NUM_THREADS) {
            data = malloc(sizeof(int));
            *data = 0;
            my_stack_push(stack, data);
        }

        mostrar_stack();
        printf("new stack lenght: %d\n\n", my_stack_len(stack));

        return stack;

    }
    
    //LA PILA EXISTE:

    // Si < 10: rellenar los restantes
    if(my_stack_len(stack) < NUM_THREADS) {

        printf("initial stack length: %i\n", my_stack_len(stack));
        printf("original stack content:\n");
        mostrar_stack();

        int i = 0;
        int *data = malloc(sizeof(int));

        // Rellenamos la pila hasta NUM_THREADS
        while(my_stack_len(stack) < NUM_THREADS) {
            data = malloc(sizeof(int));
            *data = 0;
            my_stack_push(stack, data);
            i++;
        }

        printf("\nNumber of elements added to inital stack: %i\n", i);
        printf("stack content for treatment:\n");
        mostrar_stack();
        printf("stack lenght: %i\n\n", my_stack_len(stack));

        return stack;

    } 
    
    //PILA CON MÁS DE 10 ELEMENTOS
    printf("original stack content:\n");
    mostrar_stack();
    printf("original stack length: %i\n\n", my_stack_len(stack));

    return stack;
}

/**
 * Función que ejecuta cada hilo
 */
void *worker(void *ptr) {

    for(int i = 0; i < N; i++) {

        //Sección obtener TOS
        pthread_mutex_lock(&mutex);

        //printf("Soy el hilo %ld ejecutando pop\n", pthread_self());

        int *data = my_stack_pop(stack);
        pthread_mutex_unlock(&mutex);

        (*data)++; //Sumamos 1

        ////Sección metemos TOS
        pthread_mutex_lock(&mutex);
        
        //printf("Soy el hilo %ld ejecutando push\n", pthread_self());

        my_stack_push(stack, data);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

/**
 * Función que muestra el Stack
 */
void *mostrar_stack() {

    struct my_stack *auxStack = my_stack_init(sizeof(int));

    //Vemos contenido del stack
    int *data = malloc(sizeof(int));
    while(my_stack_len(stack) > 0) {
        data = malloc(sizeof(int));
        data = my_stack_pop(stack);

        printf("%i \n", *data);

        my_stack_push(auxStack, data);
    }

    //Lo ponemos como estaba
    while(my_stack_len(auxStack) > 0) {
        my_stack_push(stack, my_stack_pop(auxStack));
    }

    return 0;
}