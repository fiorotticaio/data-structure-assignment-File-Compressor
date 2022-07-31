#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes

int main(int argc, char **argv) {
    char path[100];

    // Caminho do arquivo passado na execucao do programa
    sprintf(path, "%s", argv[1]);
    FILE * entrada = fopen(path, "r");
    // printf("altura descompactada: %d\n", altura);




    /*================ Tabela de codificação do arquivo compactado ================*/
    
    int altura = 0, k;
    fread(&altura, sizeof(int), 1, entrada);

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
    
    
    // char tamanho_binario[100];
    // long int tamanho_decimal;
    // fread(tamanho_binario, sizeof(char*), 1, entrada);
    // int i;
    
    // for(i=0;i<strlen(tamanho_binario);i++) if (tamanho_binario[i] == '1') tamanho_decimal += pow(2,strlen(tamanho_binario)-i);
    
    // printf("tamanho_binario(desco): %s\n", tamanho_binario);
    // printf("tamanho_decimal(desco): %ld\n", tamanho_decimal);
    
    bitmap* bm = bitmapInit(MAX_SIZE);
    while(!feof(entrada)){
        unsigned char aux;
        fread(&aux, sizeof(unsigned char), 1, entrada);
        bitmapAppendLeastSignificantBit(bm, aux);
    }

    // unsigned char * aux;
    // fread(aux, sizeof(unsigned char*), tamanho_decimal, entrada);

    // for(i=0;i<tamanho_decimal;i++) bitmapAppendLeastSignificantBit(bm, aux[i]);




    /* ============================== Escrevendo na saida ============================== */

    
    char saidaPath[100];
    sprintf(saidaPath, "%s", path);
    saidaPath[strlen(saidaPath)-5] = '\0';
    strcat(saidaPath, "_saida.txt");

    FILE * saida = fopen(saidaPath, "wr");
    decodifica(arv_huffman, bm, saida);


    /* ======================== Liberando a memória ======================== */
    fclose(entrada);
    fclose(saida);
    liberaTabCode(tabCode);
    bitmapLibera(bm);

    return 0;
}