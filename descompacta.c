#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes


unsigned int bit(unsigned char byte, int pos){
    unsigned char aux = (1 << pos);
    return byte & aux;
}


int main(int argc, char **argv) {
    int i, altura = 0, k;
    long int *v = malloc(sizeof(long int) * 256);
    char path[100];

    // Caminho do arquivo passado na execucao do programa
    sprintf(path, "%s", argv[1]);
    FILE * entrada = fopen(path, "rb");

    fread(v, sizeof(long int), 256, entrada);
    
    // for(i= 0; i < 256; i++) if (v[i]) printf("%d = %ld\n", i, v[i]);

    /*================ Tabela de codificação do arquivo compactado ================*/
    
    // fread(&altura, sizeof(int), 1, entrada);
    // // printf("altura descompactada: %d\n", altura);

    // //TODO: retirar
    // unsigned char** tabCode = alocaTabela(altura+1);
    // // for(k=0;k<256;k++) fread(tabCode[k], sizeof(unsigned char*), 1, entrada);

    // printf("\nDESCOMPACT\n");

    //  inserindo as arvores com os pesos na lista
    Lista * listaArvores = InicializaListaVazia();
    for(i=0;i<256;i++) {
        if (v[i]>0) {
            InsereArvUlt(listaArvores, abb_cria((char)i, v[i], abb_cria_vazia(), abb_cria_vazia()));
        }
    }

    OrdenaLista(listaArvores);
    Aplica_Huffman(listaArvores);
    // ImprimeLista(listaArvores);



    /* ================= LENDO ARQUIVO COMPACTADO ================= */

    path[strlen(path)-5] = '\0';
    //TODO: mudar o nome depois
    strcat(path, "_saida.txt");

    FILE * saida = fopen(path, "wr");
    // decodifica(arv_huffman, bm, saida);

    unsigned char byte;
    Arv * raiz = getPrimeiroNo(listaArvores);
    Arv * aux = raiz;

    while (fread(&byte, sizeof(unsigned char), 1, entrada)) {
        for (int i = 7; i >= 0; i--) {
            if (bit(byte, i)) {
                aux = getRamoDir(aux);
            } else {
                aux = getRamoEsq(aux);
            }

            if (getRamoEsq(aux) == NULL && getRamoDir(aux) == NULL) {
                fprintf(saida, "%c", getChar(aux));
                aux = raiz;
            }
        }
    }



    /* ================= Criando arvore pela tabela de codificação ================= */
    
    // Arv * arv_huffman=abb_cria('-', 0, abb_cria_vazia(), abb_cria_vazia());
    
    // for(k=0;k<256;k++){
    //     if (strlen(tabCode[k])>0){
    //         char * codigo = strdup(tabCode[k]);
    //         abb_preenche_codigos(arv_huffman, codigo, 0, k);
    //         free(codigo);
    //     }
    // }

    //TODO: retirar 
    // abb_imprime_formato_graphviz(arv_huffman);




    /*===================== Conteudo do texto no arquivo compactado =====================*/
    

    // bitmap* bm = bitmapInit(MAX_SIZE);
    // while(!feof(entrada)){
    //     unsigned char aux;
    //     fread(&aux, sizeof(unsigned char), 1, entrada);
    //     bitmapAppendLeastSignificantBit(bm, aux);
    // }

    

    
    //FIXME: isso nao funciona
    // long int tamanho;
    // fread(&tamanho, sizeof(long int), 1, entrada);
    
    // unsigned char * aux = malloc(sizeof(unsigned char) * tamanho);
    // fread(aux, sizeof(unsigned char*), 1, entrada);

    // for(i=0;i<256;i++) {
    //     if (aux[i]=='1') bitmapAppendLeastSignificantBit(bm, 1);
    //     else if (aux[i]=='0') bitmapAppendLeastSignificantBit(bm, 0);
    // }

    // for(i=0;i<tamanho;i++) bitmapAppendLeastSignificantBit(bm, aux[i]=='1'?1:0);
    // for(i=0;i<tamanho;i++) fread(&aux[i], sizeof(unsigned char), 1, entrada);   
    
    // fread(aux, sizeof(unsigned char*), 1, entrada);




    /* ======================== Liberando a memória ======================== */
    // free(aux);
    fclose(entrada);
    fclose(saida);
    LiberaLista(listaArvores);
    // liberaTabCode(tabCode);
    // bitmapLibera(bm);
    free(v);

    return 0;
}



