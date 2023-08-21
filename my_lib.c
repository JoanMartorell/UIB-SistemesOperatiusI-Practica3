#include "my_lib.h"

/*
 * Miembros: 
 *   - Joan Català Mas
 *   - Oriol Arderiu Canal
 *   - Joan Martorell Coll
 *
 * Nota: para la función my_stack_write hemos creado una función auxiliar "my_stack_node_write"
 * la cual está declarada también en my_lib.h, por ello la incluimos en el directorio a entregar.
 * 
*/

/*
 * R1, F1: my_strlen
 ---------------------------------------------------------
 * calcula el nº de bytes de la cadena str
 * str: puntero a la cadena a encontrar la longitud
 * returns: devuelve la longitud de la cadena str. No devuelve error.
*/
size_t my_strlen(const char *str){
  size_t len =0;
  for (len =0; str[len] != '\0';len++){
  }
  
  return len;
}

/*
 * R1, F2: my_strcmp
 ---------------------------------------------------------
 * Compara las cadenas str1 y str2
 * str1: puntero a la cadena a comparar
 * str2: puntero a la cadena a comparar
 * returns: devuelve un entero. -1 -> str1<str2
 *                               0 -> str1=str2
 *                               1 -> str1>str2
*/
int my_strcmp(const char *str1, const char *str2){
    //-1 si str1<str2
    //0 si son iguales
    //1 si str1>str2
    int longStr1 = sizeof(*str1);
    int longStr2 = sizeof(*str2);
    //mirar longitudes de los trings, si hay una mas largo que el otro ya sabemos que no son iguales
    if (longStr1 == longStr2){//si son iguales comprovamos el mas grande
        for (int i =0;str1[i] !='\0';i++){
            if (str1[i]<str2[i]){
                return -1;
            }else if(str1[i]>str2[i]){
                return 1;
            }
        }
        return 0;
    }else if(longStr1 < longStr2){//en caso de que sean de longitud diferente, el mas largo sera mayor
        return -1;
    }else{
        return 1;
    }
}

/*
 * R1, F3: my_strcpy
 ---------------------------------------------------------
 * Copia la cadenas src en dest
 * src: puntero a la cadena a copiar
 * dest: puntero a la cadena destino
 * returns: devuelve el puntero dest. No devuelve error.
*/
char *my_strcpy(char *dest, const char *src) {

  //Guardamos el puntero destino
  char *primero = dest;

  //Recorremos la cadena a copiar
  while(*src != '\0') {
      *dest = *src;   //copiamos el carácter en el destino
      dest++;         //siguiente carácter (1 byte)
      src++;          //siguiente carácter (1 byte)
  }

  *dest = 0;
  return primero;

}

/*
 * R1, F4: my_strncpy
 ----------------------------------------------------------
 * Copia n caracteres de la cadena src en dest
 * src: puntero a la cadena a copiar
 * dest: puntero a la cadena destino
 * n: cantidad de caracteres que se copiarán 
 * returns: devuelve el puntero dest. No devuelve error.
*/
char *my_strncpy(char *dest, const char *src, size_t n) {
  
  //Inicializamos *dest con el carácter nulo
  //memset(dest, 0, sizeof(dest));

  //Recorremos hasta n en src
  for(int i = 0; i < n; i++) {
    
    if(*src != '\0') { //Carácter diferente de '\0'

      *(dest + i) = *(src + i); //copiamos el carácter en el destino
    
    } else { //Carácter igual a '\0'

      *(dest + i) = 0; //guardamos 0s

    }

  }

  return dest;
}

/*
 * R1, F5: my_strcat
 ---------------------------------------------------------
 * Añade la cadena src a dest
 * src: puntero a la cadena a concatenar
 * dest: puntero a la cadena destino
 * returns: devuelve el puntero dest. No devuelve error.
*/
char *my_strcat(char *dest, const char *src)
{

  // Guardem la longitud de dest i src
  //utilitzem my_strlen ja que ens retornen la longitud sense el /0
  int llargadaDest = my_strlen(dest);
  int llargadaSrc = my_strlen(src);
  // posem el 'punter' al final de la cadena destí
  dest += llargadaDest;
  //bucle per anar escribint cada caracter 
  for (int i = 0; i < llargadaSrc; i++)
  {
    *dest = *src;
    src++;
    dest++;
  }
  //posem el 'punter' al principi de la cadena dest
  dest -= llargadaDest - llargadaSrc;
  return dest;
}

/*
 * R1, F6: my_strchr
 ---------------------------------------------------------
 * Busca el primer carácter c en la cadena str
 * str: puntero a la cadena a escanear
 * c: carácter buscado
 * returns: devuelve el puntero a la primera ocurrencia del carácter c. No devuelve error.
*/
char *my_strchr(const char *str, int c){
    //calculem la longitud del array de caracters
    int llargadaStr=my_strlen(str);
    //fem el bucle que passi per a cada caracter del array
    for (int i =0;i<llargadaStr;i++){
        //comparem el caracter i fa el return si son iguals
        if (*(str+i)==c){
            return (char *)(str+i);
        }
    }
    return NULL;
    
}

//###############################################################

/*
 * R2, F1: my_stack_init
 ---------------------------------------------------------
 * Reserva espacio para una variable de tipo struct my_stack
 * size: tamaño de los datos
 * returns: devuelve un puntero a la pila inicializada.
*/
struct my_stack *my_stack_init(int size) {

  //Guardamos espacio para la nueva pila
  struct my_stack *stack = (struct my_stack *) malloc(sizeof(struct my_stack));
  
  //Inicializamos atributos
  stack->size = size;
  stack->top = NULL;
  
  return stack;
}

/*
 * R2, F2: my_stack_push
 ---------------------------------------------------------
 * Inserta un nuevo nodo en los elementos de la pila
 * stack: puntero al struct my_stack
 * data: puntero a los datos de ese nodo
 * returns: devuelve 0 si ha ido bien, -1 si hubo error
*/
int my_stack_push(struct my_stack *stack, void *data) {
  if(stack != NULL && stack->size > 0){
    //Nuevo nodo
    struct my_stack_node *newNode = (struct my_stack_node *)malloc(sizeof(struct my_stack_node));

    //Nuevos datos
    newNode->data = data;
    newNode->next = stack->top;

    //Insertar nuevo nodo en el TOS
    stack->top = newNode;

    //No ha habido errores
    return 0;
    
  } else {
    //Ha habido un error
    return -1;
  }
}

/*
 * R2, F3: my_stack_pop
 * Elimina el TOS
 * stack: puntero a la pila
 * returns: puntero a los datos del nodo. NULL si la pila es vacía
*/
void *my_stack_pop(struct my_stack *stack) {

  if(stack->top != NULL) {

    //Nodo a eliminar
    struct my_stack_node *aux = stack->top;

    //Guardamos el siguiente Nodo en el TOS
    stack->top = aux->next;
    
    //Devolvemos el TOS original
    return aux->data;

  } else {

    //Pila vacía
    return NULL;

  }

}

/*
 * R2, F4: my_stack_len
 * Número de nodos total de la pila
 * stack: puntero a la pila
 * returns: número de nodos de la pila
*/
int my_stack_len (struct my_stack *stack) {

  int n = 0;

  struct my_stack_node *aux = stack->top;

  while(aux != NULL) {
    //Sumamos elemento
    n++;

    //Apuntamos al siguiente elemento
    aux = aux->next;
  }

  return n;
}

/*
 * R2, F5: my_stack_purge
 * Recorre la pila liberando la memoria
 * stack: puntero a la pila
 * returns: devuelve el número de bytes liberados
*/
int my_stack_purge(struct my_stack *stack) {
    //Declaramos los nodos 
    struct my_stack_node *ultimoNodo;
    struct my_stack_node *nodoActual;
    int numBytesLib = 0;

    if (stack->top != NULL) {
        nodoActual = stack->top;

        while(nodoActual != NULL){

            //Elegimos el siguiente nodo
            ultimoNodo = nodoActual;
            nodoActual = nodoActual->next;

            //Liberamos el espacio de data del nodo
            numBytesLib += stack->size;
            free(ultimoNodo->data);

            //Ahora liberamos el espacio del nodo
            numBytesLib += sizeof(struct my_stack_node);
            free(ultimoNodo);
        }
    }
    //Por último, liberamos stack
    numBytesLib += sizeof(struct my_stack_node);
    free(stack);
    
    return numBytesLib;
}

/*
 * R2, F6: my_stack_write
 * Almacena los datos de la pila en el fichero (opción recursiva)
 * stack: puntero a la pila
 * filename: fichero donde se van a almacenar los datos
 * returns: devuelve el número de elementos almacenados, -1 si hubo error
*/
int my_stack_write(struct my_stack *stack, char *filename){

    int f;
    f = creat(filename, O_WRONLY | O_CREAT | O_TRUNC | S_IRUSR | S_IWUSR);

    if (stack->top || f != -1) {

        struct my_stack_node *nodoActual = stack ->top;
        //Escribimos el tamaño de los datos
        write(f, &(stack->size), sizeof(int));
        //Escribimos el contenido de la pila
        int wNodos = my_stack_node_write(nodoActual, f, stack->size);
        close(f);

        return wNodos;
    } else {

        return -1;
    }
}

/*
 * R2, F6: my_stack_write
 * Almacena los datos de la pila en el fichero (función auxiliar)
 * stack: puntero a la pila
 * filename: fichero donde se van a almacenar los datos
 * returns: devuelve el número de elementos almacenados, -1 si hubo error
*/
int my_stack_node_write(struct my_stack_node *nodo, int f, int size) {
    
    if(f != -1) {
        int numNodos = 0;
        if (nodo->next) {
            numNodos = my_stack_node_write(nodo->next, f, size);
        }

        write(f, nodo->data, size);
        numNodos++;

        return (numNodos);
    } else {

        return -1;
    }
}

/*
 * R2, F7: my_stack_read
 * Lee los datos de la pila almacenados en el fichero
 * filename: fichero donde se van a leer los datos
 * returns: nueva pila
*/
struct my_stack *my_stack_read(char *filename) {
     
     int f;
     f = open(filename, O_RDONLY);

     if (f != -1) {

        //Leemos el tamaño de los datos 
        int size;
        read(f, &size, sizeof(size));

        //Inicializamos la pila
        struct my_stack *stack = my_stack_init(size);
        void *data = malloc(size);

        //Leemos los nodos del fichero
        while((read(f,data,size)) > 0) {

            if(data) {

                my_stack_push(stack, data);
                data = malloc(size);
            } else {

                return NULL;
            }
        }

        close (f);
        return stack;
     } else {

        return NULL;
     }
}
