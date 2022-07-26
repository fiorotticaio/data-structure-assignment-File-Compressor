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
    liberaTabCode(tabCode);


    /*=========== Escrevendo no arquivo com bitmap (codificando) =========================*/

    // abrindo o arquivo de entrada de novo pra ler o texto
    FILE * entrada = fopen(path, "r");
    //gerando o arquivo de saida
    int qtdLetras = strlen(path);
    path[qtdLetras-4] = '\0'; // tirar o .txt do path
    FILE* saida = fopen(strcat(path, ".comp"), "w");

    // criando o bitmap
    bitmap* bm = bitmapInit(MAX_SIZE);
    int total_gravado = 0, qtdBytes = 0;

    // loop pra preencher o bitmap
    while(!feof(entrada)){
        fscanf(entrada, "%c", &caractere);
        // codifica(tabCode, bm, caractere); // não sei o porquê não funciona
        // preenche_bitmap(getPrimeiroNo(listaArvores), caractere, bm); // antiga
        // total_gravado = fwrite(bm, sizeof(bitmap*), 8, saida); // isso ta errado
        qtdBytes++;
    }

    i = 0;
	for (i = 0; i < bitmapGetLength(bm); i++) {
		printf("bit #%d = %0x\n", i, bitmapGetBit(bm, i));
	}

    printf("\n");
    printf("bm length: %d\n", bitmapGetLength(bm));
    printf("qtdBytes: %d\n", qtdBytes);
    printf("total gravado: %d\n", total_gravado);

    fclose(entrada);
    fclose(saida);

    bitmapLibera(bm);
    LiberaLista(listaArvores);
    free(v);

    return 0;
}
