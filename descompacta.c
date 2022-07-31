#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes

int main(int argc, char **argv) {
    int i, altura = 0, k;
    char path[100];

    // Caminho do arquivo passado na execucao do programa
    sprintf(path, "%s", argv[1]);
    FILE * entrada = fopen(path, "r");




    /*================ Tabela de codificação do arquivo compactado ================*/
    
    fread(&altura, sizeof(int), 1, entrada);
    // printf("altura descompactada: %d\n", altura);

    unsigned char** tabCode = alocaTabela(altura+1);
    for(k=0;k<256;k++) fread(tabCode[k], sizeof(unsigned char*), 1, entrada);





    /* ================= Criando arvore pela tabela de codificação ================= */
    
    Arv * arv_huffman=abb_cria('-', 0, abb_cria_vazia(), abb_cria_vazia());
    
    for(k=0;k<256;k++){
        if (strlen(tabCode[k])>0){
            char * codigo = strdup(tabCode[k]);
            abb_preenche_codigos(arv_huffman, codigo, 0, k);
            free(codigo);
        }
    }

    //TODO: retirar 
    // abb_imprime_formato_graphviz(arv_huffman);




    /*===================== Conteudo do texto no arquivo compactado =====================*/
    

    bitmap* bm = bitmapInit(MAX_SIZE);
    while(!feof(entrada)){
        unsigned char aux;
        fread(&aux, sizeof(unsigned char), 1, entrada);
        bitmapAppendLeastSignificantBit(bm, aux);
    }

    
    //FIXME: isso nao funciona
    // long int tamanho;
    // fread(&tamanho, sizeof(long int), 1, entrada);
    // unsigned char * aux = malloc(sizeof(unsigned char) * tamanho);
    // fread(aux, sizeof(unsigned char), tamanho, entrada);
    // for(i=0;i<tamanho;i++) bitmapAppendLeastSignificantBit(bm, aux[i]=='1'?1:0);




    /* ============================== Escrevendo na saida ============================== */

    
    path[strlen(path)-5] = '\0';
    //TODO: mudar o nome depois
    strcat(path, "_saida.txt");

    FILE * saida = fopen(path, "wr");
    decodifica(arv_huffman, bm, saida);


    /* ======================== Liberando a memória ======================== */
    // free(aux);
    fclose(entrada);
    fclose(saida);
    liberaTabCode(tabCode);
    bitmapLibera(bm);

    return 0;
}