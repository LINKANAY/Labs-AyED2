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
  Character character;
  float iniciative;
  struct s_node *next;
};

/* ============================================================================
INVREP
============================================================================ */

static bool invrep(pqueue q) {
  unsigned int i = 0u;
  struct s_node *n = q->front;
  while (n != NULL) {
    n = n->next;
    i++;
  }
  return q->size == i;
}

/* ============================================================================
NEW
============================================================================ */

pqueue pqueue_empty(void) {
  pqueue q = NULL;
  q = malloc(sizeof(struct s_pqueue));
  q->front = NULL;
  q->size = 0u;
  assert(pqueue_is_empty(q));
  return q;
}

/* ============================================================================
ENQUEUE
============================================================================ */

static float calculate_priority(Character character) {
  float iniciative = 0.0f;
  if (character_is_alive(character)) {
    iniciative = character_agility(character);
    if (character_ctype(character) == agile) {
      iniciative = iniciative * 1.5f;
    } else if (character_ctype(character) == tank) {
      iniciative = iniciative * 0.8f;
    }
  }
  return iniciative;
}

static struct s_node *create_node(Character character) {
  struct s_node *new_node = NULL;
  float priority = calculate_priority(character);
  new_node = malloc(sizeof(struct s_node));
  assert(new_node != NULL);
  new_node->character = character;
  new_node->iniciative = priority;
  new_node->next = NULL;
  return new_node;
}

pqueue pqueue_enqueue(pqueue q, Character character) {
  assert(invrep(q));
  struct s_node *new_node = create_node(character);
  if (q->front == NULL || q->front->iniciative < new_node->iniciative) {
    new_node->next = q->front;
    q->front = new_node;
  } else {
    struct s_node *current = q->front;
    while (current->next != NULL && current->next->iniciative >= new_node->iniciative) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
  q->size++;
  assert(!pqueue_is_empty(q));
  return q;
}

/* ============================================================================
IS EMPTY?
============================================================================ */

bool pqueue_is_empty(pqueue q) {
  return q->front == NULL;
}

/* ============================================================================
PEEKS
============================================================================ */

Character pqueue_peek(pqueue q) {
  return q->front->character;
}

float pqueue_peek_priority(pqueue q) {
  return q->front->iniciative;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int pqueue_size(pqueue q) {
  assert(invrep(q));
  return q->size;
}

/* ============================================================================
COPY
============================================================================ */

pqueue pqueue_copy(pqueue q) {
  assert(invrep(q));
  pqueue q_copy = pqueue_empty();
  struct s_node *node = q->front;
  while (node != NULL) {
    Character c = character_copy(node->character);
    q_copy = pqueue_enqueue(q_copy, c);
    node = node->next;
  }
  return q_copy;
}

/* ============================================================================
DESTROY!
============================================================================ */
static struct s_node *destroy_node(struct s_node *node) {
  assert(node != NULL); 
  node->character = character_destroy(node->character);
  node->next = NULL;
  free(node);
  node = NULL;
  assert(node == NULL);
  return node;
}

pqueue pqueue_dequeue(pqueue q) {
  assert(invrep(q));
  struct s_node *dequeueme = q->front;
  q->front = q->front->next;
  dequeueme = destroy_node(dequeueme);
  q->size--;  
  return q;
}

pqueue pqueue_destroy(pqueue q) {
  while (q->front != NULL) {
    q = pqueue_dequeue(q);
  }
  free(q);
  q = NULL;
  assert(q == NULL);
  return q;
}