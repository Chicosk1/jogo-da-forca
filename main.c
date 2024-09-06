#include <stdio.h>
#include <string.h>

void aberturaForca() {

    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");

}

void realizarChute(char chutesMaximos[26], int* tentativas) {

    char chuteAtual;

    scanf(" %c", &chuteAtual);
        
    // Registrar todos os chutes realizados
    chutesMaximos[(*tentativas)] = chuteAtual;
    (*tentativas)++;

}

int chutesRealizados(char letra, char chutesMaximos[26], int tentativas) {

    int encontrada = 0;

    // Loop para percorrer os chutes anteriores, armazenando os mesmos em Chutes Maximos
    for(int j = 0; j < tentativas; j++) {
                
        // Validação de acertos
        if(chutesMaximos[j] == letra) {
                
            encontrada = 1;
            break;

        }
            
    }

    return encontrada;

}

int main() {
    // Declaração Inicial das Variáveis
    int ganhou = 0, enforcou = 0, tentativas = 0;
    char palavraSecreta[20] = "MELANCIA";
    char chutesMaximos[26];

    aberturaForca();

    // Loop principal do código, onde ocorre o jogo da forca
    do {

        // Loop para percorrer os caracteres da Palavra Secreta
        for(int i = 0; i < strlen(palavraSecreta); i++) {
            
            int encontrada = chutesRealizados(palavraSecreta[i], chutesMaximos, tentativas);

            // Impressão da letra se acertada
            if(encontrada) {
            
                printf("%c ", palavraSecreta[i]);
            
            } else {
            
                printf("_ ");
            
            }
        
        }
        
        printf("\n");

        realizarChute(chutesMaximos, &tentativas);

    } while (!ganhou && !enforcou);

}