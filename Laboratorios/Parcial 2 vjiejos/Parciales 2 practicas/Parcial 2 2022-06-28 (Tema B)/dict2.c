#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "string.h"

/*
	Estructura principal:
		#Puntero a nodo words
		#Puntero a nodo definitions
		#size
		(las listas enlazadas deben estar sincronizadas)
		(las palabras deben estar en orden)

	Invariante:
		■Verificación de caso base.
		■Consistencia entre componentes del struct.
		■Propiedad fundamental del Diccionario
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
    // d no puede ser NULL
    if(d == NULL){
        return false;
    }
  
    // caso base
    if(d->size == 0){
        return (d->words == NULL) && (d->definitions == NULL);
    }
    // caso general, debe respetar consistencia
    /* 
    	La idea es recorrer tanto el nodo de words como el de definitions
   	al final ambos deben apuntar a null, mientras tanto vamos verificando que
  	la word anterior sea menor a la siguiente (oden) y a su vez sumamos un contador
	para verificar que se respete size
   */
    else{
        struct _node_t *node_w = d->words;
        struct _node_t *node_d = d->definitions;
        unsigned int counter = 0u;
        while(node_w != NULL && node_d != NULL && b){
            if(node_w->next != NULL){
                b = string_less(node_w->wd, node_w->next->wd);
            }
            node_w = node_w->next;
            node_d = node_d->next;
            counter++;
        }
        // verificamos tamaño y consistencia
        b = b && (counter == d->size) && (node_w == node_d);
    }
    return b;
}

// returns the amount of nodes to skip when adding a new word
static int nodes_to_skip(dict_t dict, string word) {
  unsigned int numberToSkip = 0;
  // la idea es recorrer hasta llegar al nodo->next con mayor estricta word
  if(dict->size != 0){
      struct _node_t *node = dict->words;
      while(node != NULL){
          // si la palabra que quiero agregar es mayor a la del nodo actual: avanzo
          if(string_less(node->wd,word)){
              numberToSkip++;
          }
          else{
              break;
          }
          node = node->next;
      }
  }
  return numberToSkip;
}

// returns the position of the word on the list of nodes (0 being the first node)
// returns -1 if the word is not on the dict
static int find_index_of_key(dict_t dict, string word) {
  int index = 0;
  struct _node_t *node = dict->words;
  bool b = true;
  while(node != NULL && b){
      if(string_eq(node->wd, word)){
          b = false;
      }
      else{
          index++;
      }
      node = node->next;
  }
  if(b){
      index = (-1);
  }
  return index;
}

dict_t dict_empty(void) {
    dict_t new_dict = NULL;
    new_dict = malloc(sizeof(struct _dict_t));
    assert(new_dict != NULL);
    new_dict->words = NULL;
    new_dict->definitions = NULL;
    new_dict->size = 0u;
    assert(invrep(new_dict));
    return new_dict;
}

static node_t create_node(string elem) {
    struct _node_t *new_node = NULL;
    new_node = malloc(sizeof(struct _node_t));
    assert(new_node != NULL);
    new_node->wd = elem;
    new_node->next = NULL;
    return new_node;
}
static node_t destroy_node(node_t node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

dict_t dict_add(dict_t dict, string word, string def) {
    assert(invrep(dict));
    struct _node_t *new_word = create_node(word);
    struct _node_t *new_def = create_node(def);
    
    // Caso 1: diccionario vacio
    if(dict->size == 0u){
        dict->words = new_word;
        dict->definitions = new_def;
        dict->size++;
    }
    // Caso 2: No es vacio
    else{
        int index = find_index_of_key(dict, word);
        // SubCaso 2: word no esta en dict
        if(index == (-1)){
            int skip = nodes_to_skip(dict, word);
            struct _node_t *cursor_w = dict->words;
            struct _node_t *cursor_d = dict->definitions;
            if(skip == 0){
                new_word->next = dict->words->next;
                new_def->next = dict->definitions->next;
                dict->words = new_word;
                dict->definitions = new_def;
            }
            else{
                while(skip != 1){
                    cursor_w = cursor_w->next;
                    cursor_d = cursor_d->next;
                    skip--;    
                }
                    new_word->next = cursor_w->next;
                    new_def->next = cursor_d->next;
                    cursor_d->next = new_def;
                    cursor_w->next = new_word;
                    dict->size++;
            }
        }
        // Subcaso 2: word si esta en dict
        else{
            struct _node_t *cursor_d = dict->definitions;
            while(index != 0){
                cursor_d = cursor_d->next;
                index--;
            }
            cursor_d->wd = new_def->wd;
            new_def = destroy_node(new_def); // No lo necesitamos
        }
    
    }
    assert(invrep(dict));
    return dict;
}

string dict_search(dict_t dict, string word) {
/* Returns the definition of the given [word], or NULL if [word] is not in
 * the dictionary.
 *
 * Note: Returns a reference to the string owned by the dictionary (not a copy).
 *
 * PRE: {dict --> dict_t /\ word --> string}
 *   def = dict_search(dict, word);
 * POS: {(def != NULL) == dict_exists(dict, word)}
 */
    string definition;
    if(dict->size != 0){ 
        int index = find_index_of_key(dict, word);
        if(index == (-1)){
            definition = NULL;
        }
        else{
            struct _node_t *node = dict->definitions;
            while(index != 0){
                node = node->next;
                index--;
            }
            definition = node->wd;
        }
    }
    else{
        definition = NULL;
    }
    
    assert((definition != NULL) == dict_exists(dict, word));
    return definition;
}

bool dict_exists(dict_t dict, string word) {
    return find_index_of_key(dict, word) != (-1);
}

unsigned int dict_length(dict_t dict) {
    return dict->size;
}

// removes the "index" element of the "list" list of nodes
static node_t remove_on_index(node_t list, int index) {
    int index_aux = index;
    struct _node_t *aux = list;
    if(index_aux == 0){
        list = list->next;
        aux = destroy_node(aux);
        aux = NULL;
    }
    else{
        struct _node_t *prev_node = list;
        int i = 0;
        while(i < index-1){
            prev_node = prev_node->next;
            i++;
        }
        aux = prev_node->next;
        prev_node->next = aux->next;
        aux = destroy_node(aux);
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
    dict->size = 0u;
    assert(dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    string word;
    string def;
    struct _node_t *aux_word = dict->words;
    struct _node_t *aux_def = dict->definitions;
    while(aux_word != NULL && aux_def != NULL){
        word = aux_word->wd;
        def = aux_def->wd;
        fprintf(file, "%s : %s\n", string_ref(word), string_ref(def));
        aux_word = aux_word->next;
        aux_def = aux_def->next;
    }
}

dict_t dict_destroy(dict_t dict) {
  dict = dict_remove_all(dict);
  free(dict);
  dict = NULL;
  return dict;
}
