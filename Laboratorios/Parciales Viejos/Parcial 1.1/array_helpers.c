/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
 * @brief returns true when reach last line in flight file
 * @return True when is the last line of the file, False otherwise
 */
static bool is_last_line(unsigned int hour, unsigned int type)
{
  return hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DelayTable a)
{
  for (unsigned int type = 0u; type < TYPE; ++type)
  {
    for (unsigned int hour = 0u; hour < HOURS; ++hour)
    {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: %s flight with %u passengers arrived at %u:00, with %u delay",
              f.code,
              f.type == 0 ? "last_mile" : "layover",
              f.passengers_amount,
              f.hour - 1,
              f.delay);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int compensation_cost(DelayTable a, unsigned int h)
{
  /* COMPLETAR */
  unsigned int compensation = 0u;
  for (unsigned int type = 0; type < TYPE; type++)
  {
    for (unsigned int hour = 0; hour < h; hour++)
    {
      if (type == 0)
      {
        if (a[type][hour].delay > MAX_LM_DELAY_ALLOWED)
        {
          compensation += a[type][hour].passengers_amount * COMPENSATION_PER_MINUTE * a[type][hour].delay;
        }
      }
      else
      {
        if (a[type][hour].delay > MAX_LAYOVER_DELAY_ALLOWED)
        {
          compensation += a[type][hour].passengers_amount * COMPENSATION_PER_MINUTE * a[type][hour].delay;
        }
      }
    }
  }

  return compensation;
}

void array_from_file(DelayTable array, const char *filepath)
{
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL)
  {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (!feof(file))
  {
    /* COMPLETAR: lectura de cada vuelo */
    Flight last_mile_info = flight_from_file(file);
    printf("datos: %u, %u, %u\n", last_mile_info.hour, last_mile_info.delay, last_mile_info.passengers_amount);
    last_mile_info.type = last_mile;
    Flight layover_info = flight_from_file(file);
    printf("datos2: %u, %u, %u\n", layover_info.hour, layover_info.delay, layover_info.passengers_amount);
    layover_info.type = layover;
    /* COMPLETAR: lectura de codigo de vuelo */
    int res = fscanf(file, " #%c# ", &code);
    if (res != 1)
    {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    printf("codigo: %c\n", code);
    last_mile_info.code = code;
    layover_info.code = code;
    /* Completar acá: completar y guardar ambos Flight en el array multidimensional*/

    array[last_mile][last_mile_info.hour - 1] = last_mile_info;
    array[layover][layover_info.hour - 1] = layover_info;
  }
  i++;

  fclose(file);
}

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name)
{
  /* Print the usage help of this program. */
  printf("Usage: %s <input file path>\n\n"
         "Load flight data from a given file in disk.\n"
         "\n"
         "The input file must exist in disk and every line in it must have the following format:\n\n"
         "<code> <flight type> <hour> <passengers> <flight type> <hour> <passengers>\n\n"
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
