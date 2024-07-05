#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "string.h"

/*

# El TAD contiende: palabras y sus definiciones, cada palabra tiene una definicion.
# La estructura es mediante listas enlazadas de nodos
# La estructura tiene dos listas enlazadas, una para las palabras y otra para las definiciones
# Los indices de ambas listas estan sincornizados 
# Todos sus nodos deben estar ordenados como en un diccionario real ( invrep ) 

# length debe ser de orden constante

El invariante debe chequear al menos:
■Verificación de caso base. (size = 0?)
■Consistencia entre componentes del struct. 
■Propiedad fundamental del Diccionario. Si no es claro cuál es, releer el enunciado. (orden)

*/

struct _dict_t {
  struct _node_t *words;
  struct _node_t *definitions;
  unsigned int size;
};

struct _node_t {
  string wd;
  struct _node_t *next;
};

static bool invrep(dict_t d) {
  
  bool b = true;
  
  /* EL diccionario no puede ser NULL */
  if( d == NULL ){
      return false;
  }
  
  /* Verificacion del caso base */
  if( d->size == 0 ){
      b = (d->words == NULL) && (d->definitions == NULL);
  }
  else{  
  /* No es vacio, chequeamos consistencia, cada nodo de word 
     debe tener un nodo en el mismo nivel de definitions 
     y ademas el tamaño coincide con d->size */
      unsigned int counter = 0u;
      node_t word = d->words;
      node_t def = d->definitions;
      while(word != NULL && def != NULL){
         
          /* chequeamos orden */
          if(word->next != NULL){
              if(!string_less(word->wd, word->next->wd)){
                  return false;
              }
          }
         
          /* avanzamos */         
          word = word->next;
          def = def->next;
          counter++;          /* aumentamos el contador */
      }
      /* verificamos que sea consistente y de tamaño correcto */
      b = (word == NULL) && (def == NULL) && d->size == counter;   
       
  }
  return b;
}

// returns the amount of nodes to skip when adding a new word
static int nodes_to_skip(dict_t dict, string word) {
    unsigned int numberToSkip = 0;
    /* #Si el dict es vacio, es 0 
       #Si el dict no es vacio, debemos recorrer hasta encontrar una 
       word que no sea mayor a la que queremos agregar
    */
    if(dict->size  == 0){
        return numberToSkip;
    }
    else{
        node_t node = dict->words;
        while(node != NULL && string_less(node->wd, word)){
            node = node->next;
            numberToSkip++;
        }
    }
    return numberToSkip;
}

// returns the position of the word on the list of nodes (0 being the first node)
// returns -1 if the word is not on the dict
static int find_index_of_key(dict_t dict, string word) {
    int index = 0;
    if(dict->size == 0){
        index = -1;
    }
    else{
        node_t node = dict->words;
        while(node != NULL){
            if(string_eq(node->wd, word)){
                return index;
            }
            index++;
            node = node->next;
        }
        if(node == NULL){
            index = -1;
        }
    }
    return index;
}

dict_t dict_empty(void) {
    dict_t newd = NULL; 
    newd = malloc(sizeof(struct _dict_t));
    newd->words = NULL;
    newd->definitions = NULL;
    newd->size = 0;
    
    assert(dict_length(newd) == 0);
    assert(invrep(newd));
    return newd;
}

static node_t create_node(string elem) {
    node_t new_node = NULL;
    new_node = malloc(sizeof(struct _node_t));
    new_node->wd = elem;
    new_node->next = NULL;
    
    return new_node;
}

static node_t destroy_node(node_t node) {
    if(node != NULL){
        node->wd = string_destroy(node->wd);
        node->next = NULL;
        free(node);
        node = NULL;
    }
    return node;
}

dict_t dict_add(dict_t dict, string word, string def) {
    assert(invrep(dict));
    node_t new_word = create_node(word);
    node_t new_def = create_node(def);
   
    /* El diccionario es vacío */
    if(dict->size == 0){
        dict->words = new_word;
        dict->definitions = new_def;
        dict->size++;
    }
    /* El diccionario no es vacío */
    else{
        node_t cursorw = dict->words;
        node_t cursord = dict->definitions;
        int index = find_index_of_key(dict, word);
      
        /* La palabra no está en el diccionario */
        if(index == (-1)){
            unsigned int skip = nodes_to_skip(dict, word);
            if(skip == 0) {
                /* Insertar al inicio */
                new_word->next = dict->words;
                new_def->next = dict->definitions;
                dict->words = new_word;
                dict->definitions = new_def;
            } else {
                /* Insertar en medio o al final */
                while(skip > 1){
                    cursorw = cursorw->next;
                    cursord = cursord->next;
                    skip--;
                }
                new_word->next = cursorw->next;
                cursorw->next = new_word;
                new_def->next = cursord->next;
                cursord->next = new_def;
            }
            dict->size++;
        }
        /* La palabra está en el diccionario */
        else{
            while(index != 0){
               cursord = cursord->next;
               index--;
            }
            cursord->wd = new_def->wd;
            destroy_node(new_def);  // No necesitamos el nuevo nodo de definición
        }
    }
    assert(invrep(dict));
    return dict;
}

string dict_search(dict_t dict, string word) {
    int index = find_index_of_key(dict, word);
    string result;
    if(index == (-1)){
        result = NULL;
    }
    else{
        node_t node = dict->definitions;
        while(index != 0){
            node = node->next;
            index--;
        }
        result = node->wd;
    }
    assert((result != NULL) == dict_exists(dict, word));
    return result;
}

bool dict_exists(dict_t dict, string word) {
    int index = find_index_of_key(dict, word);
    bool b = false;
    if(index != (-1)){
       b = true;
    }
    return b;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep);
    return dict->size;
}

// removes the "index" element of the "list" list of nodes
static node_t remove_on_index(node_t list, int index) {
    node_t aux_node;
    
    if (index == 0) {
        aux_node = list;
        list = list->next;
        destroy_node(aux_node);
    } else {
        node_t prev_node = list;
        for (int i = 0; i < index - 1; i++) {
            prev_node = prev_node->next;
        }
        aux_node = prev_node->next;
        prev_node->next = aux_node->next;
        aux_node = destroy_node(aux_node);
    }
    
    return list;
}

dict_t dict_remove(dict_t dict, string word) {
  assert(invrep(dict));
  int index = find_index_of_key(dict, word);
  if (index != -1) {
    dict->words = remove_on_index(dict->words, index);
    dict->definitions = remove_on_index(dict->definitions, index);
    dict->size--;
  }
  assert(invrep(dict));
  return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    unsigned int length = dict_length(dict);
    if(length != 0){
        length--;
        while(length != 0){
            dict->words = remove_on_index(dict->words, length);
            dict->definitions = remove_on_index(dict->definitions, length);
            length--;
        }
        dict->words = remove_on_index(dict->words, 0);
        dict->definitions = remove_on_index(dict->definitions, 0);
    }
    dict->size = 0;
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict)); // Ensure the dictionary invariant holds
    
    node_t word_node = dict->words;
    node_t def_node = dict->definitions;

    while (word_node != NULL && def_node != NULL) {
        fprintf(file, "%s : %s\n", string_ref(word_node->wd), string_ref(def_node->wd));
        word_node = word_node->next;
        def_node = def_node->next;
    }

    assert(word_node == NULL && def_node == NULL); // Ensure both lists are fully traversed
}

dict_t dict_destroy(dict_t dict) {
  dict = dict_remove_all(dict);
  free(dict);
  dict = NULL;
  return dict;
}
