#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes

int main(int argc, unsigned char**argv) {
    //variaveis uteis    
    int i = 0, j = 0, n = 0, k = 0;
    unsigned char path[100];
    unsigned char caractere = '\0';
    long int *v = malloc(sizeof(long int) * 256);

    
    
    
    
    /* =========================== Vetor de pesos =========================== */
    //limpando vetor
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


    /* =================== Montando a tabela de codificação =================== */
    int altura = calculaAlturaArvore_Huff(listaArvores);
    unsigned char** tabCode = alocaTabela(altura+1);
    geraTabCode(tabCode, getPrimeiroNo(listaArvores), "", altura+1);
    // imprimeTabCode(tabCode);



    /* ============  Escrevendo no arquivo com bitmap (codificando) ============ */
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
    for(k=0;k<256;k++) fwrite(tabCode[k], sizeof(unsigned char*), 1, saida);

    // printf("(compacta) o: [%s]\n", tabCode['o']);



    
    
    /* ================================== BITMAP ================================== */
    bitmap* bm = bitmapInit(MAX_SIZE);
    int qtdBytes = 0;
    
    //preenchendo o bitmap
    while(!feof(entrada)){ 
        fscanf(entrada, "%c", &caractere);
        codifica(tabCode, bm, caractere); 
        
        //TODO: retirar
        // preenche_bitmap(getPrimeiroNo(listaArvores), caractere, bm); // antiga
        // fwrite(&bitmapGetContents(bm)[qtdBytes], sizeof(unsigned char),1, saida);
    }

    







    /* ====== Escrevendo tamanho e conteudo do texto no arquivo compactado ====== */

    long int tamanho = bitmapGetLength(bm);
    
    //FIXME: isso nao funciona
    // fwrite(&tamanho, sizeof(long int), 1, saida);
    // unsigned char * aux = bitmapGetContents(bm);
    // fwrite(aux, sizeof(unsigned char*), 1, saida);

    for(i=0;i<tamanho-1;i++){
        unsigned char aux = bitmapGetBit(bm, i);
        fwrite(&aux, sizeof(unsigned char), 1, saida);
    }


    //TODO: retirar
    // printf("(codifica) imprimindo bitmap\n");
    // for(k=0;k<bitmapGetLength(bm);k++) printf("%d", bitmapGetBit(bm, k));
    // printf("\n");






    /* ========================== Liberando a memória ========================== */
    fclose(entrada);
    fclose(saida);
    liberaTabCode(tabCode);
    bitmapLibera(bm);
    LiberaLista(listaArvores);
    free(v);

    return 0;
}
