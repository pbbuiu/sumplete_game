//Pablo Henrique 25.2.4149
#include "funcoes.h"


void showComands(){
    printf("\nComandos do jogo: \n");
    printf("ajuda: Exibe os comandos do jogo\n");
    printf("sair: Sair do Jogo\n");
    printf("novo: Começar um novo jogo\n");
    printf("carregar: Carregar um jogo salvo em arquivo\n");
    printf("ranking: Exibir o ranking\n");
    printf("salvar: Salva o jogo atual\n");
    printf("dica: Marca uma posição no jogo\n");
    printf("resolver: Resolve o jogo atual\n");
    printf("adicionar <lin> <col>: adiciona a posição na soma\n");
    printf("remover <lin> <col>: remove a posição da soma\n\n");
}


void menuOptions(){
    int i=0;
    char option[10];
    while (i == 0){
        scanf("%s", option);
        if (strcmp (option, "ajuda") == 0){
            clearDisplay();
            showComands();
            continue;
        }
    }
}

void clearDisplay(){
    printf("\e[1;1H\e[2J");
}
/*
Sumario:
5 - Mostrar comandos do jogo
20 - Menu de opções
*/

