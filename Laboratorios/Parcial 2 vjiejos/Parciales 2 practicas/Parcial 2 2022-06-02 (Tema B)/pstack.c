#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

/*
	Consideraciones:
		Un elemento con mayor prioridad sera desapilado antes
		Si dos elementos tienen la misma prioridad, se sigue el orden normal
		Se implementa utilizando listas enlazadas
	Estructura principal:
		#Puntero a nodos
			* Los nodos tienen los campos elemento/prioridad/siguiente nodo
		#Comportamiendo
			* pstack es LIFO, pero para apilar y desapilar elementos debemos
			fijarnos en la prioridad, siendo 0 la prioridad mas baja (fondo de la pila) y la
			prioridad mas alta es el nodo en el tope de la pila. Entonces para desapilar debe ser siempre del
			tope, pero para apilar debemos tener cuidado con ubicarlo en su prioridad.
		# invrep: 
			*La propiedad fundamental es que, desde el tope hasta el fondo de la pila debe respetarse que 
			la mayor prioridad del nodo del tope (numericamente) es mayor a la prioridad
			del siguiente nodo  
			*Caso base: cuando es vacio, el nodo debe apuntar a NULL
				
*/

struct s_pstack {
    struct s_node *front;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    priority_t prio;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->prio = priority;
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


static bool invrep(pstack s) {
    // La pila no puede ser NULL
    if (s == NULL) {
        return false;
    }
    
    // Caso base: pila vacía
    if (pstack_is_empty(s)) {
        return s->front == NULL && s->size == 0;
    }

    // Caso general: pila no vacía
    bool b = true;
    unsigned int counter = 0u;
    struct s_node *node = s->front;
    
    while (node != NULL && node->next != NULL && b) {
        if (node->prio < node->next->prio) {
            b = false;
        }
        node = node->next;
        counter++;
    }
    
    // Ultimo nodo en caso de que se cumpla
    counter++;

    // Verifico tamaño correcto
    b = b && (counter == s->size);
    
    return b;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    assert(s != NULL);
    s->front = NULL;
    s->size = 0u;
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);

    if (pstack_is_empty(s)) {
        s->front = new_node;
    } else {
        if (new_node->prio >= s->front->prio) {
            // Insertar al principio si la prioridad es mayor o igual que la del primer nodo
            new_node->next = s->front;
            s->front = new_node;
        } else {
            // Caso general: insertar en la posición adecuada en base a la prioridad
            struct s_node *node = s->front;
            while (node->next != NULL && new_node->prio < node->next->prio) {
                node = node->next;
            }
            // Insertar new_node en la posición encontrada
            new_node->next = node->next;
            node->next = new_node;
        }
    }

    s->size++;
    return s;
}

bool pstack_is_empty(pstack s) {
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(!pstack_is_empty(s) && invrep(s));
    return s->front->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(!pstack_is_empty(s) && invrep(s));
    return s->front->prio;
}

unsigned int pstack_size(pstack s) {
    unsigned int size=0;
    size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    // Debemos quitar el tope sin más
    struct s_node *killme = s->front;
    s->front = s->front->next;
    killme = destroy_node(killme);
    killme = NULL;
    s->size--;
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *temp = s->front;
    struct s_node *killme = NULL;
    while(temp != NULL){
        killme = temp;
        temp = temp->next;
        killme = destroy_node(killme);
        killme = NULL;
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

