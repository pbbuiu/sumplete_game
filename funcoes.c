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
    printf("salvar <name_file>: Salva o jogo atual\n");
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
        for (int i=0;i<(int)strlen(word);i++)
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
        if (optionDifficulty[0] != '\n'){
            if (optionDifficulty[1] != '\n'){
                flush();
                clearDisplay();
                printf("Erro: comando incompatível, tente novamente\n");
                continue;
            }
        }
        else{
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
Num **createMatrix(int optionDifficulty, int load){
    Num **matrix;
    matrix = malloc (optionDifficulty * sizeof(Num*));
    for (int i=0;i<optionDifficulty;i++)
        matrix[i] = malloc (optionDifficulty * sizeof(Num));
    if (load == 0)
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
    for (int i=0;i<tam*2;i++)
        (*tip)[i] = 0;
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
            printf(BOLD("%-2d"), tip[tam+i]);
        else
            printf("%-2d", tip[tam+i]);
        s = 0;
        printf(" \u2503");
    }
}

//Libera memória
void freeMatrix(Num **matrix, int tip[], int tam){
    for (int i=0;i<tam;i++)
        free(matrix[i]);
    free(matrix);
    free(tip);
}

//Retorna o cálculo do tempo
double calculateTime(Time begin, Time end){
    return end.tv_sec - begin.tv_sec;
}

//Salva o jogo em um arquivo com nome dado pelo usuario
void saveGame(Num **matrix, int tam, int tip[], char gameName[], Player gamer){
    char totalName[TAM_NAME+5];
    strcpy (totalName, gameName);
    strcat (totalName, ".sum");
    int contSum=0, contMark=0;
    FILE *arqMatrix = fopen(totalName, "w");
    
    //Tamanho
    fprintf(arqMatrix, "%d\n", tam);
    
    //Números da matrix e quantidade de numeros que fazem parte da soma e também quantidade de numeros que estão marcados
    for (int i=0;i<tam;i++){
        for (int j=0;j<tam;j++){
            fprintf(arqMatrix, "%d ", matrix[i][j].number);
            if (matrix[i][j].sum == 1)
                contSum++;
            if (matrix[i][j].mark != 0)
                contMark++;
        }
        fprintf(arqMatrix, "\n");
    }
    
    //Dicas
    for (int i=0;i<tam;i++)
        fprintf(arqMatrix, "%d ", tip[i]);
    fprintf(arqMatrix, "\n");
    for (int i=tam;i<tam*2;i++)
        fprintf(arqMatrix, "%d ", tip[i]);
        
    //Posições dos números que fazem parte da soma
    fprintf(arqMatrix, "\n%d\n", contSum);
    for (int i=0;i<tam;i++)
        for (int j=0;j<tam;j++)
            if (matrix[i][j].sum == 1)
                fprintf(arqMatrix, "%d %d\n", i, j);
    
    //Imprimindo quantidade de numeros que estão marcados
    fprintf(arqMatrix, "%d\n", contMark);
    
    //Posições dos números marcados
    for (int i=0;i<tam;i++)
        for (int j=0;j<tam;j++)
            if (matrix[i][j].mark == 1)
                fprintf(arqMatrix, "a %d %d\n", i, j);
            else if(matrix[i][j].mark == -1)
                fprintf(arqMatrix, "r %d %d\n", i, j);
    
    //Nome
    fprintf(arqMatrix, "%s", gamer.name);
    
    //Tempo até o momento de save
    fprintf(arqMatrix, "%d", gamer.totalTime);
    fclose (arqMatrix);
}

//Mostra o ranking na tela
void showRanking(){
    char str[TAM_NAME+10];
    FILE *arqRanking = fopen("sumplete.rnk", "r");
    clearDisplay();
    printf("\nRANKING:\n");
    if (arqRanking == NULL){
        printf("Nenhum recorde encontrado.\n");
    }
    else{
        while (fgets(str, TAM_NAME+10, arqRanking) != NULL){
            printf("%s", str); // O \n já vem do arquivo
        }
        fclose(arqRanking);
    }
}

//Adiciona e altera as posições no ranking
void addRanking(Player gamer){
    Rank vet[TAM_RANK];
    char str[TAM_NAME+10];
    int temp = 0;
    int i = 0;
    int space;
    FILE *arqRanking = fopen("sumplete.rnk", "r");
    if (arqRanking == NULL){
        arqRanking = fopen("sumplete.rnk", "w");
        fprintf(arqRanking, "%s %d\n", gamer.name, gamer.totalTime);
        fclose(arqRanking);
    }
    else{
        while (fgets(str, TAM_NAME+10, arqRanking) != NULL && i < 10){
            str[strlen(str)-1] = '\0';
            for (int j=0;j<(int)strlen(str);j++)
                if (str[j] == ' ')
                    space = j;
            str[space] = '\0';
            if (temp == 0 && gamer.totalTime < atoi(&str[space+1])){
                strcpy(vet[i].nameRank, gamer.name);
                vet[i].timeRank = gamer.totalTime;
                i++;
                temp = 1;
                if (i < 10){
                    strcpy(vet[i].nameRank, str);
                    vet[i].timeRank = atoi(&str[space+1]);
                    i++;
                }
            }
            else{
                strcpy(vet[i].nameRank, str);
                vet[i].timeRank = atoi(&str[space+1]);
                i++;
            }
        }
        if (temp == 0 && i < 10){
            strcpy(vet[i].nameRank, gamer.name);
            vet[i].timeRank = gamer.totalTime;
            i++;
        }
        fclose(arqRanking);
        arqRanking = fopen("sumplete.rnk", "w");
        for (int j=0;j<i;j++)
            fprintf(arqRanking, "%s %d\n", vet[j].nameRank, vet[j].timeRank);
        fclose(arqRanking);
    }
    // Print formatado para não pular linha entre nome e tempo
    for (int j=0;j<i;j++)
        printf("%-15s %d\n", vet[j].nameRank, vet[j].timeRank);
}

//Todos os comandos possíveis na hora do jogo
void gameControls(int tip[], Num **matrix, int tam, Time begin, Player gamer){
    Time end;
    char gameName[TAM_NAME];
    char command[TAM_COMMANDS_GAME];
    int x, y;
    int contSum=0, contCorrect=0, contWrong = 0, contMistakes=0;
    char *space;
    int valida=0;
    int save=0;
    char saveOption[TAM_OPTION];
    char next;
    int contTip=0;
    
    //Contador de números que fazem parte da soma
    for (int i=0;i<tam;i++)
        for (int j=0;j<tam;j++)
            if (matrix[i][j].sum == 1)
                contSum++;
                
    while (1){
        contWrong = 0;
        contCorrect = 0;
        contMistakes = 0;
        //Conferindo todos os numeros certos marcados
        for (int i=0;i<tam;i++)
            for (int j=0;j<tam;j++)
                if (matrix[i][j].sum == 1 && matrix[i][j].mark == 1)
                    contCorrect++;
                else if (matrix[i][j].sum == 0 && matrix[i][j].mark == -1)
                    contWrong++;
                else if ((matrix[i][j].sum == 0 && matrix[i][j].mark == 1) || (matrix[i][j].sum == 1 && matrix[i][j].mark == -1))
                    contMistakes++;
            
        //Condição de vitória
        if ((contWrong == (tam*tam)-contSum) && contMistakes == 0){
            gameInterface(tip, matrix, tam);
            freeMatrix(matrix, tip, tam);
            printf("\n\nVocê venceu!!!\n");
            gettimeofday(&end, NULL);
            gamer.totalTime += (int)(end.tv_sec - begin.tv_sec);
            printf("\nSeu tempo foi: %d\n\n", gamer.totalTime);
            printf("Pressione enter para continuar ");
            scanf("%c", &next);
            if (contTip != 0)
                printf("Não será possível ver seu nome no ranking, pois você usou as dicas\n");
            else{
                addRanking(gamer);
                showRanking();
            }
            printf("Pressione enter para continuar ");
            scanf("%c", &next);
            clearDisplay();
            break;
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
                save++;
            }
            else{
                clearDisplay();
                printf("Error: Comando incompatível, digite ajuda caso precise ver os comandos\n");
            }
        }    
        else if (strcmp(command, "adicionar") == 0 && space != NULL){
            if (*(space+1) <= tam+'0' && *(space+1) >= '1' && *(space+3) <= tam+'0' && *(space+3) >= '1' && *(space+2) == ' ' && *(space+4) == '\n'){
                x = *(space+1) - '0';
                y = *(space+3) - '0';
                matrix[x-1][y-1].mark = 1;
                clearDisplay();
                save++;
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
            gettimeofday(&end, NULL);
            if (save != 0){
                while(1){
                    printf("O jogo atual não foi salvo deseja salva-lo (S/n)? ");
                    fgets(saveOption, TAM_OPTION, stdin);
                    if ((saveOption[0] == 's' || saveOption[0] == 'S' || saveOption[0] == 'N' || saveOption[0] == 'n')){
                        if (strlen(saveOption) > TAM_OPTION-1){
                            printf("Erro: comando grande demais, tente novamente\n");
                            flush();
                            continue;
                        }
                        saveOption[strlen(saveOption)-1] = '\0';
                        charDown(saveOption, NULL);
                        break;
                    }
                    else{
                        printf("Erro: comando incompatível, tente novamente\n");
                        continue;
                    }
                }
            }
            else {
                freeMatrix(matrix, tip, tam);
                clearDisplay();
                break;
            }
            if (strcmp(saveOption, "s") == 0){
                while(1){
                    printf("Digite o nome do arquivo: ");
                    fgets(gameName, TAM_NAME, stdin);
                    if (strchr(gameName, '\n') == NULL){
                        printf("Erro: O nome do arquivo deve conter 20 caractéres no máximo\n");
                        flush();
                        continue;
                    }
                    else if (gameName[0] == '\n'){
                            printf("Erro: Nome do arquivo curto demais\n");
                            continue;
                    }
                    else{
                        gameName[strlen(gameName)-1] = '\0';
                        for (int i=0;i<(int)strlen(gameName);i++)
                            if ((gameName[i] >= 'a' && gameName[i] <= 'z') || (gameName[i] >= 'A' && gameName[i] <= 'Z') || (gameName[i] >= '0' && gameName[i] <= '9') || gameName[i] == '_');
                            else{
                                valida++;
                                break;
                            }
                    }
                    if (valida != 0){
                        printf("Erro: Não é possível o uso de caractéres especiais exceto _\n");
                        valida = 0;
                    }
                    else
                        break;
                }
                valida = 0;
                clearDisplay();
                gamer.totalTime = end.tv_sec - begin.tv_sec; 
                saveGame(matrix, tam, tip, gameName, gamer);
                printf("Jogo salvo com sucesso!\n");
                freeMatrix(matrix, tip, tam);
                break;
            }
            else{
                freeMatrix(matrix, tip, tam);
                clearDisplay();
                break;
            }
        }
        else if (strcmp(command, "dica") == 0){
            if (contCorrect != contSum){
                contTip++;
                srand(time(NULL));
                x = rand() % tam;
                y = rand() % tam;
                while(1){
                    if (matrix[x][y].sum == 1 && matrix[x][y].mark != 1){
                            matrix[x][y].mark = 1;
                            clearDisplay();
                            break;
                    }
                    else
                        y++;
                    if (y >= tam){
                        x++;
                        y = 0;
                        if (x >= tam){
                            x = 0;
                            y = 0;
                        }
                    }
                }
                save++;
            }
            else{
                clearDisplay();
                printf("Não é possível usar a dica\n");
            }
        }
        else if (strcmp(command, "salvar") == 0 && space != NULL){
            strcpy (gameName, space+1);
            if (strchr(gameName, '\n') == NULL){
                clearDisplay();
                printf("Erro: O nome do arquivo deve conter 20 caractéres no máximo\n");
            }
            else if (gameName[0] == '\n'){
                clearDisplay();
                printf("Erro: Nome do arquivo curto demais\n");
            }
            else{
                gameName[strlen(gameName)-1] = '\0';
                for (int i=0;i<(int)strlen(gameName);i++)
                    if ((gameName[i] >= 'a' && gameName[i] <= 'z') || (gameName[i] >= 'A' && gameName[i] <= 'Z') || (gameName[i] >= '0' && gameName[i] <= '9') || gameName[i] == '_');
                    else{
                        valida++;
                        break;
                    }
            }
            if (valida != 0){
                clearDisplay();
                printf("Erro: Não é possível o uso de caractéres especiais exceto _\n");
            }
            else{
                clearDisplay();
                gettimeofday(&end, NULL);
                gamer.totalTime = end.tv_sec - begin.tv_sec; 
                saveGame(matrix, tam, tip, gameName, gamer);
                printf("Jogo salvo com sucesso!\n");
                save = 0;
            }
            valida = 0;
        }
        else if (strcmp(command, "resolver") == 0){
            clearDisplay();
            for (int i=0;i<tam;i++)
                for (int j=0;j<tam;j++)
                    if (matrix[i][j].sum == 1)
                        matrix[i][j].mark = 1;
                    else
                        matrix[i][j].mark = -1;
            gameInterface(tip, matrix, tam);
            freeMatrix(matrix, tip, tam);
            printf("\n\nPressione enter para continuar ");
            scanf("%c", &next);
            clearDisplay();
            break;
        }
        else {
            clearDisplay();
            printf("Error: Comando incompatível, digite ajuda caso precise ver os comandos\n");
        }
    }
}   
//Cria um novo jogo, gerando, organizando e modificando a interface
void newGame(int load){
    Time begin;
    Player gamer;
    int option;
    Num **matrix;
    int *tip;
    int tam;
    int val;
    gamer.totalTime = 0;
    if (load == 0){
        while(1){
            printf("Digite o nome do jogador: ");
            fgets (gamer.name, TAM_NAME, stdin);
            if (strchr(gamer.name, '\n') == NULL){
                flush();
                clearDisplay();
                printf("Erro: O nome deve conter no máximo 20 caractéres\n\n");
            }
            else {
                // ADICIONE ESTA LINHA: remove o \n do nome do jogador
                gamer.name[strlen(gamer.name)-1] = '\0'; 
                break;
            }
        }
        option = difficultyOptions();
        if (option == -1){
            clearDisplay();
        }
        else if (option == 1){
            matrix = createMatrix(TAM_F, 0);
            tips(&tip, matrix, TAM_F);
            clearDisplay();
            gettimeofday(&begin, NULL);
            gameControls(tip, matrix, TAM_F, begin, gamer);
        }
        else if (option == 2){
            matrix = createMatrix(TAM_M, 0);
            tips(&tip, matrix, TAM_M);
            clearDisplay();
            gettimeofday(&begin, NULL);
            gameControls(tip, matrix, TAM_M, begin, gamer);
        }
        else if (option == 3){
            matrix = createMatrix(TAM_D, 0);
            tips(&tip, matrix, TAM_D);
            clearDisplay();
            gettimeofday(&begin, NULL);
            gameControls(tip, matrix, TAM_D, begin, gamer);
        }
    }
    else{
        val = loadGame(&matrix, &tip, &tam, &gamer);
        if (val == 1){
            clearDisplay();
            gettimeofday(&begin, NULL);
            gameControls(tip, matrix, tam, begin, gamer);
        }
    }
}

//Carrega jogos anteriores que foram salvos
int loadGame(Num ***matrix, int **tip, int *tam, Player *gamer){
    FILE *arqMatrix = NULL;
    char gameName[TAM_NAME];
    char ar, buffer;
    int contSum, contMark, x, y;
    clearDisplay();
    while(1){
        printf("(x - voltar)\nDigite o nome do arquivo salvo: ");
        fgets(gameName, TAM_NAME-5, stdin);
        if (strchr(gameName, '\n') == NULL){
            flush();
            clearDisplay();
            printf("ERRO: O nome do arquivo deve conter no máximo 20 caractéres\n");
        } 
        else if (gameName[0] == 'x' && gameName[1] == '\n')
            return 0;
        else{
            gameName[strlen(gameName)-1] = '\0';
            strcat (gameName, ".sum");
            arqMatrix = fopen(gameName, "r");
            if (arqMatrix != NULL){
                break;
            }
            else{
                clearDisplay();
                printf("ERRO: arquivo não encontrado\n");
            }
        }
    }
    fscanf(arqMatrix, "%d", tam);
    (*matrix) = createMatrix((*tam), 1);
    (*tip) = malloc (((*tam)*2) * sizeof(int));
    
    //Preenchendo os numeros e zerando sum os dados do save
    for (int i=0;i<(*tam);i++)
        for (int j=0;j<(*tam);j++){
            fscanf(arqMatrix, "%d", &(*matrix)[i][j].number);
            (*matrix)[i][j].sum = 0;
            (*matrix)[i][j].mark = 0;
        }
    
    //Preenchendo as dicas com os dados do save
    for (int i=0;i<((*tam)*2);i++)
        fscanf(arqMatrix, "%d", &(*tip)[i]);
        
    //Preenchendo as localizações dos números que fazem parte da soma
    fscanf(arqMatrix, "%d", &contSum);
    for (int i=0;i<contSum;i++){
        fscanf(arqMatrix, "%d%d", &x, &y);
        (*matrix)[x][y].sum = 1;
    }
    
    //Preenchendo as marcações
    fscanf(arqMatrix, "%d", &contMark);
    for (int i=0;i<contMark;i++){
        fscanf(arqMatrix, "%c%c%d%d", &buffer, &ar, &x, &y);
        if (ar == 'a')
            (*matrix)[x][y].mark = 1;
        else
            (*matrix)[x][y].mark = -1;
    }
    
    //Nome do jogador e tempo até o momento do save
    fscanf(arqMatrix, "%c", &buffer);
    fgets ((*gamer).name, TAM_NAME, arqMatrix);
    fscanf(arqMatrix, "%d", &(*gamer).totalTime);
    return 1;
}

void menuOptions(){
    int i=0;
    char option[TAM_COMMANDS];
    char next;
    while (i == 0){
        printf("|Menu do jogo|\n\n");
        showCommands();
        fgets (option, TAM_COMMANDS, stdin);
        if (strchr(option, '\n') == NULL)
            flush();
        else
            option[strlen(option)-1] = '\0';
        charDown(option, NULL);
        if (strcmp (option, "ajuda") == 0){
            clearDisplay();
            continue;
        }
        else if (strcmp (option, "sair") == 0)
            i = -1;
        else if (strcmp (option, "novo") == 0){
            clearDisplay();
            newGame(0);
        }
        else if (strcmp (option, "carregar") == 0)
            newGame(1);
        else if (strcmp (option, "ranking") == 0) {
            showRanking();
            printf("\nPressione enter para voltar ao menu");
            scanf("%c", &next);
            clearDisplay();
        }
        else if (strcmp (option, "salvar") == 0){
            printf("Só é possível utilizar esse comando em jogo\n");
            clearDisplay();
        }
        else if (strcmp (option, "dica") == 0){
            printf("Só é possível utilizar esse comando em jogo\n");
            clearDisplay();
        }
        else if (strcmp (option, "resolver") == 0){
            printf("Só é possível utilizar esse comando em jogo\n");
            clearDisplay();
        }
        else if (strcmp (option, "adicionar") == 0){
            printf("Só é possível utilizar esse comando em jogo\n");
            clearDisplay();
        }
        else if (strcmp (option, "remover") == 0){
            printf("Só é possível utilizar esse comando em jogo\n");
            clearDisplay();
        }
        else{
            clearDisplay();
            printf("Erro: comando incompatível, tente novamente\n");
            
        }
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

