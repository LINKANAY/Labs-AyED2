#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node **array;
    unsigned int size;
    priority_t min_priority;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    
    new_node = malloc(sizeof(*new_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    
    if (node != NULL)
    {
        free(node);
    }
    
    return node;
}


static bool invrep(pqueue q) {
    bool b = true;
    
    if (q == NULL)
    {
        b = false;
    }
    else if (q->size == 0)
    {
        b = pqueue_is_empty(q);
    }
    else
    {   
        unsigned int count = 0;
        for (unsigned int i = 0; i <= q->min_priority; i++)
        {
            struct s_node * p = NULL;
            p = q->array[i];
            
            if (p != NULL)
            {
                while (p->next != NULL)
                {
                    count++;
                    p = p->next;
                }
                count++;
            }            
        }
        if(q->size != count){
            b = false;
        }
    }
    return b;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    
    q = malloc(sizeof(*q));
    assert(q!=NULL);
    q->min_priority = min_priority;
    q->array = calloc(min_priority+1 , sizeof(struct s_node *));
    q->size = 0;
    
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q) && priority <= q->min_priority);

    struct s_node * new_node = create_node(e);
    struct s_node * p = NULL;

    if (q->array[priority] == NULL)
    {
        q->array[priority] = new_node;
    }
    else
    {
        p = q->array[priority];

        while (p->next != NULL)
        {
            p = p->next;
        }
            
        p->next = new_node;
    }

    q->size++; 
    
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(q!=NULL);

    bool b = true;

    if (q->array != NULL)
    {
        for (unsigned int i = 0; i <= q->min_priority && b; i++)
        {
            if (q->array[i] != NULL)
            {
                b = false;
            }
        }
    }
    return b;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    pqueue_elem elem;

    bool stop = false;
    priority_t peek=0;

    for (unsigned int i = 0; i <= q->min_priority && !stop; i++)
    {
        if (q->array[i] != NULL)
        {
            stop = true;
        }
        else
        {
            peek++;
        }   
    }
    
    elem = q->array[peek]->elem;
    assert(invrep(q));
    return elem;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    bool stop = false;
    priority_t peek=0;

    for (unsigned int i = 0; i <= q->min_priority && !stop; i++)
    {
        if (q->array[i] != NULL)
        {
            stop = true;
        }
        else
        {
            peek++;
        }   
    }
    assert(invrep(q));
    return peek; 
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    
    priority_t peekp = pqueue_peek_priority(q);
    struct s_node *killme = NULL;
    killme = q->array[peekp];

    q->array[peekp] = q->array[peekp]->next;

    killme = destroy_node(killme);

    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));

    while (!pqueue_is_empty(q))
    {
        q = pqueue_dequeue(q);
    }
    free(q->array);
    free(q);
    
    return q;
}
