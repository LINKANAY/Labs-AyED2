#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

/*
	Consideraciones:
		#Cada elemento esta asociado a una prioridad asignada
		#Un elemento con mayor prioridad sera desencolado primero
		#Si dos elementos tienen la misma prioridad se desencolan 
			siguiendo el orden de la cola

	Estructura principal:
		#Contiene un puntero a nodos front y size  
		#Nodos: cada uno tiene un elemento, la prioridad del
			elemento y un nodo al siguiente
	Prioridades:
		#La mayor prioridad es 0 y numeros más grandes establecen
			prioridades más bajas
		#En los nodos seria p1 ≤ p2 ≤ … ≤ pN --> 0 < 1 < 2 < 3 < 4
		#Si siempre se usa la misma prioridad la cola funciona como 
			siempre (first input, first output)
	Invrep:
		#En todo momento, size debe representar la cantidad de nodos
			encolador
		#Se debe respetar el orden se las prioridades
		#Si es una cola vacia size debe ser 0

*/



struct s_pqueue {
    struct s_node *front;
    unsigned int size;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    
    // q no puede ser NULL
    if(q == NULL){
        return false;
    }
    
    bool b = true;
    unsigned int counter = 0u;
    
    // caso q es vacio
    if(pqueue_is_empty(q)){
        return (q->size == 0) && (q->front == NULL);
    }
    // caso q no es vacio
    else{
        struct s_node *node = q->front;
        while(node != NULL && node->next != NULL && b){
            if(node->priority > node->next->priority){
                b = false;
            }
            node = node->next;
            counter++;
        }
        counter++;
    }
    
    b = b && (counter == q->size);
    return b;
}

pqueue pqueue_empty(void) {
    pqueue q = NULL;
    q = malloc(sizeof(struct s_pqueue));
    assert(q != NULL);
    q->front = NULL;
    q->size = 0u;
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    
    // caso q es vacio
    if(pqueue_is_empty(q)){
        q->front = new_node;
    }
    // caso general
    else{
    	// En caso de que sea de mayor prioridad que el primer nodo
        if(new_node->priority < q->front->priority){
            new_node->next = q->front;
            q->front = new_node;
        }
        // Caso general
        else{
            bool b = true;
            struct s_node *node = q->front;
            while(node->next != NULL && new_node->priority >= node->next->priority && b){
                node = node->next;
            }
            // Insertar el nuevo nodo en la posicion encontrada
            new_node->next = node->next;
            node->next = new_node;
        }
    }
    q->size++;
    return q;
}

bool pqueue_is_empty(pqueue q) {
    return q->size == 0u;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(!pqueue_is_empty(q) && invrep(q));
    return q->front->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(!pqueue_is_empty(q) && invrep(q));
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size=0;
    size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    // Si enqueue esta bien implementado, esto es equivalente a desencolar normalmente
    struct s_node *killme = NULL;
    killme = q->front;
    q->front = q->front->next;
    killme = destroy_node(killme);
    killme = NULL;  
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *killme = NULL;
    struct s_node *current = NULL;
    current = q->front;
    while(current != NULL){
    killme = current;
    current = current->next;
    killme = destroy_node(killme);
    killme = NULL;
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
