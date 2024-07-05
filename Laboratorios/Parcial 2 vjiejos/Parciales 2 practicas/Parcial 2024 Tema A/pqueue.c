#include <assert.h>
	#include <stdbool.h>
	#include <stdlib.h>

	#include "character/character.h"
	#include "pqueue.h"

	/* ============================================================================
	STRUCTS!
	============================================================================ */

	struct s_pqueue {
	  struct s_node *front;
	  unsigned int size;					
	};

	struct s_node {
	  struct s_Character *character;
	  float priority;
	  struct s_node *next; 
	};

	/* ============================================================================
	INVREP
	============================================================================ */

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
            if(node->priority < node->next->priority){
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

	/* ============================================================================
	NEW
	============================================================================ */

	pqueue pqueue_empty(void) {
	  pqueue q = NULL;
	  q = malloc(sizeof(struct s_pqueue));
	  assert(q != NULL);
	  q->front = NULL;
	  q->size = 0u;
	  return q;
	}

	/* ============================================================================
	ENQUEUE
	============================================================================ */

	static float calculate_priority(Character character) {
	  unsigned int baseInitiative = 0u;
	  float isAlive = 0;
	  float modificador;
	  unsigned int type;
	  float priority = 0;
	  baseInitiative = character_agility(character); 
	  type = character_ctype(character);
	  if(character_is_alive(character)){
		  isAlive = 1;
	  }
	  if(type == agile){
		  modificador = 1.5;
	  }		
	  else if(type == tank){
		  modificador = 0.8;
	  }
	  else{		
		  modificador = 1;
	  }
	  
	  priority = modificador * baseInitiative * isAlive;
	  
	  return priority;
	}

	static struct s_node *create_node(Character character) {
	  struct s_node *new_node = NULL;
	  float priority = calculate_priority(character);
	  new_node = malloc(sizeof(struct s_node));
	  assert(new_node != NULL);
	  new_node->character = character;
	  new_node->next = NULL;
	  new_node->priority = priority;
	  return new_node;
	}

	pqueue pqueue_enqueue(pqueue q, Character character) {
	  assert(invrep(q));
	  struct s_node *new_node = create_node(character);
	  // caso la cola es vacia
	  if(pqueue_is_empty(q)){
		  q->front = new_node;
	  }
	  // caso no es vacia
	  else{
		  // debo encolar mi nuevo nodo en el primer nodo con prioridad menor	
		  struct s_node *aux = q->front;
		  // la prioridad que queremos agregar es la más alta
		  if(new_node->priority > q->front->priority){
		      new_node->next = q->front;
		      q->front = new_node;
		  }
		  else{
		     while(aux->next != NULL && new_node->priority <= aux->next->priority){
		        aux = aux->next;
		     }
		     new_node->next = aux->next;
		     aux->next = new_node;
		     }    
          }
	  q->size++;
	  return q;
	}

	/* ============================================================================
	IS EMPTY?
	============================================================================ */

	bool pqueue_is_empty(pqueue q) {
	  return q->size == 0;
	}

	/* ============================================================================
	PEEKS
	============================================================================ */

	Character pqueue_peek(pqueue q) {
	  assert(!pqueue_is_empty(q));
	  return q->front->character;
	}

	float pqueue_peek_priority(pqueue q) {
	  assert(!pqueue_is_empty(q));
	  return q->front->priority;
	}

	/* ============================================================================
	SIZE
	============================================================================ */

	unsigned int pqueue_size(pqueue q) {
	  assert(invrep(q));
	  unsigned int size = 0;
	  size = q->size;		
	  return size;
	}

	/* ============================================================================
	COPY
	============================================================================ */

pqueue pqueue_copy(pqueue q) {
    assert(invrep(q));  
    struct s_pqueue *copy = pqueue_empty();
    if (!pqueue_is_empty(q)) {
    
        // Inicializamos
        struct s_node *current = q->front;
        copy->front = create_node(character_copy(current->character));

        struct s_node *last_copied = copy->front;
        current = current->next;

        // Recorre el resto de los nodos y agrégalos a la copia
        while (current != NULL) {
            last_copied->next = create_node(character_copy(current->character));
            last_copied = last_copied->next;
            current = current->next;
        }
        
    }
    copy->size = q->size;
    assert(invrep(copy));  
    return copy;
}

	/* ============================================================================
	DESTROY!
	============================================================================ */
	static struct s_node *destroy_node(struct s_node *node) {
	  assert(node != NULL);
	  node->character = character_destroy(node->character);
	  free(node);
	  node = NULL;
	  assert(node == NULL);
	  return node;
	}
	
pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *killme = q->front; 
    q->front = q->front->next;
    killme = destroy_node(killme);
    q->size--;
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *killme = NULL;
    struct s_node *current = NULL;
    if(!pqueue_is_empty(q)){
        current = q->front;
        while(current != NULL){
            killme = current;
            current = current->next;
            killme = destroy_node(killme);
            
        }
        
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
