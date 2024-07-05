#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

/*
#La estructura principal es un arreglo dinamico a punteros
	Contiene:
		*El arreglo a punteros
		*La minimia prioridad permitida
		*El tamaño de la cola que forma el arreglo
		
#Invariante: 
	Se debe respetar en todo momento:
		*El tipo s_pqueue no puede ser NULL
		*El tamaño de la cola debe ser equivalente a la 
			cantidad de nodos
		*Si el tamaño es 0, el arreglo no debe tener nodos
		*No debemos chequear relacion de orden pues esta 
			dada por los indices
*/

struct s_pqueue {
    struct s_node **array;
    priority_t min_priority;
    unsigned int size;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}

static bool invrep(pqueue q) {
    
    bool b = true;
    
    // q no puede ser NULL
    if(q == NULL){
        b = false;
    }  
    // Si q->size > 0 entonces la cantidad de nodos es igual a size
    if(q->size > 0){
        unsigned int counter = 0u;
        struct s_node *current_node = NULL;
        for(unsigned int i = 0; i <= q->min_priority; i++){
            current_node = q->array[i];
            while(current_node != NULL){
                current_node = current_node->next;
                counter++;
            }
        }
        if(counter != q->size){
            b = false;
        }
    } 
    return b;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q = NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->array = calloc(min_priority+1, sizeof(struct s_node));
    q->size = 0;
    q->min_priority = min_priority;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    // tengo una cola q
    // tengo un elemento e
    // tengo una prioridad
    /*  
      Antes de ver caso por caso, la prioridad debe ser una prioridad valida. 
      Es decir, que este dentro de la capacidad del arreglo para almacenarla
    
      caso 1: la cola es vacia, por lo tanto, debo agregar el nuevo nodo con e
		en la posicion de la prioridad VALIDA
      caso 2: la cola no es vacia, debo agregar mi nuevo nodo AL FINAL de la cola en 
		la posicion de la prioridad VALIDA
      		caso sub2: la cola no esta vacia pero la prioridad esa si
    */
    
    // Verificamos que la prioridad sea valida
    assert(priority <= q->min_priority);
    
    // Listo, creamos el nuevo nodo
    struct s_node *new_node = NULL;
    new_node = create_node(e);
    
    // Encolamos por casos, caso 1:
    if(pqueue_is_empty(q)){
        q->array[priority] = new_node;
        new_node->next = NULL;
    }
    // La cola no es vacia
    else{
        // No hay elementos con esa prioridad
        if(q->array[priority] == NULL){
             q->array[priority] = new_node;
             new_node->next = NULL;
        // Si hay elementos previos, debemos agregar el nuevo nodo alfinal de la cola
        }
        else{
            struct s_node *current_node = q->array[priority];
            while(current_node->next != NULL){
                current_node = current_node->next;
            }
            current_node->next = new_node;
            new_node->next = NULL;
        }
    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    /* El elemento con mayor prioridad es aquel que esta en la primer posicion
 	distinta de NULL dentro de los limites del arreglo, luego ya
  	en esta posicion, el elemento con mas prioridad es el primero pues 
 	desencolamos de esa manera
    */
    struct s_node *node = NULL;
    for(unsigned int i = 0; i <= q->min_priority; i++){
        node = q->array[i];
        if(node != NULL){
            break;
        }
    }
    return node->elem;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
   /*
	Nuevamente, el elemento con mayor prioridad esta en la primer
	posicion distinta de null, entonces la idea es recorrer todo el arreglo
	y la primera que tenga una posicion distinta de null es la que debemos retornar
   */
    priority_t result;
    unsigned int i = 0u;
    while(i <= q->min_priority){
        if(q->array[i] != NULL){
            result = i;
            break;
        }
        i++;
    }
    return result;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    /* 
    	Separamos en casos:
    		Idea: La maxima prioridad son las primeras posiciones del arreglo
    		por lo que debemos recorrerlo y cuando encontremos la prioridad que necesitamos
    		eliminamos el primer nodo que tiene la prioridad, de esa forma estamos desencolando
		de forma normal. 
		Caso 1: no hay casos? simplemente es recorrer xd y desencolar el primero
     */
    bool b = true;
    unsigned int i = 0u;
    while(i <= q->min_priority && b){
        if(q->array[i] != NULL){
            struct s_node *node = q->array[i];
            q->array[i] = node->next;
            node = destroy_node(node);
            b = false;
            q->size--;
        }
        i++;
    }
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    /* Antes de liberar la estructura princial, debemos recorrer el arreglo
	y liberar cada nodo sus posiciones. 
    */
    // Si es vacia, de igual forma se le asigno memoria
    if(!pqueue_is_empty(q)){
        unsigned int i = 0u;
        while(i <= q->min_priority){
            if(q->array[i] != NULL){
                struct s_node *current = q->array[i];
                struct s_node *killme = NULL;
                while(current != NULL){
                    killme = current;
                    current = current->next;
                    killme = destroy_node(killme);
                    killme = NULL;
                }
            }
        i++;
        }
    }
    free(q->array);
    free(q);
    q = NULL;
    return q;
}

