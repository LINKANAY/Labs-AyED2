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

struct _line_node *create_node(domino t)
{
    struct _line_node *newNode = NULL;
    newNode = malloc(sizeof(struct _line_node));
    assert(newNode != NULL);
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
    domino_line new = NULL;
    new = malloc(sizeof(domino_line));
    assert(new != NULL);
    new->head = create_node(first);
    new->size = 1;
    return new;
}

/*Agregar una ficha a la línea de juego*/
domino_line line_add(domino_line line, domino t)
{
    /*
     * COMPLETAR
     *
     */
    struct _line_node *new = line->head;
    while (new->next != NULL)
    {
        new = new->next;
    }
    new->next = create_node(t);
    line->size++;

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
    bool correct = false;
    unsigned int i = 0u;
    struct _line_node *aux = line->head;
    struct _line_node *prev = line->head;
    if (n == 0 && aux->next != NULL)
    {
        if (domino_matches(prev->tile, aux->next->tile))
        {
            correct = true;
        }
    }
    else if (n == line_length(line) - 1)
    {
        while (aux->next != NULL)
        {
            prev = aux;
            aux = aux->next;
        }

        if (domino_matches(prev->tile, aux->tile))
        {
            correct = true;
        }
    }
    else
    {
        while (aux->next != NULL && !correct && i < n)
        {
            i++;
            prev = aux;
            aux = aux->next;
        }
        if (domino_matches(prev->tile, aux->tile) && domino_matches(aux->tile, aux->next->tile))
        {
            correct = true;
        }
    }
    return correct;
}

int line_total_points(domino_line line)
{
    /*
     * COMPLETAR
     *
     */
    int total = 0;
    struct _line_node *ficha = line->head;
    while (ficha != NULL)
    {
        total = total + domino_up(ficha->tile) + domino_down(ficha->tile);
        ficha = ficha->next;
    }
    return total;
}

domino *line_to_array(domino_line line)
{
    /*
     * COMPLETAR
     *
     */
    int size = line_length(line);
    domino *array = malloc(sizeof(domino) * line_length(line));
    struct _line_node *ficha = line->head;
    for (int i = 0; i < size; i++)
    {
        array[i] = ficha->tile;
        ficha = ficha->next;
    }
    return array;
}
void line_dump(domino_line line)
{
    domino *array = line_to_array(line);
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
    struct _line_node *ficha = line->head;
    struct _line_node *next = NULL;
    while (ficha != NULL)
    {
        next = ficha->next;
        free(ficha);
        ficha = next;
    }
    free(line);
    line = NULL;
    return line;
}

line_iterator line_iterator_begin(domino_line line)
{
    /*
     * COMPLETAR
     *
     */
    line_iterator new = line->head;
    return new;
}

domino line_iterator_get(line_iterator lit)
{
    /*
     * COMPLETAR
     *
     */
    return lit->tile;
}

line_iterator line_iterator_next(line_iterator lit)
{
    /*
     * COMPLETAR
     *
     */
    if (lit->next == NULL)
    {
        return NULL;
    }
    else
    {
        lit = lit->next;
    }
    return lit;
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
    bool res = false;
    if (lit->tile != NULL)
    {
        res = false;
    }
    else
    {
        res = true;
    }
    return res;
}
