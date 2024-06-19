#include <assert.h>
#include "dict.h"
#include "key_value.h"
#include <stdlib.h>

struct _node_t
{
    string word;
    string definition;
    struct _node_t *next;
};

struct _dict_t
{
    node_t words;
    unsigned int size;
};

static bool invrep(dict_t d)
{
    /* needs implementation */ if (d == NULL)
        return false;

    node_t current = d->words;
    unsigned int count = 0;

    while (current != NULL)
    {
        if (current->word == NULL || current->definition == NULL)
            return false;
        current = current->next;
        count++;
    }

    return (count == d->size);
}

dict_t dict_empty(void)
{
    dict_t dict = NULL;
    /* needs implementation */
    dict = malloc(sizeof(struct _dict_t));
    if (dict == NULL) {
        perror("Unable to allocate memory for dictionary");
        exit(EXIT_FAILURE);
    }
    dict->words = NULL;
    dict->size = 0;
    return dict;
}

static node_t create_node(string word, string def)
{
    node_t node = malloc(sizeof(struct _node_t));
    if (node == NULL)
    {
        perror("Unable to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    node->word = word;
    node->definition = def;
    node->next = NULL;
    return node;
}

static node_t destroy_node(node_t node)
{
    if (node != NULL)
    {
        string_destroy(node->word);
        string_destroy(node->definition);
        free(node);
    }
    return NULL;
}

static node_t remove_on_index(node_t list, int index)
{
    if (index == 0)
    {
        node_t temp = list;
        list = list->next;
        destroy_node(temp);
    }
    else
    {
        node_t prev = list;
        for (int i = 0; i < index - 1; i++)
        {
            prev = prev->next;
        }
        node_t temp = prev->next;
        prev->next = temp->next;
        destroy_node(temp);
    }
    return list;
}

static int find_index_of_key(dict_t dict, string word)
{
    int index = 0;
    node_t current = dict->words;

    while (current != NULL)
    {
        if (string_eq(current->word, word))
        {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

dict_t dict_add(dict_t dict, key_t word, value_t def)
{
    /* needs implementation */
    int index = find_index_of_key(dict, word);
    if (index != -1)
    {
        node_t current = dict->words;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        string_destroy(current->definition);
        current->definition = def;
    }
    else
    {
        node_t new_node = create_node(word, def);
        if (dict->words == NULL || string_less(word, dict->words->word))
        {
            new_node->next = dict->words;
            dict->words = new_node;
        }
        else
        {
            node_t current = dict->words;
            while (current->next != NULL && string_less(current->next->word, word))
            {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
        dict->size++;
    }
    return dict;
}

value_t dict_search(dict_t dict, key_t word)
{
    key_t def = NULL;
    /* needs implementation */
    node_t current = dict->words;
    while (current != NULL)
    {
        if (string_eq(current->word, word))
        {
            return current->definition;
        }
        current = current->next;
    }
    return def;
}

bool dict_exists(dict_t dict, key_t word)
{
    /* needs implementation */
    return dict_search(dict, word) != NULL;
}

unsigned int dict_length(dict_t dict)
{
    /* needs implementation */
    return dict->size;
}

dict_t dict_remove(dict_t dict, key_t word)
{
    /* needs implementation */
    int index = find_index_of_key(dict, word);
    if (index != -1)
    {
        dict->words = remove_on_index(dict->words, index);
        dict->size--;
    }
    return dict;
}

dict_t dict_remove_all(dict_t dict)
{
    /* needs implementation */
    while (dict->words != NULL)
    {
        dict->words = remove_on_index(dict->words, 0);
    }
    dict->size = 0;

    assert(invrep(dict));
    return dict;
    return dict;
}

void dict_dump(dict_t dict, FILE *file)
{
    /* needs implementation */
    node_t current = dict->words;
    while (current != NULL)
    {
        fprintf(file, "%s : %s\n", string_ref(current->word), string_ref(current->definition));
        current = current->next;
    }
}

dict_t dict_destroy(dict_t dict)
{
    /* needs implementation */
    dict = dict_remove_all(dict);
    free(dict);
    dict = NULL;
    return dict;
}
