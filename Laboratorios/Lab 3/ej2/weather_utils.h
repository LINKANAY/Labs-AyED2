#ifndef MI_LIB_H
#define MI_LIB_H

#include "array_helpers.h"
#include "weather_utils.h"

int tempMin(WeatherTable a);
void tempMax(WeatherTable a, int output[YEARS]);
void preciMax(WeatherTable a, int output[YEARS]);

#endif 