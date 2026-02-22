//Pablo Henrique 25.2.4149
#include "funcoes.h"

int main(){
    printf("Boas Vindas ao SUMPLETE_GAME!!\n\n");
    
    //Chamadas de funções do menu
    clearDisplay();
    menuOptions();
    printf("Obrigado por jogar!!\n");
    return 0;
}
/*
while(1){
                printf("Digite o nome do jogador: ");
                fgets (name, TAM_NAME, stdin);
                if (strchr(name, '\n') == NULL){
                    flush();
                    clearDisplay();
                    printf("Erro: O nome deve conter no máximo 20 caractéres\n\n");
                }
                else
                    break;
            }
*/
