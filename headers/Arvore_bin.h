#ifndef ARVORE_BIN
#define ARVORE_BIN

#include "../headers/bitmap.h"

// Tipo Arv (árvore binária)
typedef struct arv Arv;


/*================ FUNÇÕES BÁSICAS ==============================*/

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
Arv* abb_cria(int ehFolha, char caracter, long int peso, Arv* e, Arv* d);

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

/** Gera o bitmap
 * input: ponteiro para a árvore de huffman, caracter a ser codificado,
 *        e o bitmap que está sendo gerado
 * output: nenhum
 * pré-condição: ponteiro para a árvore existe
 * pós-condição: nenhuma
 */
void preenche_bitmap(Arv* a, char caracter, bitmap* bm);

/** Insere um caracter na árovre binária
 * input: ponteiro para a árvore, caracter a ser inserido,
 *        peso do caractere
 * output: ponteiro para árovre com o caracter inserido
 * pré-condição: ponteiro para árvore existe, caracter válido,
 *               ponteiro para vetor de pesos existe
 * pós-condição: ponteiro de retorno aponta para árvore com o caracter adicionado
 */
Arv* abb_insere(Arv* a, char caracter, long int peso);

/** Retira um caracter da árvore binária
 * input: ponteiro para a árvore, caracter a ser retirado,
 *        peso do caractere
 * output: ponteiro para árovre com o caracter retirado
 * pré-condição: ponteiro para árvore existe, caracter válido,
 *               ponteiro para vetor de pesos existe
 * pós-condição: ponteiro de retorno aponta para árvore agora sem o caracter
 */
Arv* abb_retira(Arv* a, char caracter, long int peso);

/** Livra memória alocada para a árvore binária
 * input: ponteiro para árovre a ser liberada
 * output: ponteiro para a árvore liberada
 * pré-condição: ponteiro para árvore existe
 * pós-condição: toda a memória alocada para a árvore é liberada
 */
Arv* abb_libera(Arv* a);

/** Seta o código do nó
 * input: ponteiro para arvore binári e ponteiro para o código a ser setado
 * output: nenhum
 * pré-condição: ponteiro para árvore e código existem
 * pós-condição: campo de código do nó é atualizado
 */
void setCodigo(Arv* a, char* codigo);

/** Retorna o peso do caractere localizado em um nó
 * input: ponteiro para arvore com o nó
 * output: inteiro com valor do peso do caractere
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
long int getPeso(Arv * a);

/** Retorna o caractere localizado em um nó
 * input: ponteiro para arvore com o nó
 * output: caractere
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
char getChar(Arv * a);

/** Retorna o ponteiro para o ramo esquerdo da arvore
 * input: ponteiro para arvore
 * output: ponteiro para ramo esquerdo
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
Arv * getRamoEsq(Arv * a);

/** Retorna o ponteiro para o ramo direito da arvore
 * input: ponteiro para arvore
 * output: ponteiro para ramo direito
 * pré-condição: ponteiro para árvore existe
 * pós-condição: arvore não é alterada
 */
Arv * getRamoDir(Arv * a);

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

/** Codifica todos os nós folha da árvore de huffman
 * input: ponteiro para arvore e ponteiro para o código a ser inserido no nó
 * output: nenhum
 * pré-condição: ponteiro para árvore e código existem
 * pós-condição: campo código de todos os nós folha preenchidos
 */
void abb_codifica_nos(Arv* a, char* codigo);

#endif // ARVORE_BIN