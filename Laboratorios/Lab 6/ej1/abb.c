#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb
{
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b)
{
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b)
{
    return a < b;
}

static bool invrep(abb tree)
{
    bool b = true;

    if (abb_is_empty(tree))
    {
        b = true;
    }

    if (!abb_is_empty(tree))
    {
        if (!abb_is_empty(tree->left))
        {
            b = (!elem_less(tree->elem, tree->left->elem) && invrep(tree->left));
        }
        if (!abb_is_empty(tree->right))
        {
            b = (elem_less(tree->elem, tree->right->elem) && invrep(tree->right));
        }
    }

    return b;
}

abb abb_empty(void)
{
    abb tree;
    /*
     * Needs implementation
     */
    tree = NULL;

    assert(abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e)
{
    assert(invrep(tree));
    /*
     * Needs implementation
     */
    if (tree == NULL)
    {
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    }
    else if (elem_less(e, tree->elem))
    {
        tree->left = abb_add(tree->left, e);
    }
    else if (elem_less(tree->elem, e))
    {
        tree->right = abb_add(tree->right, e);
    }

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree)
{
    
    /*
     * Needs implementation
     */
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e)
{
    bool exists = false;
    assert(invrep(tree));
    /*
     * Needs implementation
     */
    if (tree == NULL)
    {
        exists = false;
    }
    else if (elem_eq(e, tree->elem))
    {
        exists = true;
    }
    else if (elem_less(e, tree->elem))
    {
        exists = abb_exists(tree->left, e);
    }
    else if (elem_less(tree->elem, e))
    {
        exists = abb_exists(tree->right, e);
    }

    assert(abb_length(tree) != 0 || !exists);
    return exists;
}

unsigned int abb_length(abb tree)
{
    unsigned int length = 0;
    assert(invrep(tree));
    /*
     * Needs implementation
     */
    if (tree != NULL)
    {
        length = 1 + abb_length(tree->left);
        length += abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e)
{
    assert(invrep(tree));
    /*
     * Needs implementation
     */
    if (tree == NULL)
    {
        return NULL;
    }
    else if (elem_less(e, tree->elem))
    {
        tree->left = abb_remove(tree->left, e);
    }
    else if (elem_less(tree->elem, e))
    {
        tree->right = abb_remove(tree->right, e);
    }
    else
    {
        if (tree->left == NULL && tree->right == NULL)
        {
            free(tree);
            tree = NULL;
        }
        else if (tree->left == NULL)
        {
            abb aux = tree;
            tree = tree->right;
            free(aux);
        }
        else if (tree->right == NULL)
        {
            abb aux = tree;
            tree = tree->left;
            free(aux);
        }
        else
        {
            abb_elem min = abb_min(tree->right);
            tree->elem = min;
            tree->right = abb_remove(tree->right, min);
        }
    }

    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree)
{
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    /*
     * Needs implementation
     */
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree)
{
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    /*
     * Needs implementation
     */
    abb pointer = tree;
    while (pointer->right != NULL)
    {
        pointer = pointer->right;
    }
    max_e = pointer->elem;

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree)
{
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    /*
     * Needs implementation
     */
    abb pointer = tree;
    while (pointer->left != NULL)
    {
        pointer = pointer->left;
    }
    min_e = pointer->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord)
{
    assert(invrep(tree) && (ord == ABB_IN_ORDER ||
                            ord == ABB_PRE_ORDER ||
                            ord == ABB_POST_ORDER));
    /*
     * c) Needs implementation: use the dump order indicated by `ord`
     *
     */

    // Implementing in-order as default
    if (tree != NULL)
    {
        if (ord == ABB_IN_ORDER)
        {
            abb_dump(tree->left, ord);
            printf("%d ", tree->elem);
            abb_dump(tree->right, ord);
        }
        else if (ord == ABB_PRE_ORDER)
        {
            printf("%d ", tree->elem);
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
        }
        else if (ord == ABB_POST_ORDER)
        {
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
            printf("%d ", tree->elem);
        }
    }
}

abb abb_destroy(abb tree)
{
    assert(invrep(tree));
    /*
     * Needs implementation
     */
    if (tree == NULL)
    {
        return NULL;
    }
    tree->left = abb_destroy(tree->left);
    tree->right = abb_destroy(tree->right);
    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree;
}
