#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 1000000 // teste com 1 MEGA bytes

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
            InsereArvUlt(listaArvores, abb_cria(1, (char)i, v[i], abb_cria_vazia(), abb_cria_vazia()));
        }
    }

    ImprimeLista(listaArvores);
    
    OrdenaLista(listaArvores);

    ImprimeLista(listaArvores);

    Aplica_Huffman(listaArvores);

    // CodificaNos(listaArvores); acho que não vai precisar mais
    // era fonte de um monte daqueles ERROS

    ImprimeLista(listaArvores);




    /*====== montando a tabela de codificação ===========*/
    int altura = calculaAlturaArvore_Huff(listaArvores);
    unsigned char** tabCode = alocaTabela(altura+1);
    geraTabCode(tabCode, getPrimeiroNo(listaArvores), "", altura+1);
    imprimeTabCode(tabCode);



    /*=========== Escrevendo no arquivo com bitmap (codificando) =========================*/

    // abrindo o arquivo de entrada de novo pra ler o texto
    FILE * entrada = fopen(path, "r");
    //gerando o arquivo de saida
    int qtdLetras = strlen(path);
    path[qtdLetras-4] = '\0'; // tirar o .txt do path
    FILE* saida = fopen(strcat(path, ".comp"), "w");


    // escrevendo a altura da tabela no arquivo compactado (teste)
    fwrite(&altura, sizeof(int), 1, saida);


    // criando o bitmap
    bitmap* bm = bitmapInit(MAX_SIZE);
    int qtdBytes = 0;

    // loop pra preencher o bitmap
    while(!feof(entrada)){
        fscanf(entrada, "%c", &caractere);
        codifica(tabCode, bm, caractere); 
        qtdBytes++;
    }

    // escrevendo o bitmap no arquivo compactado
    i = 0;
    while (i < qtdBytes) {
        // não tenho certeza se ta imprimindo certo, tem que descompactar pra ver 
        fwrite(&(bitmapGetContents(bm)[i]), sizeof(unsigned char), 1, saida);
        i++;
    }

    

    fclose(entrada);
    fclose(saida);

    liberaTabCode(tabCode);
    bitmapLibera(bm);
    LiberaLista(listaArvores);
    free(v);

    return 0;
}