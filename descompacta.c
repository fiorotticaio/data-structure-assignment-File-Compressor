#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./headers/Lista_arv.h"
#include "./headers/bitmap.h"

#define MAX_SIZE 3567587328 // Limite de 3 GIGA bytes


static unsigned int bit(unsigned char byte, int pos){
    unsigned char aux = (1 << pos);
    return byte & aux;
}


int main(int argc, char **argv) {
    /* Variaveis uteis */
    int i = 0, j = 0, altura = 0, k = 0;
    long int *v = malloc(sizeof(long int) * 256);  // vetor de frequência
    char path[100];

    /* Caminho do arquivo passado na execucao do programa */
    sprintf(path, "%s", argv[1]);
    FILE * entrada = fopen(path, "rb");


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
    // ImprimeLista(listaArvores);


    /* gerando o arquivo de saída */
    path[strlen(path)-5] = '\0'; // tirando o .comp do nome
    //TODO: mudar o nome depois
    strcat(path, "_saida.txt");

    FILE * saida = fopen(path, "wr");

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
                fprintf(saida, "%c", getChar(aux));
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