#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 1000000 // teste com 1 MEGA bytes


int main(int argc, char **argv) {

    // abrindo o arquivo de entrada
    char path[100];
    sprintf(path, "%s", argv[1]);
    FILE * entrada = fopen(path, "r");

    // abrindo o arquivo de saida
    // int qtdLetras = strlen(path);
    // path[qtdLetras-4] = '\0'; // tirar o .comp do path
    // FILE* saida = fopen(strcat(path, ".txt"), "w");

    
    // lendo a altura da tabela no arquivo compactado
    int altura = 0;
    fread(&altura, sizeof(int), 1, entrada);
    printf("altura descompactada: %d\n", altura);


    // lendo a tabela de codificação (montando a árvore de huffman)
    // TODO
    Arv* arvHuff;


    // lendo o conteúdo do arquivo (supondo já saber a árovre de huffman)
    int i = 0;
    unsigned char byte;
    Arv* arvAux = arvHuff;

    /* DESCOMENTAR DEPOIS QUE TIVER A ÁRVORE PRONTA */
    // while (fread(&byte, sizeof(unsigned char), 1, entrada)) {
        
    //     for (i = 7; i >= 0; i--) {
    //         unsigned char aux = (1 << i); // 00000001 deslocado i vezes pra esquerda

    //         if (byte & aux) { // o bit é 1
    //             arvHuff = arvHuff->dir;

    //         } else { // o bit é zero
    //             arvHuff = arvHuff->esq;
    //         }

    //         if (arvHuff->esq == NULL && arvHuff->dir == NULL) { // cheggou num nó folha
    //             fprintf(saida, "%c", getInfo(arvHuff));
    //             arvAux = arvHuff; // volta pro início da árvore de huffman
    //         }

    //     }

    // }



    // liberando a memória alocada
    fclose(entrada);
    // fclose(saida);

    return 0;
}