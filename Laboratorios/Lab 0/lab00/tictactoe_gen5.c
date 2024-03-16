/*
Lab 00 - Ejercicio 3-b
Para compilar un archivo .c escribir en la terminal:
$> gcc -Wall -Wextra -std=c99 asoc.c -o picachuYoTeElijo
Para ejecutar escribir:
$> ./miprograma
Para compilar para gdb se debe agregar el flag -g al momento de compilar .c escribir en la
terminal:
$> gcc -Wall -Wextra -std=c99 -g miarchivo.c -o miprograma
gdb ./miprograma
break miprograma:numerodelineadecodigo
run
enable
next
step
continue
finish


*/

#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */
#include <assert.h>  /* assert() */

#define SIZE 3
#define CELL_MAX (SIZE * SIZE - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[SIZE][SIZE])
{
    int cell = 0;

    print_sep(SIZE);
    for (int row = 0; row < SIZE; ++row) {
        for (int column = 0; column < SIZE; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(SIZE);
    }
}

char get_winner(char board[SIZE][SIZE])
{
    char winner = '-';
    int diagonalI = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (board[0][0] == board[i][i])
        {
            diagonalI++;
        }        
    }
    if (diagonalI == SIZE)
    {
        winner = board[0][0];
    }

    int diagonalD = 0;
    int j = (SIZE - 1);
    for (int i = 0; i < SIZE; i++)
    {
        while (j > i)
        {
            if (board[0][j] == board[i+1][j-1])
            {
                printf ("el valor de diagonalD antes: %d\n", j);
                diagonalD++;
                printf ("el valor de diagonalD despues: %d\n", j);
                
            }
            
            break;
            
        }   
        j--;    
    }
    
    if (diagonalD == SIZE)
    {
        winner = board[0][SIZE];
    }
    
/*     
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == board[3][3] )|| (board[3][0] == board[2][1] && board[3][0] == board[1][2] && board[3][0] == board[0][3]) )
        {
            winner = board[1][1]; 
        }
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == board[i][3] )
        {
            winner = board[i][0];
            break;
        }
        else if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == board[3][i])
        {
            winner = board[0][i];
            break;
        }              
    } */
    return winner;
}

bool has_free_cell(char board[SIZE][SIZE])
{
    bool free_cell=false;
    char lugar = '-';
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (lugar == board[i][j])
            {
                free_cell = true;
            }
        }
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");
    char board[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = '-';
        }
        
    }
    
    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / SIZE;
            int colum = cell % SIZE;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
