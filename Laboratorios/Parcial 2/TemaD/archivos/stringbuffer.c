#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <assert.h>

#include "stringbuffer.h"

struct s_stringbuffer
{
    struct s_node *first;
    struct s_node *last;
    /*
     * COMPLETAR
     */
    unsigned int size;
};

struct s_node
{
    char c;
    struct s_node *nextchar;
};

typedef struct s_node *node_t;

// Representation invariant
static bool invrep(stringbuffer sb)
{
    bool valid = false;
    /*
     * COMPLETAR
     *
     */
    if (sb->size == 0)
    {
        valid = sb->first == NULL && sb->last == NULL;
    }
    else
    {
        valid = sb->first != NULL && sb->last != NULL;
    }

    return valid;
}

// Creates a single node in dynamic memory with a given char
static node_t create_node(char c)
{
    node_t newnode = NULL;
    /*
     * COMPLETAR
     *
     */
    newnode = malloc(sizeof(struct s_node));
    newnode->c = c;
    newnode->nextchar = NULL;

    assert(newnode != NULL);
    return newnode;
}

// Destroy a single node
static node_t destroy_node(node_t node)
{
    /*
     * COMPLETAR
     *
     */
    free(node);
    node = NULL;

    assert(node == NULL);
    return node;
}

// Public functions of the Abstract Data Type
stringbuffer stringbuffer_empty(void)
{
    /*
     * COMPLETAR
     *
     */
    stringbuffer newBuffer = NULL;
    newBuffer = malloc(sizeof(struct s_stringbuffer));
    newBuffer->first = NULL;
    newBuffer->last = NULL;
    newBuffer->size = 0;
    assert(newBuffer != NULL);
    return newBuffer;
}

stringbuffer stringbuffer_create(const char *word)
{
    assert(word != NULL);
    //node_t newnode = NULL;
   /*  node_t first = NULL;
    node_t last = NULL; */

    /*
     * COMPLETAR
     *
     */
    stringbuffer sb = stringbuffer_empty();
    unsigned int i = 0;
    while (word[i] != '\0')
    {
        sb = stringbuffer_append(sb, word[i]);
        i++;
    }
    sb->last->c = '\0';


    assert(invrep(sb) && !stringbuffer_is_empty(sb));
    return sb;
}

bool stringbuffer_is_empty(stringbuffer sb)
{
    /*
     * COMPLETAR
     *
     */
    return sb->size == 0;
}

stringbuffer stringbuffer_append(stringbuffer sb, const char c)
{
    /*
     * COMPLETAR
     *
     */
    node_t newnode = create_node(c);
    if (sb->first == NULL)
    {
        sb->first = newnode;
        sb->last = newnode;
    }
    else
    {
        sb->last->nextchar = newnode;
        sb->last = newnode;
    }
    sb->size++;
    assert(invrep(sb) && !stringbuffer_is_empty(sb));
    return sb;
}

char stringbuffer_char_at(stringbuffer sb, unsigned int index)
{
    assert(invrep(sb) && !stringbuffer_is_empty(sb) && index < stringbuffer_length(sb));
    unsigned pos = 0;
    node_t node = sb->first;
    while (pos < index)
    {
        node = node->nextchar;
        pos++;
    }
    return node->c;
}

stringbuffer stringbuffer_remove(stringbuffer sb, unsigned int index)
{
    assert(invrep(sb));
    node_t node = sb->first;
    node_t prev = NULL;
    unsigned pos = 0;
    /*
     * COMPLETAR
     *
     */
    if (index == 0)
    {
        sb->first = node->nextchar;
        destroy_node(node);
    }
    else
    {
        while (pos < index)
        {
            prev = node;
            node = node->nextchar;
            pos++;
        }
        prev->nextchar = node->nextchar;
        destroy_node(node);
    }
    sb->size--;

    assert(invrep(sb));
    return sb;
}

stringbuffer stringbuffer_replace(stringbuffer sb, const char c, unsigned int index)
{
    /*
     * COMPLETAR
     *
     */
    assert(invrep(sb) && index < stringbuffer_length(sb));
    node_t aux = sb->first;
    unsigned int i = 0;
    while (i < index)
    {
        aux = aux->nextchar;
        i++;
    }
    aux->c = c;

    assert(invrep(sb));
    return sb;
}

unsigned int stringbuffer_length(stringbuffer sb)
{
    /*
     * COMPLETAR
     *
     */
    return sb->size;
}

char *stringbuffer_to_string(stringbuffer sb)
{
    /*
     * COMPLETAR
     *
     */
    char *str = calloc((sb->size + 1), sizeof(char));
    node_t node = sb->first;
    unsigned int i = 0;
    while (node != NULL)
    {
        str[i] = node->c;
        node = node->nextchar;
        i++;
    }
    str[i] = '\0';
    return str;
}

void stringbuffer_dump(stringbuffer sb)
{
    assert(invrep(sb));
    node_t node = sb->first;
    while (node != NULL)
    {
        printf("%c", node->c);
        node = node->nextchar;
    }
    printf("\n");
}

stringbuffer stringbuffer_destroy(stringbuffer sb)
{
    /*
     * COMPLETAR
     *
     */
    node_t node = sb->first;
    while (node != NULL)
    {
        node_t killme = node;
        node = node->nextchar;
        killme = destroy_node(killme);
    }
    free(sb);
    sb = NULL;
    assert(sb == NULL);
    return sb;
}
