#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 1000000 // teste com 1 MEGA bytes

int main(int argc, char **argv) {
    //variaveis uteis    
    int i=0, j=0, n=0;
    char path[100];
    char caractere='\0';
    long int *v = malloc(sizeof(long int) * 256);


    //limpando vetor de pesos
    for(i=0;i<256;i++) v[i] = 0;

    //caminho do arquivo passado na execucao do programa
    sprintf(path, "%s", argv[1]);
    FILE * arquivo = fopen(path, "r");

    //lendo o arquivo de texto e anotando os pesos no vetor
    while(!feof(arquivo)){
        if (caractere!='\0') v[caractere]+=1;
        fscanf(arquivo, "%c", &caractere);
    }
    fclose(arquivo);

    //impressão do vetor de pesos
    // for(i=0;i<256;i++) if (v[i]>0) printf("[%c - %ld] ", (char)i, v[i]); printf("\n");

    //inserindo as arvores com os pesos na lista
    Lista * listaArvores = InicializaListaVazia();
    for(i=0;i<256;i++) {
        if (v[i]>0) {
            InsereArvUlt(listaArvores, abb_cria(1, (char)i, v[i], abb_cria_vazia(), abb_cria_vazia()));
        }
    }

    ImprimeLista(listaArvores);
    
    OrdenaLista(listaArvores);

    ImprimeLista(listaArvores);

    Aplica_Huffman(listaArvores);

    CodificaNos(listaArvores);

    ImprimeLista(listaArvores);





    /*=========== Escrevendo no arquivo binário =========================*/

    int altura = calculaAlturaArvore_Huff(listaArvores);
    printf("altura: %d\n", altura); // a altura da árvore é o número máximo de bits
                                    // que um caracter pode ter na tabela de codificação


    // abrindo o arquivo de entrada de novo pra ler o texto
    FILE * entrada = fopen(path, "r");
    //gerando o arquivo de saida
    int qtdLetras = strlen(path);
    path[qtdLetras-4] = '\0'; // tirar o .txt do path
    FILE* saida = fopen(strcat(path, ".comp"), "w");


    // criando o bitmap
    bitmap* bm = bitmapInit(MAX_SIZE);

    // while(!feof(entrada)){
    //     fscanf(entrada, "%c", &caractere);
    //     printf("%c - %ld\n", caractere, v[caractere]);
        // abb_get_codigo(getPrimeiroNo(listaArvores), caractere, v[caractere], codigo);
        // printf(" - %s\n", codigo);
    // }

    fclose(entrada);
    fclose(saida);


    LiberaLista(listaArvores);
    free(v);

    return 0;
}
