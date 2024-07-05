#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"
#include <stdio.h>

struct s_pstack {
    struct s_node **array;  		// Arreglo de punteros a nodo
    priority_t max_priority;  		// Maxima prioridad aceptada
    unsigned int size;
};

struct s_node {
    pstack_elem elem;    	// Valor del nodo
    struct s_node *next; 	// Puntero al siguiente nodo 
};

static bool invrep(pstack ps) {
    if (ps == NULL) {
        return false; // La pila no debe ser NULL
    }

    unsigned int counted_size = 0; // Contador de elementos

    // Verificación de la estructura del arreglo
    for (unsigned int i = 0; i <= ps->max_priority; i++) {
        struct s_node *current = ps->array[i];
        
        while (current != NULL) {
            counted_size++;
            current = current->next;
        }
    }

    // Verificar que el tamaño contado coincida con el tamaño registrado
    if (counted_size != ps->size) {
        return false;
    }

    return true; // Si todas las condiciones se cumplen, la invariante es válida
}

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
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

pstack pstack_empty(priority_t max_priority) {
    pstack s = NULL;
    s = malloc(sizeof(struct s_pstack));			// Asignamos memoria para la estructura principal
    s->array = calloc(max_priority+1, sizeof(struct s_node));	// Asignamos memoria para el arreglo de punteros
    s->max_priority = max_priority;				// Inicializamos max_priority
    s->size = 0;						// Inicializamos size 
    for (unsigned int i = 0u; i <= max_priority; i++) {		// Inicializamos el arreglo en NULL
        s->array[i] = NULL;
    }
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    
    assert(invrep(s));
    assert(priority <= s->max_priority);
    
    struct s_node *new_node = create_node(e); // creamos el nodo
    
    // priority es una posicion, veamos si esta ocupada
    if(s->array[priority] == NULL){ // NO esta ocupada, debemos agregar el nodo
        s->array[priority] = new_node;
        new_node->next = NULL;
    }
    else{  // SI esta ocupada, debemos agregar el nuevo nodo en el tope de la pila ya existente
        new_node->next = s->array[priority];
        s->array[priority] = new_node;
    }
    s->size++;
    assert(invrep(s));
    assert(!pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    
    // Buscar el primer nodo no nulo en el arreglo de nodos
    int i = s->max_priority;
    while (i >= 0) {
        if (s->array[i] != NULL) {
            return s->array[i]->elem; // Devolver el elemento del primer nodo no nulo
        }
        i--;
    }
    
    // Si no se encontró ningún nodo no nulo, la pila está vacía
    assert(false); // Esto no debería ocurrir si la pila no está vacía
    return 0; // Devolver un valor predeterminado en caso de falla
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    int max_prio = -1; // Inicializa con un valor inválido para la prioridad
    for (unsigned int i = 0; i <= s->max_priority; i++) {
        if (s->array[i] != NULL) {
            max_prio = i; // Actualiza la prioridad más alta encontrada
        }
    }
    assert(max_prio != -1); // Debe haber encontrado al menos una prioridad válida
    return max_prio;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    
    /* debo buscar la maxima prioridad en el arreglo */
    
    unsigned int max_prio = pstack_top_priority(s);
    
    if (s->array[max_prio] != NULL) {
        struct s_node *killme = s->array[max_prio];
        s->array[max_prio] = killme->next;
        killme = destroy_node(killme);
    }
    s->size--;
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    
    // Liberar cada nodo en cada posición del arreglo
    for (unsigned int i = 0; i <= s->max_priority; i++) {
        struct s_node *current = s->array[i];
        while (current != NULL) {
            struct s_node *temp = current;
            current = current->next;
            destroy_node(temp); // Liberar el nodo actual
        }
    }
    
    // Liberar el arreglo de punteros a nodo
    free(s->array);
    s->array = NULL;
    
    // Liberar la estructura principal
    free(s);
    s = NULL;
    
    return NULL; // Devolver NULL ya que la pila ha sido destruida
}
