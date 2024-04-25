/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

static const int EXPECTED_DIM_VALUE = 2;

static const char *CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char *SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int best_profit(BakeryProductTable a)
{
    unsigned int max_profit = 0u;
    //COMPLETAR
    for (unsigned int city = 0; city < CITIES; city++)
    {
        for (unsigned int  seasson = low; seasson < SEASONS; seasson++)
        {
            unsigned int expenses = 0;
            unsigned int benefits = 0;
            expenses = a[city][seasson].flour_cant * a[city][seasson].flour_price;
            expenses += a[city][seasson].yeast_cant * a[city][seasson].yeast_price;
            expenses += a[city][seasson].butter_cant * a[city][seasson].butter_price;
            benefits = a[city][seasson].sale_value - expenses;
            if (benefits > max_profit)
            {
                max_profit = benefits;
            }               
        }
    }    
    return max_profit;
}

void array_from_file(BakeryProductTable array, const char *filepath)
{
    FILE *file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int city;
    unsigned int seasson;
    while (!feof(file))
    {
        /* COMPLETAR**/
        int res = fscanf(file, "##%u??%u ", &city, &seasson);

        if (res != EXPECTED_DIM_VALUE)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        /* COMPLETAR: Leer y guardar product en el array multidimensional*/
        /* Agregar las validaciones que considere necesarias*/
        /* Completar*/
        BakeryProduct bakery = bakery_product_from_file(file);
        array[city][seasson] = bakery;
    }
    fclose(file);
}

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name)
{
    /* Print the usage help of this program. */
    printf(
        "Usage: %s <input file path>\n\n"
        "Load bakery product data from a given file in disk.\n"
        "\n"
        "The input file must exist in disk and every line in it must have the following format:\n\n"
        "##<uint>\?\?<uint> (<uint>,<uint>) (<uint>,<uint>) (<uint>,<uint>) <uint> \n\n"
        "where each value represent: \n\n"
        "##<city_code>\?\?<season> (<flour_cant>,<flour_price>) (<yeast_cant>,<yeast_price>) (<butter_cant>,<butter_price>) <sales_value> \n\n"
        "Those elements must be integers and will be copied into the multidimensional integer array 'a'.\n"
        "\n\n",
        program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 */
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