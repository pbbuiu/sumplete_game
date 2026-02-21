//Pablo Henrique 25.2.4149
#include "funcoes.h"

//Mostra todos os comandos do menu inicial
void showCommands(){
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

//Limpa a tela
void clearDisplay(){
    printf("\e[1;1H\e[2J");
}

//Transforma as letras em minúsculas
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

//O usuário escolhe qual será a opção de dificuldade
int difficultyOptions(){
    int i=0;
    char optionDifficulty[TAM_DIFFICULTY];
    clearDisplay();
    while (i == 0){
        printf("\n(x)Voltar\nDigite o nível de dificuldade (F - 3x3) (M - 5x5) (D - 7x7): ");
        fgets(optionDifficulty, TAM_DIFFICULTY, stdin);
        if (optionDifficulty[1] != '\n'){
            flush();
            clearDisplay();
            printf("Erro: comando incompatível, tente novamente\n");
            continue;
        }
        charDown(optionDifficulty, NULL);
        if (optionDifficulty[0] == 'x')
            i = -1;
        else if (optionDifficulty[0] == 'f')
            i = 1;
        else if (optionDifficulty[0] == 'm')
            i = 2;
        else if (optionDifficulty[0] == 'd')
            i = 3;
        else{
            clearDisplay();
            printf("Erro: comando incompatível, tente novamente\n");
        }
    }
    return i;
}

//Cria a matriz e o vetor com as dicas de acordo com a dificuldade selecionada pelo usuário
Num **createMatrix(int optionDifficulty){
    Num **matrix;
    matrix = malloc (optionDifficulty * sizeof(Num*));
    for (int i=0;i<optionDifficulty;i++)
        matrix[i] = malloc (optionDifficulty * sizeof(Num));
    fillMatrix(matrix, optionDifficulty);
    return matrix;
}    

//Preenche a matriz com números aleatórios, as respectivas posições
void fillMatrix(Num **matrix, int tam){
    int contador=0;
    srand (time(NULL));
    do{
        for (int i=0;i<tam;i++)
            for (int j=0;j<tam;j++){
                matrix[i][j].number = rand() % 9 + 1;
                matrix[i][j].sum = rand() % 2;
                matrix[i][j].mark = 0;
                if (matrix[i][j].sum == 1)
                    contador++;
            }
        if (contador < (tam*tam)/2-1 || contador > (tam*tam)/2+1)
        contador = 0;
    } while (contador == 0);
}

//Cria as dicas com base nos numeros que estão na tabela
void tips(int **tip, Num **matrix, int tam){
    *tip = malloc ((tam*2) * sizeof(int));
    for (int i=0;i<tam;i++){
        for (int j=0;j<tam;j++)
            if (matrix[i][j].sum == 1)
                (*tip)[i] += matrix[i][j].number;
        //printf("%d \n", (*tip)[i]);
    }
    for (int i=0;i<tam;i++){
        for (int j=0;j<tam;j++)
            if (matrix[j][i].sum == 1)
                (*tip)[i+tam] += matrix[j][i].number;
        //printf("%d \n", (*tip)[i+tam]);
    }
}
/*
//Mostra a interface do jogo
void gameInterface(int tip[], Num **matrix, int tam){
    printf("\n    \u2503");
    //Canto de cima
    for (int i=0;i<tam;i++)
        printf(" %2d  \u2503", (i+1));

    //Meio
    for (int i=0;i<tam;i++){
        printf("\n");
        printf("\u2501\u2501\u2501\u2501");
        for (int j=0;j<tam+1;j++){
            printf("\u254b");
            for (int k=0;k<5;k++)
                printf("\u2501");
        }
        printf("\n%2d  ", i+1);
        for (int j=0;j<tam;j++)
            printf("\u2503 %2d  ", matrix[i][j].number);
        printf("\u2503 %2d", tip[i]);
    }
    printf("\n\u2501\u2501\u2501\u2501");
    for (int j=0;j<tam+1;j++){
        printf("\u254b");
        for (int k=0;k<5;k++)
            printf("\u2501");
    }
    printf("\n    \u2503");
    for (int i=0;i<tam;i++) 
        printf(" %2d  \u2503", tip[i+tam]);
    printf("\n");
}*/
void gameInterface(int tip[], Num **matrix, int tam){
    int s=0;
    //Cima
    printf("\n\t     \u2503");
    for (int i=0;i<tam;i++)
        printf("  %d  \u2503", (i+1));
    
    //Meio
    for (int i=0;i<tam;i++){
        //Linhas horizontais das bordas
        printf("\n\t\u2501\u2501\u2501\u2501\u2501");
        for (int j=0;j<tam+1;j++)
            printf("\u254b\u2501\u2501\u2501\u2501\u2501");
        printf("\n");
        
        //Linhas horizontais dos numeros
        printf("\t  %d  ", i+1);
        for (int j=0;j<tam;j++){
            printf("\u2503  ");
            if (matrix[i][j].mark == 1)
                printf(GREEN("%d"), matrix[i][j].number);
            else if (matrix[i][j].mark == -1)
                printf(RED("%d"), matrix[i][j].number);
            else
                printf("%d", matrix[i][j].number);
            printf("  ");
        }
        printf("\u2503  ");
        for (int j=0;j<tam;j++)
            if (matrix[i][j].mark != -1)
                s += matrix[i][j].number;
        if (s == tip[i])
            printf(BOLD("%d"), tip[i]);
        else
            printf("%d", tip[i]);
        s = 0;
    }
    
    //Ultima linha horizontal das bordas
    printf("\n\t\u2501\u2501\u2501\u2501\u2501");
        for (int j=0;j<tam+1;j++)
            printf("\u254b\u2501\u2501\u2501\u2501\u2501");
        printf("\n");
    
    //Dicas inferiores
    printf("\t     \u2503");
    for (int i=0;i<tam;i++){
        printf("  ");
        for (int j=0;j<tam;j++)
            if (matrix[j][i].mark != -1)
                s += matrix[j][i].number;
        if (s == tip[tam+i])
            printf(BOLD("%2d"), tip[tam+i]);
        else
            printf("%2d", tip[tam+i]);
        s = 0;
        printf(" \u2503");
    }
}


//Todos os comandos possíveis na hora do jogo
void gameControls(int tip[], Num **matrix, int tam){
    char command[TAM_COMMANDS_GAME];
    int x, y;
    int contSum=0, contCorrect=0, contMistakes=0;
    char *space;
    //Contador de números que fazer parte da soma
    for (int i=0;i<tam;i++)
        for (int j=0;j<tam;j++)
            if (matrix[i][j].sum == 1)
                contSum++;
                
    while (1){
        //Conferindo todos os numeros certos marcados
        for (int i=0;i<tam;i++)
            for (int j=0;j<tam;j++)
                if (matrix[i][j].sum == 1 && matrix[i][j].mark == 1)
                    contCorrect++;
                else if (matrix[i][j].sum == 0 && matrix[i][j].mark == 1)
                    contMistakes++;
                
        //Condição de vitória
        if (contCorrect == contSum && contMistakes == 0){
            printf("Você venceu!!!\n");
            break;
        }
        else{
            contCorrect = 0;
            contMistakes = 0;
        }
        
        //Mostrando a interface e validando o comando do usuário
        gameInterface(tip, matrix, tam);
        printf("\n\najuda - Ver comandos\n\nDigite o comando: ");
        //Lê a entrada e organiza a string
        fgets(command, TAM_COMMANDS_GAME, stdin);
        if (strchr(command, '\n') == NULL)
            flush();
        space = strchr(command, ' ');
        if (space != NULL)    
            *space = '\0';
        else
            command[strlen(command)-1] = '\0';
        charDown(command, NULL);
        
        //Validando os comandos
        if (strcmp(command, "remover") == 0 && space != NULL){
            //
            if (*(space+1) <= tam+'0' && *(space+1) >= '1' && *(space+3) <= tam+'0' && *(space+3) >= '1' && *(space+2) == ' ' && *(space+4) == '\n'){
                x = *(space+1) - '0';
                y = *(space+3) - '0';
                matrix[x-1][y-1].mark = -1;
                clearDisplay();
            }
            else{
                clearDisplay();
                printf("Error: Comando incompatível, digite ajuda caso precise ver os comandos\n");
            }
        }    
        else if (strcmp(command, "adicionar") == 0 && space != NULL){
            printf("Pinto");
            if (*(space+1) <= tam+'0' && *(space+1) >= '1' && *(space+3) <= tam+'0' && *(space+3) >= '1' && *(space+2) == ' ' && *(space+4) == '\n'){
                x = *(space+1) - '0';
                y = *(space+3) - '0';
                matrix[x-1][y-1].mark = 1;
                clearDisplay();
            }
            else{
                clearDisplay();
                printf("Error: Comando incompatível, digite ajuda caso precise ver os comandos\n");
            }
        }
        else if (strcmp(command, "ajuda") == 0){
            clearDisplay();
            showCommands();
        }
        else if (strcmp(command, "sair") == 0){
            clearDisplay();
            showCommands();
            break;
        }
        else if (strcmp(command, "dica") == 0){
            while(1){
                srand(time(NULL));
                x = rand() % tam;
                y = rand() % tam;
                if (matrix[x][y].sum == 1)
                    if (matrix[x][y].mark == 1);
                    else{
                        matrix[x][y].mark = 1;
                        clearDisplay();
                        break;
                    }
                else
                    if (matrix[x][y].mark == -1);
                    else{
                       matrix[x][y].mark = -1;
                       clearDisplay();
                       break;
                    }
            }
        }
        else{
            clearDisplay();
            printf("Error: Comando incompatível, digite ajuda caso precise ver os comandos\n");
        }
    }
}   
//Cria um novo jogo, gerando, organizando e modificando a interface
void newGame(){
    int option = difficultyOptions();
    Num **matrix;
    int *tip;
    if (option == -1){
        clearDisplay();
        showCommands();
    }
    else if (option == 1){
        matrix = createMatrix(TAM_F);
        tips(&tip, matrix, TAM_F);
        clearDisplay();
        gameControls(tip, matrix, TAM_F);
    }
    else if (option == 2){
        matrix = createMatrix(TAM_M);
        tips(&tip, matrix, TAM_M);
        clearDisplay();
        gameControls(tip, matrix, TAM_M);
    }
    else if (option == 3){
        matrix = createMatrix(TAM_D);
        tips(&tip, matrix, TAM_D);
        clearDisplay();
        gameControls(tip, matrix, TAM_D);
    }
}




void menuOptions(){
    int i=0;
    char option[TAM_COMMANDS];
  //  char name[TAM_NAME];
    while (i == 0){
        fgets (option, TAM_COMMANDS, stdin);
        if (strchr(option, '\n') == NULL)
            flush();
        else
            option[strlen(option)-1] = '\0';
        charDown(option, NULL);
        if (strcmp (option, "ajuda") == 0){
            clearDisplay();
            showCommands();
            continue;
        }
        else if (strcmp (option, "sair") == 0)
            i = -1;
        else if (strcmp (option, "novo") == 0)
            //fgets (name, TAM_NAME, stdin);
            newGame();
        else if (strcmp (option, "carregar") == 0);
        else if (strcmp (option, "ranking") == 0);
        else if (strcmp (option, "salvar") == 0)
            printf("Só é possível utilizar esse comando em jogo\n");
        else if (strcmp (option, "dica") == 0)
            printf("Só é possível utilizar esse comando em jogo\n");
        else if (strcmp (option, "resolver") == 0)
            printf("Só é possível utilizar esse comando em jogo\n");
        else if (strcmp (option, "adicionar") == 0)
            printf("Só é possível utilizar esse comando em jogo\n");
        else if (strcmp (option, "remover") == 0)
            printf("Só é possível utilizar esse comando em jogo\n");
        else
            printf("Erro: comando incompatível, tente novamente\n");
        }
}


/*
Sumario:
5 - Mostrar comandos do jogo
20 - Limpar tela
25 - Caracteres minúsculos
37 - Limpar buffer
43 - Escolher dificuldade
- Menu de opções
*/

