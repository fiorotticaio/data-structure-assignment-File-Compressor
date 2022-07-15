#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula Celula;

struct lista {
    Celula* Prim;
    Celula* Ult;
};

struct celula {
    Aluno* aluno;
    Celula* prox;
};

Lista* InicializaListaVazia() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));

    /* lista vazia */
    lista->Prim = NULL;
    lista->Ult = NULL;

    return lista;
}

void DestroiLista(Lista* lista) {
    Celula* p = lista->Prim;
    Celula* temp;

    while (p != NULL) {
        temp = p->prox;
        free(p);
        p = temp;
    }

    free(lista);
}

void ImprimeLista(Lista* lista) {
    Celula* p;

    if (lista->Prim == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    for (p = lista->Prim; p != NULL; p = p->prox) {
        ImprimeAluno(p->aluno);
    }
}

void InsereAlunoUlt(Lista* lista, Aluno* aluno) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->aluno = aluno;
    nova->prox = NULL;

    if(lista->Prim == NULL) { // lista vazia
        lista->Prim = nova;
        lista->Ult = nova;
        return;
    }

    lista->Ult->prox = nova; 
    lista->Ult = nova;
}

void InsereAlunoPrim(Lista* lista, Aluno* aluno) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));

    nova->aluno = aluno;
    nova->prox = lista->Prim;
    lista->Prim = nova;

    if (lista->Ult == NULL) { // lista estava vazia inicialmente
        lista->Ult = nova;
    }
}

Aluno* RetiraAlunoLista(Lista* lista, char* nome) {
    Celula* p = lista->Prim;
    Celula* ant = NULL; 
    Aluno* aluno;

    while (p != NULL && strcmp(RetornaNomeAluno(p->aluno), nome)) {
        ant = p; // incremento
        p = p->prox;
    }

    if (p == NULL) { // não encontrou o aluno ou a lista está vazia
        printf("Lista vazia ou aluno %s nao encontrado\n", nome);
        return NULL;
    }

    aluno = p->aluno;

    if (p == lista->Prim && p == lista->Ult) { // lista com só 1 aluno
        // lista volta a ficar vazia
        lista->Prim = NULL;
        lista->Ult = NULL;

    } else if (lista->Prim == p) { // primera célula
        lista->Prim = p->prox;

    } else if (lista->Ult == p) { // última célula
        lista->Ult = ant;
        ant->prox = NULL;

    } else { // célula no meio da lista
        ant->prox = p->prox;
    }

    free(p);
    return aluno;
}