
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes

int main(int argc, unsigned char**argv) {
    /* Variaveis uteis */    
    int i = 0, n = 0, k = 0;
    unsigned char path[100];
    unsigned char caractere = '\0';
    long int * v = malloc(sizeof(long int) * 256); // vetor de frequência

    
    for(i = 0; i < 256; i++) v[i] = 0; // limpando o vetor de frequência

    /* caminho do arquivo passado na execucao do programa */
    sprintf(path, "%s", argv[1]);
    FILE * arquivo = fopen(path, "r");

    /* lendo o arquivo de texto e anotando as frequências no vetor */
    while(!feof(arquivo)){
        if (caractere != '\0') v[caractere] += 1;
        fscanf(arquivo, "%c", &caractere);
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
    // ImprimeLista(listaArvores);


    /* Montando a tabela de codificação */
    int altura = calculaAlturaArvore_Huff(listaArvores);
    unsigned char** tabCode = alocaTabela(altura+1);
    geraTabCode(tabCode, getPrimeiroNo(listaArvores), "", altura+1);
    // imprimeTabCode(tabCode);


    
    /* abrindo o arquivo de entrada de novo pra ler o texto */
    FILE * entrada = fopen(path, "r");

    /* gerando o arquivo de saida */
    int qtdLetras = strlen(path);
    path[qtdLetras-4] = '\0'; // tirar a extensão do path
    FILE* saida = fopen(strcat(path, ".comp"), "wb");


    /* escrevendo o vetor de frequência no arquivo compactado,
    ele é nossa chave de decodificação */
    fwrite(v, sizeof(long int), 256, saida); 


    int tam_nao_codificado = 0;
    /* loop apenas para contar o tamanho do conteúdo do aquivo de entrada */
    while(!feof(entrada)) {
        fscanf(entrada, "%c", &caractere);
        tam_nao_codificado++;
    }
    
    rewind(entrada); // volta pro início do arquivo

    
    bitmap* bm = bitmapInit(MAX_SIZE);

    int j = 0;
    for(i = 0; i < tam_nao_codificado-1; i++) {
        fscanf(entrada, "%c", &caractere);

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