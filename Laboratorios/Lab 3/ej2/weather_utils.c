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

void preciMax(WeatherTable a, int  output[YEARS])
{
    unsigned int maxPrec = a[0][january][FST_DAY]._rainfall;
    int listPrec[MONTHS-1];
    for (unsigned int i = 0u; i < YEARS; i++)
    {
        for (month_t month = january; month <= december; month++)
        {
            for (unsigned int j = 0u; j < DAYS; j++)
            {
                if (maxPrec < a[i][month][j]._rainfall)
                {
                    maxPrec = a[i][month][j]._rainfall;
                }
            }
            listPrec[month] = maxPrec;
        }
        month_t maxMonth = january;
        for (month_t month = january; month < december; month++)
        {
            if (listPrec[month] > listPrec[month+1])
            {
                maxMonth = month;
            }            
        }
        output[i] = maxMonth;
        maxPrec = a[i][january][FST_DAY]._rainfall;
        
    }
}