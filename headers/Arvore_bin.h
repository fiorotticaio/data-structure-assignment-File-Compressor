#ifndef ARVORE_BIN
#define ARVORE_BIN

#include "../headers/bitmap.h"

// Tipo Arv (árvore binária)
typedef struct arv Arv;

/** Cria uma árvore vazia (nó folha)
 * input: nenhum
 * output: ponteiro para a árvore vazia
 * pré-condição: nenhuma
 * pós-condição: ponteiro de retorno aponta para a árvore vazia
 */
Arv* abb_cria_vazia(void);

/** Cria árvore com subarvores esquerda e direita
 * input: variavel de controle (ehFolha) para algoritmo de Huffman
 *        caracter a ser inserido, ponteiro para vetor de pesos,
 *        ponteiro para árvore esquerda, ponteiro para árvore direita
 * output: ponteiro para árvore
 * pré-condição: caracter válido, ponteiro para vetor de pesos existe,
 *               ponteiros para árvore esquerda e direita existem
 * pós-condição: ponteiro de retorno aponta para a árvore criada
 */
Arv* abb_cria(unsigned char caracter, long int peso, Arv* e, Arv* d);

/** Imprime árvore binária
 * input: ponteiro para árvore
 * output: nenhum
 * pré-condição: ponteiro para a árvore existe
 * pós-condição: nenhuma
 */
void abb_imprime(Arv* a);

/** Imprime árvore binária
 * input: ponteiro para árvore
 * output: nenhum
 * pré-condição: ponteiro para a árvore existe
 * pós-condição: nenhuma
 */
void abb_imprime_formato_graphviz(Arv * a);

/** Insere um caracter na árovre binária
 * input: ponteiro para a árvore, caracter a ser inserido,
 *        peso do caractere
 * output: ponteiro para árovre com o caracter inserido
 * pré-condição: ponteiro para árvore existe, caracter válido,
 *               ponteiro para vetor de pesos existe
 * pós-condição: ponteiro de retorno aponta para árvore com o caracter adicionado
 */
Arv* abb_insere(Arv* a, unsigned char caracter, long int peso);

/** Retira um caracter da árvore binária
 * input: ponteiro para a árvore, caracter a ser retirado,
 *        peso do caractere
 * output: ponteiro para árovre com o caracter retirado
 * pré-condição: ponteiro para árvore existe, caracter válido,
 *               ponteiro para vetor de pesos existe
 * pós-condição: ponteiro de retorno aponta para árvore agora sem o caracter
 */
Arv* abb_retira(Arv* a, unsigned char caracter, long int peso);

/** Livra memória alocada para a árvore binária
 * input: ponteiro para árovre a ser liberada
 * output: ponteiro para a árvore liberada
 * pré-condição: ponteiro para árvore existe
 * pós-condição: toda a memória alocada para a árvore é liberada
 */
Arv* abb_libera(Arv* a);

/** Retorna o peso do caractere localizado em um nó
 * input: ponteiro para arvore com o nó
 * output: inteiro com valor do peso do caractere
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
long int abb_get_peso(Arv * a);

/** Retorna o caractere localizado em um nó
 * input: ponteiro para arvore com o nó
 * output: caractere
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
unsigned char abb_get_char(Arv * a);

/** Retorna o ponteiro para o ramo esquerdo da arvore
 * input: ponteiro para arvore
 * output: ponteiro para ramo esquerdo
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
Arv * abb_get_esq(Arv * a);

/** Retorna o ponteiro para o ramo direito da arvore
 * input: ponteiro para arvore
 * output: ponteiro para ramo direito
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
Arv * abb_get_dir(Arv * a);

/** Verifica se a árvore está vazia
 * input: ponteiro para arvore
 * output: 1 se a árvore estiver vazia, 0 caso contrário
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
int abb_vazia(Arv* a);

/** Calcula a altura da árvore
 * input: ponteiro para arvore
 * output: altura da árvore
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
int abb_altura(Arv* a);

/** Aloca memória para a tabela de codificação
 * input: número de colunas da tabela
 * output: ponteiro para tabela de codificação (ponteiro para vetor de ponteiros)
 * pré-condição: número de colunas válido
 * pós-condição: memória para a tabela de codificação é alocada
 */
unsigned char** abb_aloca_tabela(int colunas);

/** Faz a codificação para a tabela de codificação
 * input: ponteiro para a tabela de codificação, ponteiro para nó raiz da árvore de huffman
 *        ponteiro para o código (caminho) a ser inserido no nó, número de colunas da tabela
 * output: nenhum
 * pré-condição: ponteiro para a tebela de codificação existe, ponteiro para nó raiz da árvore existe,
 *               ponteiro para código existe, número de colunas válido 
 * pós-condição: tabela de codificação é preenchida
 */
void abb_gera_tabela(unsigned char** tabela, Arv* a, char* caminho, int colunas);

/** Imprime a tabela de codificação
 * input: ponteiro para a tabela de codificação
 * output: nenhum
 * pré-condição: ponteiro para a tabela de codificação existe
 * pós-condição: tabela não é alterada
 */
void abb_imprime_tabela(unsigned char** tabela);

/** Libera toda a memória alocada para a tabela de codificação
 * input: ponteiro para a tabela de codificação
 * output: nenhum
 * pré-condição: ponteiro para a tabela de codificação existe
 * pós-condição: toda a memória alocada para a tabela de codificação é liberada
 */
void abb_libera_tabela(unsigned char** tabela);

/** Faz a serielização da árvore (transforma em string gigante)
 * input: ponteiro para a arvore e para string, e inteiro indice
 * output: inteiro para indice (usado na recursão)
 * pré-condição: ponteiros existem e indice é 0
 * pós-condição: árvore é serielizada em uma string única
 */
void abb_serializa(Arv * a, bitmap * bm);

/** Faz o processo inverso da serielização da árvore
 * input: ponteiro para a arvore e para string, e inteiro indice
 * output: inteiro para indice (usado na recursão)
 * pré-condição: ponteiros existem e indice é 0
 * pós-condição: string é desserielizada para criar arvore
 */
int abb_desserializa(Arv *a, char * serielizacao, int indice);

#endif // ARVORE_BIN