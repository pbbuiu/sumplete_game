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


void clearDisplay(){
    printf("\e[1;1H\e[2J");
}


void charDown(char word[], char *c){
    if (word != NULL){
        for (int i=0;i<strlen(word);i++)
            if (word[i] <= 'Z' && word[i] >= 'A')
                word[i] = word[i]+('a'-'A');
    }
    if (c != NULL){
        if (*c <= 'Z' && *c >= 'A')
            *c = (*c)+('a'-'A');
    }
}

void flush(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int difficultyOptions(){
    int i=0;
    char optionDifficulty;
    clearDisplay();
        printf("\n(x)Voltar\nDigite o nível de dificuldade (F - 3x3) (M - 5x5) (D - 7x7): ");
    while (i == 0){
        scanf("%c", &optionDifficulty);
        flush();
        charDown(NULL , &optionDifficulty);
        if (optionDifficulty == 'x'){
            i = -1;
            break;
        }
        else if (optionDifficulty == 'f');
        else if (optionDifficulty == 'm');
        else if (optionDifficulty == 'd');
        else{
            clearDisplay();
            printf("Erro: comando incompatível, tente novamente\n");
            printf("\n(x)Voltar\nDigite o nível de dificuldade (F - 3x3) (M - 5x5) (D - 7x7): ");
        }
    }
    return i;
}

void newGame(){
    int i = 0, option = difficultyOptions();
    while (i == 0){
        if (option == -1){
            i = -1;
            clearDisplay();
            showComands();
        }
        else if (option == 1);
        else if (option == 2);
        else if (option == 3);
        
    }
}




void menuOptions(){
    int i=0;
    char option[10];
    while (i == 0){
        scanf("%s", option);
        flush();
        charDown(option, NULL);
        if (strcmp (option, "ajuda") == 0){
            clearDisplay();
            showComands();
            continue;
        }
        else if (strcmp (option, "sair") == 0)
            i = -1;
        else if (strcmp (option, "novo") == 0)
            newGame();
        else if (strcmp (option, "carregar") == 0);
        else if (strcmp (option, "ranking") == 0);
        else if (strcmp (option, "salvar") == 0);
        else if (strcmp (option, "dica") == 0);
        else if (strcmp (option, "resolver") == 0);
        else if (strcmp (option, "adicionar") == 0);
        else if (strcmp (option, "remover") == 0);

        else
            printf("Erro: comando incompatível, tente novamente\n");
        }
}


/*
Sumario:
5 - Mostrar comandos do jogo
20 - Limpar tela
25 - Caracteres minúsculos
 - Menu de opções
*/

