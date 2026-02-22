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
#define ANSI_RESET            "\x1b[0m"
#define ANSI_BOLD             "\x1b[1m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define GREEN(string) ANSI_COLOR_GREEN string ANSI_RESET
#define RED(string)   ANSI_COLOR_RED   string ANSI_RESET
#define BOLD(string)  ANSI_BOLD        string ANSI_RESET
#define TAM_DIFFICULTY 3
#define TAM_NAME 22
#define TAM_COMMANDS_GAME 29
#define TAM_COMMANDS 10
#define TAM_F 3
#define TAM_M 5
#define TAM_D 7

//Protótipos
void menuOptions();
void newGame(char name[]);
void gameControls(int tip[], Num **matrix, int tam, char name[]);
void saveGame(Num **matrix, int tip[], char name[], int tam, char gameName[]);
void freeMatrix(Num **matrix, int tip[], int tam);
void gameInterface(int tip[], Num **matrix, int tam);
void tips(int **tip, Num **matrix, int tam);
void fillMatrix(Num **matrix, int tam);
Num **createMatrix(int optionDifficulty);
int difficultyOptions();
void flush();
void charDown(char word[], char *c);
void clearDisplay();
void showCommands();


#endif
