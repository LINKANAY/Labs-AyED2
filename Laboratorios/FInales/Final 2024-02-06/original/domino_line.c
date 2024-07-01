#include "domino_line.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "domino.h"

struct _s_line
{
     struct _line_node *head;
     unsigned int size;
};

struct _line_node
{
     struct _line_node *next;
     domino tile;
};

struct _line_node *create_node(domino t){
    struct _line_node *newNode = NULL;
    newNode = malloc(sizeof(struct _line_node));
    assert(newNode!=NULL);
    newNode->next = NULL;
    newNode->tile = t;

    return newNode;
}

domino_line line_new(domino first)
{
    /*
     * COMPLETAR
     *
     */


    return tile;
}

domino_line line_add(domino_line line, domino t)
{
    /*
     * COMPLETAR
     *
     *
    struct _line_node *new = create_node(t);
    if(line->head == NULL){
        line->head = new;
        return line; // ESTO ME DABA MEMORY LEAKS
    }*/

    return line;
}

unsigned int line_length(domino_line line)
{
     return line->size;
}

bool line_n_correct(domino_line line, unsigned int n)
{
    /*
     * COMPLETAR
     *
     */

}

int line_total_points(domino_line line)
{
    /*
     * COMPLETAR
     *
     */

}

domino* line_to_array(domino_line line)
{
    /*
     * COMPLETAR
     *
     */

}

void line_dump(domino_line line)
{
    domino* array = line_to_array(line);
    for (unsigned int i = 0u; i < line_length(line); i++)
    {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line)
{
    /*
     * COMPLETAR
     *
     */

}

line_iterator line_iterator_begin(domino_line line)
{
    /*
     * COMPLETAR
     *
     */

     return new;
}

domino line_iterator_get(line_iterator lit)
{
    /*
     * COMPLETAR
     *
     */

}

line_iterator line_iterator_next(line_iterator lit)
{
    /*
     * COMPLETAR
     *
     */

}

bool line_iterator_end(line_iterator lit)
{
    /*
     * COMPLETAR
     *

     Devuelve “true” si ya se ha alcanzado el final
    de la lista, “false” en caso contrario. Por final
    de la lista entendemos que ya no hay
    elementos por procesar. Es decir para la lista
    [1:2, 2:2, 3:0] si el iterador “lit” está apuntado
    a 3:0 esta función devolverá FALSE, pues
    existe un elemento todavía por procesar.

     */
     

}
