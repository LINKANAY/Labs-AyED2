#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <assert.h>

#include "pokerdeck.h"

struct s_pokerdck
{
    /*
     * COMPLETAR
     */
    unsigned int size;
    struct s_node *first;
    struct s_node *last;
    unsigned int count[CARD_SUITS];
};

struct s_node
{
    cardnum_t num;
    cardsuit_t suit;
    struct s_node *nextcard;
};

typedef struct s_node *node_t;

// Auxiliar dump functions
static void dump_suit(cardsuit_t suit)
{
    printf("%s", suit == spades ? "♠️  " : suit == hearts ? "♥️  "
                                      : suit == diamonds ? "♦️  "
                                      : suit == clubs    ? "♣️  "
                                                         : "???");
}

static void dump_num(cardnum_t num)
{
    if (1 < num && num < 11)
    {
        printf("%-2d", num);
    }
    else
    {
        printf("%-2s", num == 1 ? "A" : num == 11 ? "J"
                                    : num == 12   ? "Q"
                                    : num == 13   ? "K"
                                                  : "???");
    }
}

// Representation invariant
static bool invrep(pokerdeck deck)
{
    bool valid = true;
    /*
     * COMPLETAR
     *
     */
    valid = valid && (deck != NULL);
    valid = valid && ((deck->first == NULL && deck->last == NULL) || (deck->first != NULL && deck->last != NULL));

    unsigned int totalCount = 0;
    for (unsigned int i = 0; i < CARD_SUITS; i++)
    {
        totalCount += deck->count[i];
        valid = valid && (totalCount == deck->size);
    }
    return valid;
}

// Creates a single node in dynamic memory with a given card
static node_t create_node(cardnum_t num, cardsuit_t suit)
{
    node_t newnode = NULL;
    /*
     * COMPLETAR
     *
     */
    newnode = malloc(sizeof(struct s_node));
    assert(newnode != NULL);
    newnode->num = num;
    newnode->suit = suit;
    newnode->nextcard = NULL;
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
pokerdeck pokerdeck_empty(void)
{
    /*
     * COMPLETAR
     *
     */
    pokerdeck deck = malloc(sizeof(struct s_pokerdck));
    assert(deck != NULL);
    deck->size = 0;
    deck->first = NULL;
    deck->last = NULL;
    deck->count[spades] = 0;
    deck->count[hearts] = 0;
    deck->count[diamonds] = 0;
    deck->count[clubs] = 0;

    assert(pokerdeck_is_empty(deck) && invrep(deck));
    return deck;
}

bool pokerdeck_is_empty(pokerdeck deck)
{
    /*
     * COMPLETAR
     *
     */
    return deck->first == NULL;
}

pokerdeck pokerdeck_add(pokerdeck deck, cardnum_t num, cardsuit_t suit)
{
    /*
     * COMPLETAR
     *
     */
    assert(invrep(deck));
    node_t newnode = create_node(num, suit);

    if (pokerdeck_is_empty(deck))
    {
        deck->first = newnode;
        deck->last = newnode;
    }
    else
    {
        deck->last->nextcard = newnode;
        deck->last = newnode;
    }
    deck->size += 1;
    deck->count[suit] += 1;

   // assert(invrep(deck) && !pokerdeck_is_empty(deck));
    return deck;
}

pokerdeck pokerdeck_push(pokerdeck deck, cardnum_t num, cardsuit_t suit)
{
    assert(invrep(deck));
    node_t newnode = create_node(num, suit);
    newnode->nextcard = deck->first;
    deck->first = newnode;
    /*
     * COMPLETAR: si fuera necesario actualizar datos de la estructura
     * principal.
     *
     */
    if (deck->last == NULL)
    {
        deck->last = newnode;
    }
    deck->size += 1;
    deck->count[suit] += 1;

    assert(invrep(deck) && !pokerdeck_is_empty(deck));
    return deck;
}

pokerdeck pokerdeck_pop(pokerdeck deck, cardnum_t *popped_num, cardnum_t *popped_suit)
{
    /*
     * COMPLETAR
     *
     */
    node_t popped_node = deck->first;
    if (deck->first == deck->last)
    {
        deck->first = NULL;
        deck->last = NULL;
    }
    else
    {
        deck->first = popped_node->nextcard;
    }
    deck->size -= 1;
    deck->count[popped_node->suit] -= 1;

    if (popped_num != NULL)
    {
        *popped_num = popped_node->num;
    }
    if (popped_suit != NULL)
    {
        *popped_suit = popped_node->suit;
    }

    destroy_node(popped_node);

    return deck;
}

unsigned int pokerdeck_length(pokerdeck deck)
{
    /*
     * COMPLETAR
     *
     */
    unsigned int length = deck->size;
    return length;
}

pokerdeck pokerdeck_remove(pokerdeck deck, cardnum_t num, cardsuit_t suit)
{
    /*
     * COMPLETAR
     *
     */
    node_t aux = NULL;
    node_t prev = NULL;
    if (!pokerdeck_is_empty(deck))
    {
        aux = deck->first;
        while (aux != NULL && (aux->num != num || aux->suit != suit))
        {
            prev = aux;
            aux = aux->nextcard;
        }

        if (aux != NULL)
        {
            if (prev == NULL)
            {
                deck = pokerdeck_pop(deck, NULL, NULL);
            }
            else if (aux == deck->last)
            {
                deck->last = prev;
                prev->nextcard = NULL;
                deck->size -= 1;
                deck->count[aux->suit] -= 1;
                destroy_node(aux);
            }
            else
            {
                prev->nextcard = aux->nextcard;
                deck->size -= 1;
                deck->count[aux->suit] -= 1;
                destroy_node(aux);
            }
        }
    }

    return deck;
}

unsigned int pokerdeck_count(pokerdeck deck, cardsuit_t suit)
{
    /*
     * COMPLETAR
     *
     */
    unsigned int count = deck->count[suit];

    return count;
}

struct card *pokerdeck_to_array(pokerdeck deck)
{
    /*
     * COMPLETAR
     *
     */
    struct card *array = NULL;
    node_t aux = NULL;
    unsigned int length = pokerdeck_length(deck);
    if (length != 0)
    {
        array = calloc((size_t)length, sizeof(struct card));
        for (unsigned int i = 0; i < length; i++)
        {
            array[i].num = aux->num;
            array[i].suit = aux->suit;
            aux = aux->nextcard;
        }
    }
    return array;
}

void card_dump(cardnum_t num, cardsuit_t suit)
{
    printf("|");
    dump_num(num);
    printf(" ");
    dump_suit(suit);
    printf("|");
}

void pokerdeck_dump(pokerdeck deck)
{
    assert(invrep(deck));
    node_t node = deck->first;
    while (node != NULL)
    {
        card_dump(node->num, node->suit);
        printf(" ");
        node = node->nextcard;
    }
    printf("\n");
}

pokerdeck pokerdeck_destroy(pokerdeck deck)
{
    /*
     * COMPLETAR
     *
     */
    while (!pokerdeck_is_empty(deck))
    {
        deck = pokerdeck_pop(deck, NULL, NULL);
    }
    free(deck);
    deck = NULL;
    
    return deck;
}
