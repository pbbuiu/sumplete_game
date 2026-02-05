//Pablo 25.2.4149
#ifndef FUNCOES_H //Proteção de chamada repetida
#define FUNCOES_H

//Struct's
typedef struct {
    int number;
    int mark; //0: normal 1: adicionado -1: removido
    int sum; //0: não faz parte 1: faz parte da soma 
    int x, y; //coordenadas
} Num;

//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Define's
#define TAM_F 3
#define TAM_M 5
#define TAM_D 7

//Protótipos
void fillMatrix(Num **matrix, int tam);
Num *createMatrix(int optionDifficulty, int **tips);
void charDown(char word[], char *c);
void clearDisplay();
void flush();
void menuOptions();
void showComands();


#endif
