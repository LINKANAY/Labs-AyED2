#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include "weather_utils.h"

int tempMin(WeatherTable a)
{
    int minimaTemp = a[0][0][FST_DAY]._min_temp;
    for (int i = 0u; i < YEARS; i++)
    {
        for (month_t month = january; month <= december; month++)
        {
            for (unsigned u = 0u; u < DAYS; u++)
            {
                if (minimaTemp > a[i][month][u]._min_temp)
                {
                    minimaTemp = a[i][month][u]._min_temp;
                }
            }
        }
    }
    return minimaTemp;
}

void tempMax(WeatherTable a, int output[YEARS])
{
    int tempeMax = a[0][january][FST_DAY]._max_temp;
    for (unsigned int i = 0u; i < YEARS; i++)
    {
        for (month_t month = january; month <= december; month++)
        {
            for (unsigned int j = 0u; j < DAYS; j++)
            {
                if (tempeMax < a[i][month][j]._max_temp)
                {
                    tempeMax = a[i][month][j]._max_temp;
                }
            }
        }
        output[i] = tempeMax;
        tempeMax = a[i][january][FST_DAY]._max_temp;
    }
}

void preciMax(WeatherTable a, const char *output[YEARS])
{
    int listPrec[MONTHS - 1];

    static const char *month_names[] = {
        "January", "February", "March", "April", "May", "June", "July", "August",
        "September", "October", "November", "December"};

    for (unsigned int i = 0u; i < YEARS; i++)
    {
        for (month_t month = january; month <= december; month++)
        {
            unsigned int maxPrec = a[i][month][FST_DAY]._rainfall;
            for (unsigned int j = 0u; j < DAYS; j++)
            {
                if (maxPrec < a[i][month][j]._rainfall)
                {
                    maxPrec = a[i][month][j]._rainfall;
                }
            }
            listPrec[month] = maxPrec;
        }
        int maxMonth = listPrec[january];
        month_t mes = january;
        for (month_t month = january; month <= december; month++)
        {
            if (maxMonth < listPrec[month])
            {
                maxMonth = listPrec[month];
                mes = (month);
            }
        }
        output[i] = month_names[mes];
    }
}