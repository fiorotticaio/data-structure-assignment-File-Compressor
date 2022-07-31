#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes

int main(int argc, unsigned char**argv) {
    //variaveis uteis    
    int i = 0, j = 0, n = 0;
    unsigned char path[100];
    unsigned char caractere = '\0';
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
            InsereArvUlt(listaArvores, abb_cria((char)i, v[i], abb_cria_vazia(), abb_cria_vazia()));
        }
    }

    OrdenaLista(listaArvores);
    Aplica_Huffman(listaArvores);
    // ImprimeLista(listaArvores);


    /*====== Montando a tabela de codificação ===========*/
    int altura = calculaAlturaArvore_Huff(listaArvores);
    unsigned char** tabCode = alocaTabela(altura+1);
    geraTabCode(tabCode, getPrimeiroNo(listaArvores), "", altura+1);
    // imprimeTabCode(tabCode);



    /* ==============  Escrevendo no arquivo com bitmap (codificando) ============== */
    // abrindo o arquivo de entrada de novo pra ler o texto
    FILE * entrada = fopen(path, "r");
    //gerando o arquivo de saida
    int qtdLetras = strlen(path);
    path[qtdLetras-4] = '\0'; // tirar o .txt do path
    FILE* saida = fopen(strcat(path, ".comp"), "w");


    // escrevendo a altura da tabela no arquiv compactado
    //TODO: retirar comentario
    // printf("Escrevedo altura (%d) no arquivo de saida\n", altura); 
    fwrite(&altura, sizeof(int), 1, saida);

    //escrevendo a tabela de codificação no arquivo compactado
    int k=0;
    for(k=0;k<256;k++) fwrite(tabCode[k], sizeof(unsigned char*), 1, saida);

    // printf("(compacta) o: [%s]\n", tabCode['o']);



    
    
    /* ============================= BITMAP ============================= */
    bitmap* bm = bitmapInit(MAX_SIZE);
    int total_gravado = 0, qtdBytes = 0;
    
    //FIXME: esse loop passa pela ultima letra duas vezes (arrumar dps)
    //preenchendo o bitmap
    while(!feof(entrada)){ 
        fscanf(entrada, "%c", &caractere);
        codifica(tabCode, bm, caractere); 
        
        //TODO: retirar
        // preenche_bitmap(getPrimeiroNo(listaArvores), caractere, bm); // antiga
        // fwrite(&bitmapGetContents(bm)[qtdBytes], sizeof(unsigned char),1, saida);
    }

    //escrevendo no arquivo compactado
    for(qtdBytes=0;qtdBytes<bitmapGetLength(bm)-1;qtdBytes++){
        unsigned char aux = bitmapGetBit(bm, qtdBytes);
        fwrite(&aux, sizeof(unsigned char), 1, saida);
    }





    /* ================== Escrevendo tamanho do arquivo no arquivo compactado ================== */

    // printf("tamanho_decimal: %d\n", bitmapGetLength(bm));
    
    // int tamanho_decimal = bitmapGetLength(bm);
    // char inverso[100], tamanho_binario[100];
    // for (i=0;tamanho_decimal > 0;i++ ){
    //     inverso[i] = tamanho_decimal % 2 ? '1' : '0';
    //     tamanho_decimal /= 2;
    // }
    // for(i=0;i<strlen(inverso);i++) tamanho_binario[i] = inverso[strlen(inverso)-i-1];
    

    // printf("tamanho_binario: %s\n", tamanho_binario);
    // fwrite(tamanho_binario, sizeof(char), 1, saida);

    // unsigned char * aux = bitmapGetContents(bm);
    // fwrite(aux, sizeof(unsigned char*), tamanho_decimal, saida);



    // printf("(codifica) imprimindo bitmap\n");
    // for(k=0;k<bitmapGetLength(bm);k++) printf("%d", bitmapGetBit(bm, k));
    // printf("\n");





    /* ======================== Liberando a memória ======================== */
    fclose(entrada);
    fclose(saida);
    liberaTabCode(tabCode);
    bitmapLibera(bm);
    LiberaLista(listaArvores);
    free(v);

    return 0;
}
