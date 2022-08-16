#ifndef LISTA_H
#define LISTA_H

#include "Arvore_bin.h"

//Tipo Lista de Arvores
typedef struct lista Lista;

/** Cria uma Lista vazia
 * input: nenhum
 * output: ponteiro para a Lista vazia
 * pré-condição: nenhuma
 * pós-condição: ponteiro de retorno aponta para a lista vazia
 */
Lista* InicializaListaVazia();

/** Livra memória alocada para a lista
 * input: ponteiro para lista a ser liberada
 * output: ponteiro para a lista liberada
 * pré-condição: ponteiro para lista existe
 * pós-condição: toda a memória alocada para a lista é liberada
 */
void LiberaLista(Lista* lista);

/** Imprime lista 
 * input: ponteiro para lista
 * output: nenhum
 * pré-condição: ponteiro para a lista existe
 * pós-condição: nenhuma
 */
void ImprimeLista(Lista* lista);

/** Insere um caracter na lista
 * input: ponteiro para a lista, árvore a ser inserido,
 * output: ponteiro para lista com a árvore inserida
 * pré-condição: ponteiro para lista e para árvore existem
 * pós-condição: ponteiro de retorno aponta para lista com a árvore adicionada
 */
void InsereArvUltLista(Lista* lista, Arv* arvore);

/** Retira uma árvore da lista
 * input: ponteiro para a lista, árvore a ser retirada,
 * output: ponteiro para árvore retirada
 * pré-condição: ponteiro para lista existe, árvore válida,
 *               ponteiro para vetor de pesos existe
 * pós-condição: ponteiro de retorno aponta para lista agora sem a árvore
 */
Arv* RetiraArvLista(Lista* lista, Arv * arvore);

/** Ordena a lista de arvore em relação aos pesos
 * input: ponteiro para a lista
 * output: nenhum
 * pré-condição: ponteiro para lista existe
 * pós-condição: lista agora está ordenada
 */
void OrdenaLista(Lista * lista);

/** Aplica o algoritmo de Huffman para a lista de árvores
 * input: ponteiro para a lista
 * output: nenhum
 * pré-condição: ponteiro para lista existe
 * pós-condição: lista agora tem apenas um elemento que é uma árvore
 */
void Aplica_Huffman(Lista * lista);

/** Calcula a altura da árvore de huffman (primeira árvore da lista final)
 * input: ponteiro para a lista
 * output: altura da árvore de huffman (primeira árvore da lista)
 * pré-condição: ponteiro para lista existe
 * pós-condição: lista não é modificada
 */
int calculaAlturaArvore_Huff(Lista* lista);

/** Retorna a primeira árvore de uma lista de árvores
 * input: ponteiro para a lista
 * output: ponteiro para a primeira árvore da lista
 * pré-condição: ponteiro para lista existe
 * pós-condição: lista não é modificada
 */
Arv* GetPrimeiroNoLista(Lista* lista);

#endif // LISTA_H