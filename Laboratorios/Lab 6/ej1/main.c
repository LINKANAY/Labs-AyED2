/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */

void print_help(char *program_name)
{
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[])
{
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2)
    {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath)
{
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1)
    {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size)
    {
        abb_elem elem;
        res = fscanf(file, " %d ", &(elem));
        if (res != 1)
        {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

        ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[])
{
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
    int choice;
    abb_elem elem;
    abb_ordtype ord = ABB_IN_ORDER; // Default order type

    do
    {
        printf("\nSeleccione una operación:\n");
        printf("1. Mostrar árbol por pantalla\n");
        printf("2. Agregar un elemento\n");
        printf("3. Eliminar un elemento\n");
        printf("4. Chequear existencia de elemento\n");
        printf("5. Mostrar longitud del árbol\n");
        printf("6. Mostrar raiz, máximo y mínimo del árbol\n");
        printf("7. Salir\n");
        printf("Elección: ");
        scanf("%d", &choice);

        /*
         * Modificar e implementar con un ciclo una interfaz que permita al usuario
         * realizar una de las siguientes operaciones en cada iteración:
         *
         * 1 ........ Mostrar árbol por pantalla
         * 2 ........ Agregar un elemento
         * 3 ........ Eliminar un elemento
         * 4 ........ Chequear existencia de elemento
         * 5 ........ Mostrar longitud del árbol
         * 6 ........ Mostrar raiz, máximo y mínimo del árbol
         * 7 ........ Salir
         *
         * Se debe solicitar un número de entrada para realizar una de las acciones.
         *
         * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
         * elemento a agregar, eliminar o chequear respectivamente.
         *
         * Al salir debe liberarse toda la memoria utilizada.
         *
         */
        switch (choice)
        {
        case 1:
            printf("Seleccione el orden de recorrido (1: IN_ORDER, 2: PRE_ORDER, 3: POST_ORDER): ");
            int order;
            scanf("%d", &order);
            if (order == 1)
                ord = ABB_IN_ORDER;
            else if (order == 2)
                ord = ABB_PRE_ORDER;
            else if (order == 3)
                ord = ABB_POST_ORDER;
            abb_dump(tree, ord);
            printf("\n");
            break;
        case 2:
            printf("Ingrese el elemento a agregar: ");
            scanf("%d", &elem);
            tree = abb_add(tree, elem);
            break;
        case 3:
            printf("Ingrese el elemento a eliminar: ");
            scanf("%d", &elem);
            tree = abb_remove(tree, elem);
            break;
        case 4:
            printf("Ingrese el elemento a chequear: ");
            scanf("%d", &elem);
            if (abb_exists(tree, elem))
            {
                printf("El elemento %d existe en el árbol.\n", elem);
            }
            else
            {
                printf("El elemento %d no existe en el árbol.\n", elem);
            }
            break;
        case 5:
            printf("La longitud del árbol es: %u\n", abb_length(tree));
            break;
        case 6:
            if (!abb_is_empty(tree))
            {
                printf("Raíz: %d\n", abb_root(tree));
                printf("Mínimo: %d\n", abb_min(tree));
                printf("Máximo: %d\n", abb_max(tree));
            }
            else
            {
                printf("El árbol está vacío.\n");
            }
            break;
        case 7:
            tree = abb_destroy(tree);
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
            break;
        }
    } while (choice != 7);

    return (EXIT_SUCCESS);
}
