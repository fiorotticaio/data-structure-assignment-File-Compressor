
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes

int main(int argc, unsigned char**argv) {
    /* Variaveis uteis */    
    int i = 0, j = 0, n = 0, k = 0;
    unsigned char path[100];
    unsigned char caractere = '\0';
    long int * v = malloc(sizeof(long int) * 256); // vetor de frequência

    
    for(i = 0; i < 256; i++) v[i] = 0; // limpando o vetor de frequência

    /* caminho do arquivo passado na execucao do programa */
    sprintf(path, "%s", argv[1]);
    FILE * arquivo = fopen(path, "rb");

    /* pegando a extensão do arquivo de entrada */
    i = 0;
    while (path[i] != '.') {
        i++;
    }
    unsigned char extensao[10]; // a extensão do arquivo deve conter no máximo 10 caracteres 
    sprintf(extensao, "%s", path+i);


    /* lendo o arquivo de texto e anotando as frequências no vetor */
    caractere = '\0';
    while(!feof(arquivo)){
        fread(&caractere, sizeof(unsigned char), 1, arquivo);
        if (caractere != '\0') v[caractere] += 1;
    }
    fclose(arquivo);


    /* inserindo as árvores com as frequências na lista */
    Lista * listaArvores = InicializaListaVazia();
    for(i = 0; i < 256; i++) {
        if (v[i] > 0) {
            InsereArvUlt(listaArvores, abb_cria((char)i, v[i], abb_cria_vazia(), abb_cria_vazia()));
        }
    }

    OrdenaLista(listaArvores);
    Aplica_Huffman(listaArvores);


    /* Montando a tabela de codificação */
    int altura = calculaAlturaArvore_Huff(listaArvores);
    unsigned char** tabCode = alocaTabela(altura+1);
    geraTabCode(tabCode, getPrimeiroNo(listaArvores), "", altura+1);

    
    /* abrindo o arquivo de entrada de novo pra ler o texto */
    FILE * entrada = fopen(path, "rb");

    /* gerando o arquivo de saida */
    int qtdLetras = strlen(path);
    path[qtdLetras-4] = '\0'; // tirar a extensão do path
    FILE* saida = fopen(strcat(path, ".comp"), "wb");


    /* a primeira coisa do arquivo compactado vai ser o tamanho extensao 
    do arquivo a ser descompactado seguido da propria extensão */
    int tamExtnesao = strlen(extensao);
    fwrite(&tamExtnesao, sizeof(int), 1, saida);
    fwrite(extensao, sizeof(unsigned char), tamExtnesao, saida);


    /* escrevendo o vetor de frequência no arquivo compactado,
    ele é nossa chave de decodificação */
    fwrite(v, sizeof(long int), 256, saida); 


    int tam_nao_codificado = 0;
    /* loop apenas para contar o tamanho do conteúdo do aquivo de entrada */
    while(!feof(entrada)) {
        fread(&caractere, sizeof(unsigned char), 1, entrada);
        tam_nao_codificado++;
    }
    
    rewind(entrada); // volta pro início do arquivo


    bitmap* bm = bitmapInit(MAX_SIZE);
  

    for (i = 0; i < tam_nao_codificado-1; i++) {
        fread(&caractere, sizeof(unsigned char), 1, entrada);

        /* montando o vetor de bits (codificado) correspondente ao conteúdo */
        for(j = 0; j < strlen(tabCode[caractere]); j++) {
            if (tabCode[caractere][j] == '1') bitmapAppendLeastSignificantBit(bm, 1);
            else if (tabCode[caractere][j] == '0') bitmapAppendLeastSignificantBit(bm, 0);
        }
    }


    int resto = bitmapGetLength(bm)%8;
    if (resto != 0) {
        /* completando o resto do byte (com zeros) */
        while (resto < 8) {
            bitmapAppendLeastSignificantBit(bm, 0);
            resto++;
        }
    }

    /* escrevendo os bytes no arquivo compactado */
    for (i = 0; i < bitmapGetLength(bm)/8; i++) {
        fwrite(&bitmapGetContents(bm)[i], sizeof(unsigned char), 1, saida);
    }


    /* liberando toda a memória alocada */
    bitmapLibera(bm);
    fclose(entrada);
    fclose(saida);
    liberaTabCode(tabCode);
    LiberaLista(listaArvores);
    free(v);

    return 0;
}