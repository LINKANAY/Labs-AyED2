#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "character/character.h"
#include "pqueue.h"

/* ============================================================================
STRUCTS!
============================================================================ */

struct s_pqueue
{
    /*
     * COMPLETAR
     *
     */
    struct s_node *cola;
    unsigned int size;
};

struct s_node
{
    /*
     * COMPLETAR
     *
     */
    Character character;
    float iniciative;
    struct s_node *next;
};

/* ============================================================================
INVREP
============================================================================ */

static bool invrep(pqueue q)
{
    /*
     * COMPLETAR
     *
     */

    // return true;
    return (q != NULL);
}

/* ============================================================================
NEW
============================================================================ */

pqueue pqueue_empty(void)
{
    pqueue q = NULL;
    /*
     * COMPLETAR
     *
     */
    q = malloc(sizeof(struct s_pqueue));
    q->cola = NULL;
    q->size = 0u;
    return q;
}

/* ============================================================================
ENQUEUE
============================================================================ */

static float calculate_priority(Character character)
{
    /*
     * COMPLETAR
     *
     */
    float initialize = 0.0f;
    if (character_is_alive(character))
    {
        initialize = character_agility(character);
        if (character_ctype(character) == agile)
        {
            initialize *= 1.5f;
        }
        else if (character_ctype(character) == tank)
        {
            initialize *= 0.8f;
        }
    }
    return initialize;
}

static struct s_node *create_node(Character character)
{
    struct s_node *new_node = NULL;
    float priority = calculate_priority(character);
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    /*
     * COMPLETAR
     *
     */
    new_node->character = character;
    new_node->iniciative = priority;
    new_node->next = NULL;

    return new_node;
}

pqueue pqueue_enqueue(pqueue q, Character character)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(character);
    /*
     * COMPLETAR
     *
     */
    if (q->cola == NULL || q->cola->iniciative < new_node->iniciative)
    {
        new_node->next = q->cola;
        q->cola = new_node;
    }
    else
    {
        struct s_node *temp = q->cola;
        while (temp->next != NULL && temp->next->iniciative >= new_node->iniciative)
        {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
    q->size++;
    return q;
}

/* ============================================================================
IS EMPTY?
============================================================================ */

bool pqueue_is_empty(pqueue q)
{
    /*
     * COMPLETAR
     *
     */
    return q->cola == NULL;
}

/* ============================================================================
PEEKS
============================================================================ */

Character pqueue_peek(pqueue q)
{
    /*
     * COMPLETAR
     *
     */
    return q->cola->character;
}

float pqueue_peek_priority(pqueue q)
{
    /*
     * COMPLETAR
     *
     */
    return q->cola->iniciative;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    // unsigned int size = 0;
    /*
     * COMPLETAR
     */

    return q->size;
}

/* ============================================================================
COPY
============================================================================ */

pqueue pqueue_copy(pqueue q)
{
    assert(invrep(q));
    /*
     * COMPLETAR
     */
    pqueue copy = pqueue_empty();
    struct s_node *temp = q->cola;
    while (temp != NULL)
    {
        Character c = character_copy(temp->character);
        copy = pqueue_enqueue(copy, c);
        temp = temp->next;
    }

    return copy;
}

/* ============================================================================
DESTROY!
============================================================================ */
static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    /*
     * COMPLETAR
     *
     */
    node->character = character_destroy(node->character);
    node->next = NULL;
    free(node);
    node = NULL;

    assert(node == NULL);
    return node;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q));
    /*
     * COMPLETAR
     */
    struct s_node *desencolar = q->cola;
    q->cola = q->cola->next;
    desencolar = destroy_node(desencolar);
    q->size--;

    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    /*
     * COMPLETAR
     */
    if (pqueue_is_empty(q))
    {
        return NULL;
    }
    else
    {
        while (q->cola != NULL)
        {
            q = pqueue_dequeue(q);
        }
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
