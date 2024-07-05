#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "tape.h"

struct _s_node {
    tape_elem elem;
    struct _s_node *next;
};

typedef struct _s_node * node_t;

struct _s_tape {
    unsigned int size;
    node_t cursor;  // Puntero al elemento actual
    node_t start;   // Puntero al primer nodo de la cinta
};

static bool invrep(tape_t tape) {
    if (tape == NULL) return false; 

    // Verificación del tamaño de la cinta
    unsigned int count = 0;
    node_t node = tape->start;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    if (count != tape->size) return false;

    // Verificación del cursor dentro de los límites
    if (tape->cursor != NULL) {
        node = tape->start;
        while (node != NULL && node != tape->cursor) {
            node = node->next;
        }
        if (node != tape->cursor){ 
            return false;
        } 
    }

    // Verificación de las condiciones de inicio y final
    bool at_stop_correct = tape_at_stop(tape) == (tape->cursor == NULL);
    bool at_start_correct = tape_at_start(tape) == (tape->cursor == tape->start);

    return at_stop_correct && at_start_correct;
}


static node_t create_node(tape_elem e) {
    node_t new_node=malloc(sizeof(struct _s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static node_t destroy_node(node_t node) {
    assert(node != NULL);
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}

tape_t tape_create(void) {
    tape_t tape = NULL;
    tape = malloc(sizeof(struct _s_tape));
    tape->size = 0u;
    tape->cursor = NULL;
    tape->start = NULL;
    assert(tape_is_empty(tape) && tape_at_start(tape));
    return tape;
}

tape_t tape_rewind(tape_t tape) {
    assert(invrep(tape));
    assert(tape != NULL);
    tape->cursor = tape->start;
    assert(tape_at_start(tape));
    return tape;
}

bool tape_at_start(tape_t tape) {
    return tape->cursor == tape->start;
}


bool tape_at_stop(tape_t tape) {
    assert(tape != NULL);
    return tape->cursor == NULL;
}


bool tape_is_empty(tape_t tape) {
    return tape->size == 0;
}

unsigned int tape_length(tape_t tape) {
    assert(invrep(tape));
    assert(tape != NULL);
    return tape->size;
}

tape_t tape_step(tape_t tape) {
    assert(invrep(tape));
    assert(tape != NULL);
    if(tape->cursor != NULL){
        tape->cursor = tape->cursor->next;
    }
    assert(invrep(tape));
    return tape;
}

tape_t tape_insertl(tape_t tape, tape_elem e) {
    assert(invrep(tape));

    // Creamos un nuevo nodo con el elemento dado
    node_t new_node = create_node(e);
    assert(new_node != NULL);

    // Caso 1: La cinta está vacía
    if (tape_is_empty(tape)) {
        tape->start = new_node;
        tape->cursor = new_node;
    } 
    // Caso 2: El cursor está al inicio de la cinta
    else if (tape_at_start(tape)) {
        new_node->next = tape->start;
        tape->start = new_node;
    } 
    // Caso 3: El cursor está en algún lugar intermedio de la cinta
    else {
        node_t prev_node = tape->start;
        while (prev_node->next != tape->cursor) {
            prev_node = prev_node->next;
        }
        prev_node->next = new_node;
        new_node->next = tape->cursor;
    }

    // Incrementamos el tamaño de la cinta
    tape->size++;

    // Verificamos el invariante
    assert(invrep(tape));

    return tape;
}

tape_t tape_insertr(tape_t tape, tape_elem e) {
    assert(invrep(tape) && (!tape_at_stop(tape) || tape_is_empty(tape)));
    node_t new_node=create_node(e);
    if (tape->start!= NULL) {
        new_node->next = tape->cursor->next;
        tape->cursor->next = new_node;
        tape->cursor = new_node;
    } else {
        tape->start = new_node;
        tape->cursor = new_node;
    }
    tape->size++;
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_erase(tape_t tape) {
    assert( invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape));
    if(tape->cursor != NULL){
        node_t node_to_erase = tape->cursor;
        if (tape->cursor == tape->start) {
            tape->start = tape->cursor->next;
        } 
        else{
            node_t node = tape->start;
            while(node->next != tape->cursor){
                node = node->next;
            }
            node->next = tape->cursor->next;
        }
        if (tape->cursor->next == NULL) { // Si el elemento a borrar es el último
            tape->cursor = NULL; // Establecer el cursor a NULL
        } else {
            tape->cursor = tape->cursor->next;
        }
        node_to_erase = destroy_node(node_to_erase);
        tape->size--;
    
    }
    assert(invrep(tape));
    return tape;
}


tape_elem tape_read(tape_t tape) {
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape));
    return tape->cursor->elem;
}

void tape_dump(tape_t tape) {
    assert(invrep(tape));
    node_t node=tape->start;
    printf("#");
    while (node != NULL) {
        if (node != tape->cursor) {
            printf("-%c-", node->elem);
        } else {
            printf("-[%c]-", node->elem);
        }
        node = node->next;
    }
    if (tape->cursor==NULL) {
        printf("-[]-");
    }
    printf("#\n");
}

tape_t tape_copy(tape_t tape) {
    assert(invrep(tape));
    tape_t copy = tape_create();
    if(!tape_is_empty(tape)){
        node_t new_node = tape->start;
        while(new_node != NULL){
            copy = tape_insertr(copy,new_node->elem); 
            new_node = new_node->next;
        }
            copy->cursor = copy->start;
    }
    assert(tape_at_start(copy) && (copy != tape) && (tape_length(tape) == tape_length(copy)));
    return copy;
}

tape_t tape_destroy(tape_t tape) {
    if(tape != NULL){
        node_t node = tape->start;
        while(node != NULL){
            node_t killme = node;
            node = node->next;
            killme = destroy_node(killme);
        }
        free(tape);
    }
    tape = NULL;
    assert(tape == NULL);
    return tape;
}

