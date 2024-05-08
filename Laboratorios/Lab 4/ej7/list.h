#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>
typedef int list_elem;
typedef struct list *list;
// constructors

list empty();
/*crea una lista vacia*/
list addl(list list, list_elem elem);
/*agrega el elemento e al comienzo de la lista list*/

// destroy
list destroy(list list);
/*libera memoria en caso que sea necesario*/

//operations
bool is_empty(list list);
/*devuelve True(1) si list es vacia*/
list_elem head(list list);
/*devuelve el primer elemento de la lista list*/
/*PRE: not is_empty(list)*/
list tail(list list);
/*elimina el primer elemento de la lista list*/
/*PRE: not is_empty(list)*/
list addr(list list, list_elem elem);
/*agrega el elemento e al final de la lista list*/
list_elem length(list list);
/*devuelve la cantidad de elementos de la lista list*/
list concat(list list1, list list2);
/*agrega al final de la list1 todos los elementos de la list2 en el mismo orden*/
list_elem index(list list, int n);
/*devuelve el n-seimo elemento de la lista list*/
/*PRE: length(list) > n*/
list take(list list, int n);
/*deja en list solo los primeros n elementos, eliminando el resto*/
list drop(list list, int n);
/*elimina los primeros n elementos de list*/
list copy_list(list list);
/*copia todos los elementos de list en la nueva lista t2*/



#endif
