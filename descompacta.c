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
    /* variáveis úteis */
    int i = 0, j = 0, altura = 0, k = 0;
    unsigned char path[100];
    unsigned char diretorio[1000]; // diretório deve ter no máximo 1000 caracteres

    /* caminho do arquivo passado na execucao do programa */
    sprintf(path, "%s", argv[1]);
    FILE * entrada = fopen(path, "rb");

    int tam_extensao = 0;
    /* lendo o tamanho da extensão do aquivo a ser compactado */
    fread(&tam_extensao, sizeof(int), 1, entrada);
    unsigned char * extensao = malloc(sizeof(unsigned char) * (tam_extensao+1)); // +1 para o '\0'
    
    /* lendo a extensão em sim */
    fread(extensao, sizeof(unsigned char), tam_extensao, entrada);
    extensao[tam_extensao] = '\0';

    // lendo o tamanho da arvore serielizada
    int tam_arvore_serielizada;
    fread(&tam_arvore_serielizada, sizeof(int), 1, entrada);

    //lendo a arvore serielizada
    char * serielizacao = malloc(sizeof(char)*(tam_arvore_serielizada+1));// +1 para o '\0'
    unsigned char byte;
    for(i = 0; i < tam_arvore_serielizada; i+=8){
        fread(&byte, sizeof(unsigned char),1, entrada);
        for (j = 7; j >= 0; j--){
            if (bit(byte, j)) serielizacao[k] = '1';
            else serielizacao[k] = '0';
            k++;
        }
    }
    serielizacao[k]='\0';

    //desserializando a arvore
    Arv * arv_huffman = abb_cria('-', 0, abb_cria_vazia(), abb_cria_vazia());
    abb_desserializa(arv_huffman, serielizacao, 0);
    // abb_imprime_formato_graphviz(arv_huffman);

    /* gerando o arquivo de saída */
    path[strlen(path)-5] = '\0'; // tirando o .comp do nome
    strcat(path, extensao); // juntando com a extensão original

    /* gerando o arquivo de saída numa pasta separada pra poder comparar com diff */
    // TODO: tirar dessa pasta separada e colocar no diretorio raiz mesmo
    sprintf(diretorio, "arquivos_de_saida/%s", path);
    FILE * saida = fopen(diretorio, "wb");

    // lendo tamanho codificado
    int tam_codificado=0;
    fread(&tam_codificado, sizeof(int), 1, entrada);

    //lendo conteudo do texto compactado e usando a arvore para decodificar
    Arv * aux = arv_huffman;
    for (j=0;j<tam_codificado;j+=8) {
        fread(&byte, sizeof(unsigned char), 1, entrada);
        int k=0;
        for (i = 7; i >= 0; i--) {
            k++;
            if(j+k>=tam_codificado+1) break; //isso é para evitar que bits lixo sejam descompactados

            if (bit(byte, i)) {
                aux = abb_get_dir(aux);
            } else {
                aux = abb_get_esq(aux);
            }

            if (abb_get_esq(aux) == NULL && abb_get_dir(aux) == NULL) {
                unsigned char auxChar = abb_get_char(aux);
                fwrite(&auxChar, sizeof(unsigned char), 1, saida);
                aux = arv_huffman;
            }
        }
    }

    /* liberando toda a memória alocada */
    fclose(entrada);
    fclose(saida);
    abb_libera(arv_huffman);
    free(serielizacao);
    free(extensao);

    return 0;
}