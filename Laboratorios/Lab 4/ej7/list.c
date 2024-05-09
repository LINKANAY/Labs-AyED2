#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct list_t
{
    list_elem elem;
    struct list_t *next;
};

/*crea una lista vacia*/
list empty()
{
    return NULL;
}

/*agrega el elemento e al comienzo de la lista list*/
list addl(list lista, list_elem elem)
{
    list lis = malloc(sizeof(struct list_t));
    lis->elem = elem;
    lis->next = lista;
    return lis;
}

/*libera memoria en caso que sea necesario*/
list destroy(list lista)
{
    free(lista);
    return NULL;
}

/*devuelve True(1) si list es vacia*/
bool is_empty(list lista)
{
    bool estado = true;
    if (!(lista == NULL))
    {
        estado = false;
    }
    return estado;
}

/*devuelve el primer elemento de la lista list*/
/*PRE: not is_empty(list)*/
list_elem head(list lista)
{
    list_elem ele;
    if (!(is_empty(lista)))
    {
        ele = lista->elem;
    }
    return ele;
}

/*elimina el primer elemento de la lista list*/
/*PRE: not is_empty(list)*/
list tail(list lista)
{
    if (!(is_empty(lista)))
    {
        list lis = malloc(sizeof(struct list_t));
        lis = lista;
        lista = lista->next;
        free(lis);
    }

    return lista;
}

/*agrega el elemento e al final de la lista list*/
list addr(list lista, list_elem elem)
{
    list lis2 = malloc(sizeof(struct list_t));
    lis2->elem = elem;
    lis2->next = NULL;
    if (lista == NULL)
    {
        return lis2;
    }

    list lis1 = lista;
    while (lis1->next != NULL)
    {
        lis1 = lis1->next;
    }
    lis1->next = lis2;
    free(lis2);
    return lista;
}

/*devuelve la cantidad de elementos de la lista list*/
list_elem length(list lista)
{
    list lis = lista;
    list_elem longitud = 0;

    while (lis != NULL)
    {
        longitud = longitud + 1;
        lis = lis->next;
    }
    return longitud;
}

/*agrega al final de la list1 todos los elementos de la list2 en el mismo orden*/
list concat(list list1, list list2)
{
    list lis2 = malloc(sizeof(struct list_t));
    lis2 = copy_list(list2);
    list lis1 = malloc(sizeof(struct list_t));
    lis1 = list1;
    while (lis1->next != NULL)
    {
        lis1 = lis1->next;
    }
    lis1->next = lis2;
    return list1;
}

/*devuelve el n-seimo elemento de la lista list*/
/*PRE: length(list) > n*/
list_elem nth_elem(list lista, int n)
{
    list_elem num = 0;
    if (length(lista) > n)
    {
        list lis = malloc(sizeof(struct list_t));
        lis = lista;
        int i;
        i = 0;
        while (i <= n)
        {
            lis = lis->next;
            i = i + 1;
        }
        num = lis->elem;
    }
    return num;
}

/*deja en lista solo los primeros n elementos, eliminando el resto*/
list take(list lista, int n)
{
    if (!(n >= length(lista)))
    {
        int i;
        list lis = malloc(sizeof(struct list_t));
        i = 0;
        lis = lista;
        while (i <= n)
        {
            lis = lis->next;
            i = i + 1;
        }
        lis->next = NULL;
    }
    return lista;
}

/*elimina los primeros n elementos de list*/
list drop(list lista, int n)
{
    if (n > length(lista))
    {
        free(lista);
        lista = NULL;
    }
    else
    {
        int i;
        list lis = malloc(sizeof(struct list_t));
        i = 0;
        lis = lista;
        while (i <= 0)
        {
            lista = lista->next;
            i = i + 1;
            free(lis);
        }
    }
    return lista;
}

/*copia todos los elementos de list en la nueva lista t2*/
list copy_list(list lista)
{
    list lfinal = empty();

    while (lista != NULL)
    {
        lfinal = addr(lfinal, lista->elem);
        lista = lista->next;
    }

    return lfinal;
}
