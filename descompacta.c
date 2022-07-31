#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 1000000 // teste com 1 MEGA bytes

int main(int argc, char **argv) {
    // //variaveis uteis    
    // int i=0;
    char path[100];
    // char palavra[100];
    // long int *v = malloc(sizeof(long int) * 256);


    // //limpando vetor de pesos
    // for(i=0;i<256;i++) v[i] = 0;

    //caminho do arquivo passado na execucao do programa
    sprintf(path, "%s", argv[1]);
    FILE * entrada = fopen(path, "r");

    // //lendo o arquivo de texto e anotando os pesos no vetor
    // while(!feof(arquivo)){
    //     fscanf(arquivo, "%s", palavra);
    //     for(i=0;i<strlen(palavra);i++){
    //         v[palavra[i]]+=1;
    //     }
    // }
    // fclose(arquivo);

    // //impressão do vetor de pesos
    // for(i=0;i<256;i++) if (v[i]>0) printf("%c - %ld\n", (char)i, v[i]);

    
    // lendo a altura da tabela no arquivo compactado
    int altura = 0;
    fread(&altura, sizeof(int), 1, entrada);
    // printf("altura descompactada: %d\n", altura);

    unsigned char** tabCode = alocaTabela(altura+1);
    fread(tabCode, sizeof(unsigned char**), 1, entrada);

    printf("(descompacta) b: [%s]\n", tabCode['b']);






    fclose(entrada);


    // free(v);

    return 0;
}