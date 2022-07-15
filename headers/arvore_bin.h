#ifndef ARVORE_BIN
#define ARVORE_BIN

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
 * input: caracter a ser inserido, ponteiro para vetor de pesos,
 *        ponteiro para árvore esquerda, ponteiro para árvore direita
 * output: ponteiro para árvore
 * pré-condição: caracter válido, ponteiro para vetor de pesos existe,
 *               ponteiros para árvore esquerda e direita existem
 * pós-condição: ponteiro de retorno aponta para a árvore criada
 */
Arv* abb_cria(char caracter, int* v, Arv* e, Arv* d);

/** Imprime árvore binária
 * input: ponteiro para árvore
 * output: nenhum
 * pré-condição: ponteiro para a árvore existe
 * pós-condição: nenhuma
 */
void abb_imprime(Arv* a);

/** Busca por um caracter na árvore binária
 * input: ponteiro para a árvore, caracter a ser buscado,
 *        ponteiro para vetor de pesos
 * output: nó da arovre que contém o caracter buscado (NULL caso não exista)
 * pré-condição: ponteiro para árvore existe, caracter válido,
 *               ponteiro para vetor de pesos existe
 * pós-condição: ponteiro de retorno aponta para o nó da árvore que contém o caracter buscado
 */
Arv* abb_busca(Arv* a, char caracter, int* v);

/** Insere um caracter na árovre binária
 * input: ponteiro para a árvore, caracter a ser inserido,
 *        ponteiro para vetor de pesos
 * output: ponteiro para árovre com o caracter inserido
 * pré-condição: ponteiro para árvore existe, caracter válido,
 *               ponteiro para vetor de pesos existe
 * pós-condição: ponteiro de retorno aponta para árvore com o caracter adicionado
 */
Arv* abb_insere(Arv* a, char caracter, int* v);

/** Retira um caracter da árvore binária
 * input: ponteiro para a árvore, caracter a ser retirado,
 *        ponteiro para vetor de pesos
 * output: ponteiro para árovre com o caracter retirado
 * pré-condição: ponteiro para árvore existe, caracter válido,
 *               ponteiro para vetor de pesos existe
 * pós-condição: ponteiro de retorno aponta para árvore agora sem o caracter
 */
Arv* abb_retira(Arv* a, char caracter, int* v);

/** Livra memória alocada para a árvore binária
 * input: ponteiro para árovre a ser liberada
 * output: ponteiro para a árvore liberada
 * pré-condição: ponteiro para árvore existe
 * pós-condição: toda a memória alocada para a árvore é liberada
 */
Arv* abb_libera(Arv* a);

#endif // ARVORE_BIN