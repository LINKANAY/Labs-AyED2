#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    struct s_node *front;
} s_pqueue;

struct s_node
{
    pqueue_elem elem;
    unsigned int prioridad;
    struct s_node *next;
} s_node;

static struct s_node *create_node(pqueue_elem e, unsigned int priority)
{
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_pqueue));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->prioridad = priority;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    struct s_node *aux = node;
    while (aux != NULL)
    {
        struct s_node *next = aux->next;
        destroy_node(aux);
        aux = next;
    }
    free(node);
    node = NULL;    
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q)
{
    if (q == NULL)
    {
        return false;
    }

    return true;
}

pqueue pqueue_empty(void)
{
    pqueue q = NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->front = NULL;


    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    
    struct s_node *aux = q->front;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    aux->next = new_node;
    q->front = aux;
    
    assert(e == e && priority == priority && new_node == new_node); // BORRAR ESTE ASSERT
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    if (q == NULL)
    {
        return false;
    }

    return true;
}

pqueue_elem pqueue_peek(pqueue q)
{
    pqueue_elem urg = 0;
    struct s_node *aux = q->front;
    while (aux != NULL)
    {
        if (aux->prioridad < aux->next->prioridad)
        {
            urg = aux->elem;
        }

        aux = aux->next;
    }
    free(aux);
    return urg;
}

unsigned int pqueue_peek_priority(pqueue q)
{
    unsigned int urg = 0;
    struct s_node *aux = q->front;
    while (aux->next != NULL)
    {
        if (aux->prioridad < aux->next->prioridad)
        {
            urg = aux->prioridad;
        }

        aux = aux->next;
    }
    free(aux);
    return urg;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    unsigned int size = 0;
    struct s_node *aux = q->front;
    while (aux != NULL)
    {
        size++;
        aux = aux->next;
    }
    free(aux);
    return size;
}

pqueue pqueue_dequeue(pqueue q)
{
    //* DESC: Remove the element with the most urgent 
    //priority of the pqueue 'q'
    if (q==NULL || q->front==NULL)
    {
        return q;
    }
    unsigned int priory = pqueue_peek_priority(q);
    struct s_node *aux = q->front;
    struct s_node *prev = NULL;
    while (aux != NULL && prev == NULL)
    {
        if (aux->prioridad == priory)
        {
            
        }else{
            prev->next = aux->next;
        }        
    }
    free(aux);
    q->front = prev;
        
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    struct s_node *aux = q->front;
    while (aux != NULL)
    {
        struct s_node *next = aux->next;
        destroy_node(aux);
        aux = next;
        free(next);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
