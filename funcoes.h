//Pablo 25.2.4149
#ifndef FUNCOES_H //Proteção de chamada repetida
#define FUNCOES_H

//Struct's
typedef struct {
    int number;
    int mark; //0: normal 1: adicionado -1: removido
    int sum; //0: não faz parte 1: faz parte da soma 
} Num;

//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Define's
#define TAM_COMMANDS_GAME 16
#define TAM_COMMANDS 10
#define TAM_F 3
#define TAM_M 5
#define TAM_D 7

//Protótipos
void gameControls(int tip[], Num **matrix, int tam);
//void gameInterface(int tip[], Num **matrix, int tam);
void tips(int **tip, Num **matrix, int tam);
void fillMatrix(Num **matrix, int tam);
Num **createMatrix(int optionDifficulty);
void charDown(char word[], char *c);
void clearDisplay();
void flush();
void menuOptions();
void showCommands();


#endif
