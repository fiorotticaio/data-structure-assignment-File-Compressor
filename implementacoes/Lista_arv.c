#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/Arvore_bin.h"
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
    for (p = lista->Prim; p != NULL; p = p->prox) abb_imprime_formato_graphviz(p->arvore); printf("\n");
    printf("}\n\n");
}

void InsereArvUltLista(Lista* lista, Arv* arvore) {
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

Arv* RetiraArvLista(Lista* lista, Arv * arvore) {
    Celula* p = lista->Prim;
    Celula* ant = NULL; 
    
    while (p != NULL) {
        if (p->arvore == arvore) break;

        ant = p;
        p = p->prox;
    }

    if (p==NULL) { // não encontrou o caractere ou a lista está vazia
        printf("Lista vazia ou o caractere '%c' nao foi encontrado\n", abb_get_char(arvore));
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
  
        while (p->prox != q) { 
            if (abb_get_peso(p->arvore) > abb_get_peso(p->prox->arvore)) { 
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
        
        long int pesoTotal = abb_get_peso(p->arvore) + abb_get_peso(p->prox->arvore);
        Arv * a = abb_cria(abb_get_char(p->arvore), pesoTotal, p->arvore, p->prox->arvore);

        prox = p->prox->prox;
        Arv * remover1 = p->prox->arvore;
        Arv * remover2 = p->arvore;

        RetiraArvLista(lista, remover1);
        RetiraArvLista(lista, remover2);
        
        p = prox;

        InsereArvUltLista(lista, a);
        OrdenaLista(lista);
    }
}

int calculaAlturaArvore_Huff(Lista* lista) {
    return abb_altura(lista->Prim->arvore);
}

Arv* GetPrimeiroNoLista(Lista* lista) {
    return lista->Prim->arvore;
}

