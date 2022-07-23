#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/Lista_arv.h"

typedef struct celula Celula;

struct lista {
    Celula* Prim;
    Celula* Ult;
    int tam;
};

struct celula {
    Arv* arvore;
    Celula* prox;
};

Lista* InicializaListaVazia() {
    Lista* lista = malloc(sizeof(Lista));

    lista->Prim = NULL;
    lista->Ult = NULL;
    lista->tam = 0;

    return lista;
}

void LiberaLista(Lista* lista) {
    Celula* p = lista->Prim;
    Celula* temp;

    while (p != NULL) {
        temp = p->prox;
        abb_libera(p->arvore);
        free(p);
        p = temp;
    }

    free(lista);
}

void ImprimeLista(Lista* lista) {
    if (lista->Prim == NULL) return;

    Celula* p;
    for (p = lista->Prim; p != NULL; p = p->prox) abb_imprime(p->arvore); printf("\n");

    //impressao no formato graphviz
    printf("digraph G {\n\n");
    // for (p = lista->Prim; p != NULL; p = p->prox) abb_imprime_formato_graphviz(p->arvore); printf("\n");
    printf("}\n\n");
}

void InsereArvUlt(Lista* lista, Arv* arvore) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->arvore = arvore;
    nova->prox = NULL;

    if(lista->Prim == NULL) { // lista vazia
        lista->Prim = nova;
        lista->Ult = nova;
        return;
    }

    lista->Ult->prox = nova; 
    lista->Ult = nova;

    lista->tam++;
}

//TODO: retirar isso no futuro

// void InsereArvPrim(Lista* lista, Arv* aluno) {
//     Celula* nova = (Celula*) malloc(sizeof(Celula));

//     nova->aluno = aluno;
//     nova->prox = lista->Prim;
//     lista->Prim = nova;

//     if (lista->Ult == NULL) { // lista estava vazia inicialmente
//         lista->Ult = nova;
//     }
// }

Arv* RetiraArvLista(Lista* lista, Arv * arvore) {
    Celula* p = lista->Prim;
    Celula* ant = NULL; 
    
    while (p != NULL) {
        if (p->arvore == arvore) break;

        ant = p;
        p = p->prox;
    }

    if (p==NULL) { // não encontrou o caractere ou a lista está vazia
        printf("Lista vazia ou o caractere '%c' nao foi encontrado\n", getChar(arvore));
        return NULL;
    }

    // lista com só 1 arvore
    if (p == lista->Prim && p == lista->Ult) { 
        // lista volta a ficar vazia
        lista->Prim = NULL;
        lista->Ult = NULL;

    // primera célula
    } else if (lista->Prim == p) { 
        lista->Prim = p->prox;

    // última célula
    } else if (lista->Ult == p) { 
        lista->Ult = ant;
        ant->prox = NULL;

    // célula no meio da lista
    } else { 
        ant->prox = p->prox;
    }

    free(p);
    lista->tam--;

    return arvore;
}

void OrdenaLista(Lista * lista){
    if (lista->Prim == NULL) return;

    int precisaTrocar = 1;

    Celula * p = NULL;
    Celula * q = NULL;

    do { 
        precisaTrocar = 0; 
        p = lista->Prim; 
  
        while (p->prox != q) 
        { 
            if (getPeso(p->arvore) > getPeso(p->prox->arvore)) 
            { 
                Arv * temp = p->arvore;
                p->arvore = p->prox->arvore;
                p->prox->arvore = temp;

                precisaTrocar = 1; 
            } 
            p = p->prox; 
        } 

        q = p; 

    } while (precisaTrocar);
}

//FIXME: deve ser feito com recursão? Acredito que não seja necessário
void Aplica_Huffman(Lista * lista){
    if (lista->Prim == NULL) return;

    Celula * p = lista->Prim;
    Celula * prox = p->prox;
    
    while(p!=NULL && p->prox!=NULL) {
        
        long int pesoTotal = getPeso(p->arvore) + getPeso(p->prox->arvore);
        Arv * a = abb_cria(0, '-', pesoTotal, p->arvore, p->prox->arvore);

        prox = p->prox->prox;
        Arv * remover1 = p->prox->arvore;
        Arv * remover2 = p->arvore;

        RetiraArvLista(lista, remover1);
        RetiraArvLista(lista, remover2);
        
        p = prox;

        InsereArvUlt(lista, a);
    }
}

int calculaAlturaArvore_Huff(Lista* lista) {
    return abb_altura(lista->Prim->arvore);
}

Arv* getPrimeiroNo(Lista* lista) {
    return lista->Prim->arvore;
}

void CodificaNos(Lista* lista) {
    char* codigo = strdup("");
    abb_codifica_nos(lista->Prim->arvore, codigo);
    free(codigo);
}