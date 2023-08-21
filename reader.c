/**
 * Sistemas Operativos I - Práctica 3
 *
 *  - Oriol Arderiu Canal
 *  - Joan Català Mas
 *  - Joan Martorell Coll
 */

//Librerías
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "my_lib.h"

//Variables
FILE *file;
static struct my_stack *stack;

int main(int args, char *argv[]) {

    //Guardamos nombre del fichero
    char *nombre = argv[1];

    //Si hay nombre
    if(nombre) {

        stack = my_stack_read(nombre);

        //Pila inexistente
        if(stack == NULL) {
            fprintf(stderr, "Couldn't open stack file %s\n", nombre);
            return -1;
        }

        printf("Stack length: %i\n", my_stack_len(stack));

        //declaramos variables
        int items = 0, sum = 0, 
            min = INT_MAX, max = 0;

        //Leemos los datos
        int *data = malloc(sizeof(int));
        while(my_stack_len(stack) > 0 && items < 10) {
            data = malloc(sizeof(int));
            data = my_stack_pop(stack);
            printf("%i \n", *data);

            items++;
            sum += *data;

            if(min > *data) {
                min = *data;
            }

            if(max < *data) {
                max = *data;
            }
        }

        printf("Items: %i Sum: %i Min: %i Max: %i Average: %i\n", items, sum, min, max, sum/items);


    } else {
        fprintf(stderr, "USAGE: ./reader <stack_file>\n");
    }

    return 1;
}