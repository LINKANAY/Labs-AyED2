/*
Lab 00 - Ejercicio 1
Para compilar un archivo .c escribir en la terminal:
$> gcc -Wall -Wextra -std=c99 asoc.c -o picachuYoTeElijo
Para ejecutar escribir:
$> ./miprograma
Para compilar para gdb se debe agregar el flag -g al momento de compilar .c escribir en la
terminal:
$> gcc -Wall -Wextra -std=c99 -g miarchivo.c -o miprograma
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    res.is_upperbound = false;
    res.is_lowerbound = false;
    res.exists = false;
    res.where = false;
    unsigned int contadorU = 0;
    unsigned int contadorL = 0;
    for (unsigned int  i = 0; i < length; i++)
    {
        if (value == arr[i])
        {
            res.exists = true;
            res.where = i;        
        }              
        if (value > arr[i] || value == arr[i])
        {
            contadorU++;
            
        }
        if (value < arr[i] || value == arr[i])
        {
            contadorL++;
        }
    }
    if (contadorU == length)
    {
        res.is_upperbound = true;
    }
    if (contadorL == length)
    {
        res.is_lowerbound = true;
    }
    
    
    
    //
    // TODO: COMPLETAR
    //
    return res;
}

void pedir_arreglo(int n_max, int a[]);
int pedirEntero();

int main(void) {
    int lista[ARRAY_SIZE];
    pedir_arreglo(ARRAY_SIZE, lista);
    int numero = pedirEntero();

    struct bound_data result = check_bound(numero, lista, ARRAY_SIZE);

    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    printf("cota superior: %d\n", result.is_upperbound); // Imprime 1
    printf("cota inferior: %d\n", result.is_lowerbound); // Imprime 0
    if (result.is_lowerbound == false && result.is_upperbound == false)
    {
        if (result.exists)
        {
            printf("La posicion de %d es %d\n", numero, result.where); 
        }    
    }

    return EXIT_SUCCESS;
}

void pedir_arreglo(int n_max, int a[]){
    printf("Ingrese los %d elementos de la lista:\n", n_max);

    for (int i = 0; i < n_max; i++)
    {
        printf("Ingrese el elemento %d: ", i+1);
        scanf("%d", &a[i]);
    }   
}

int pedirEntero(){
  int x;  
  printf("Ingrese un numero para el analisis en la lista\n");
  scanf("%d", &x);
  return x;
}
