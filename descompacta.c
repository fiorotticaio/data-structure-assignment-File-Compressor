#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./headers/Lista_arv.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes

static unsigned int bit(unsigned char byte, int pos){
    unsigned char aux = (1 << pos);
    return byte & aux;
}


int main(int argc, char **argv) {
    /* Variaveis uteis */
    int i = 0, j = 0, altura = 0, k = 0;
    long int *v = malloc(sizeof(long int) * 256);  // vetor de frequência
    unsigned char path[100];
    unsigned char diretorio[1000]; // diretório deve ter no máximo 1000 caracteres

    /* Caminho do arquivo passado na execucao do programa */
    sprintf(path, "%s", argv[1]);
    FILE * entrada = fopen(path, "rb");


    int tamExtensao = 0;
    /* lendo o tamanho da extensão do aquivo a ser compactado */
    fread(&tamExtensao, sizeof(int), 1, entrada);
    unsigned char extensao[tamExtensao+1]; // +1 para o '\0'
    /* lendo a extensão em sim */
    fread(extensao, sizeof(unsigned char), tamExtensao, entrada);


    /* lendo o vetor de frequências */
    fread(v, sizeof(long int), 256, entrada);
    

    /* inserindo as arvores com as frequências na lista */
    Lista * listaArvores = InicializaListaVazia();
    for(i = 0; i < 256; i++) {
        if (v[i] > 0) {
            InsereArvUlt(listaArvores, abb_cria((char)i, v[i], abb_cria_vazia(), abb_cria_vazia()));
        }
    }

    OrdenaLista(listaArvores);
    Aplica_Huffman(listaArvores);


    /* gerando o arquivo de saída */
    path[strlen(path)-5] = '\0'; // tirando o .comp do nome
    strcat(path, extensao); // juntando com a extensão original


    /* gerando o arquivo de saída numa pasta separada pra poder comparar com diff */
    // TODO: tirar dessa pasta separada e colocar no diretorio raiz mesmo
    sprintf(diretorio, "arquivos_de_saida/%s", path);

    FILE * saida = fopen(diretorio, "wb");

    unsigned char byte;
    Arv * raiz = getPrimeiroNo(listaArvores);
    Arv * aux = raiz;

    while (fread(&byte, sizeof(unsigned char), 1, entrada)) {
        for (i = 7; i >= 0; i--) {
            if (bit(byte, i)) {
                aux = getRamoDir(aux);
            } else {
                aux = getRamoEsq(aux);
            }

            if (getRamoEsq(aux) == NULL && getRamoDir(aux) == NULL) {
                // fprintf(saida, "%c", getChar(aux));
                unsigned char auxChar = getChar(aux);
                fwrite(&auxChar, sizeof(unsigned char), 1, saida);
                aux = raiz;
            }
        }
    }


    /* liberando toda a memória alocada */
    fclose(entrada);
    fclose(saida);
    LiberaLista(listaArvores);
    free(v);

    return 0;
}