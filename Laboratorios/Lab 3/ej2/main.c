/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "weather_utils.h"

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[])
{
  char *filepath = NULL;

  /* parse the filepath given in command line arguments */
  filepath = parse_filepath(argc, argv);

  /* create an array with the type of tclimate */
  WeatherTable array;

  /* parse the file to fill the array and obtain the actual length */
  array_from_file(array, filepath);

  /* show the ordered array in the screen */
  // array_dump(array);

  /*search the minimum tempperature*/
  int minTemp = tempMin(array);

  /*show the minimum tempperature*/
  printf("La temperatura minima entre %u y %u fue: %d\n", FST_YEAR, LST_YEAR, minTemp);

  int output[YEARS];
  tempMax(array, output);
  for (unsigned int i = 0; i < YEARS; i++)
  {
    printf("La temperatura mas alta de %u fue de: %d\n", i + 1980, output[i]);
  }
  int output2[YEARS];
  preciMax(array, output2);
  for (unsigned int i = 0; i < YEARS; i++)
  {
    printf("El mes que registro mas precipitaciones en %u fue: %d\n", i + 1980, output2[i]);
  }

  return (EXIT_SUCCESS);
}
