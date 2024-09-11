#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

// Declaração Inicial das Variáveis Globais
char palavraSecreta[TAMANHO_PALAVRA_SECRETA];
char chutesMaximos[26];
int chutesRealizados = 0, tamanhoPalavra;


// Funções do Código
void aberturaForca() {

    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");

}

void realizarChute() {

    char chuteAtual;

    scanf(" %c", &chuteAtual);
        
    // Registrar todos os chutes realizados
    chutesMaximos[chutesRealizados] = chuteAtual;
    chutesRealizados++;

}

int chuteJaRealizado(char letra) {

    int encontrada = 0;

    // Loop para percorrer os chutes anteriores, armazenando os mesmos em Chutes Maximos
    for(int j = 0; j < chutesRealizados; j++) {
                
        // Validação de acertos
        if(chutesMaximos[j] == letra) {
                
            encontrada = 1;
            break;

        }
            
    }

    return encontrada;

}

void desenharForca() {

    // Loop para percorrer os caracteres da Palavra Secreta
        for(int i = 0; i < tamanhoPalavra; i++) {
            
            int encontrada = chuteJaRealizado(palavraSecreta[i]);

            // Impressão da letra se acertada
            if(encontrada) {
            
                printf("%c ", palavraSecreta[i]);
            
            } else {
            
                printf("_ ");
            
            }
        
        }
        
        printf("\n");

}

void escolherPalavra() {

    FILE* arquivo;

    arquivo = fopen("palavras.txt", "r");

    if (arquivo == 0) {

        printf("Desculpe, arquivo não foi aberto com sucesso\n");
        exit(1);

    }

    int quantidadeDePalavras;
    fscanf(arquivo, "%d", &quantidadeDePalavras);

    srand(time(0));
    int randomizador = rand() % quantidadeDePalavras;

    for (int i = 0; i <= randomizador; i++) {

        fscanf(arquivo, "%s", palavraSecreta);

    }

    fclose(arquivo);

}

void adicionarNovaPalavra() {

    char adicionarPalavra;

    printf("Você deseja adicionar uma nova palavra no jogo? (S/N)\n");
    scanf(" %c", adicionarPalavra);

    if (adicionarPalavra == 'S') {

        char novaPalavra[TAMANHO_PALAVRA_SECRETA];
        printf("Qual a nova palavra? \n");
        scanf("%s", novaPalavra);

        FILE* arquivo;

        arquivo = fopen("palavras.txt", "r+");

        if (arquivo == 0) {

            printf("Desculpe, banco de dados não está disponível\n");
            exit(1);

        }

        int quantidadePalavra;
        fscanf(arquivo, "%d", &quantidadePalavra);
        quantidadePalavra++;

        fseek(arquivo , 0, SEEK_SET);
        fprintf(arquivo, "\n%s", novaPalavra);

        fseek(arquivo , 0, SEEK_END);
        fprintf(arquivo, "\n%s", novaPalavra);

        fprintf(arquivo, "\n%s", novaPalavra);

        fclose(arquivo);

    }

}

int enforcou() {

    int erros = 0;

    // Loop de todos os chutes realizados
    for (int i = 0; i < chutesRealizados; i++) {

        int existe = 0;

        // Verificar o array, descobrindo se possui a letra chutada
        for (int j = 0; j < tamanhoPalavra; j++) {

            if (chutesMaximos[i] == palavraSecreta[j]) {

                existe = 1;
                break;

            }

        }

        if (!existe) {
            erros++;
        }
    }
    // Return booleano
    return erros >= 5;
}

int acertou() {

    for (int i = 0; i < tamanhoPalavra; i++) {

        if (!chuteJaRealizado(palavraSecreta[i])) {

            return 0;

        }

    }

    return 1;

}

int main() {

    escolherPalavra();
    aberturaForca();

    // Loop principal do código, onde ocorre o jogo da forca
    do {

        desenharForca();
        realizarChute();

    } while (!acertou() && !enforcou());
    
    if (acertou()) {

        printf("Parabéns, você ganhou!\n");

    } else {

        printf("Poxa, você foi enforcado!\n");
        printf("A palavra secreta era: **%s**\n\n", palavraSecreta);

    }

    adicionarNovaPalavra();

}