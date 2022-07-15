#include "arvore_bin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arv {
    char info;
    int peso;
    struct arv *esq;
    struct arv *dir;
};

Arv* abb_cria_vazia(void) {
    return NULL;
}

Arv* abb_cria(char caracter, int* v, Arv* e, Arv* d) {
    Arv* p = (Arv*) malloc(sizeof(Arv));
    p->info = caracter;
    p->info = v[caracter];
    p->esq = e;
    p->dir = d;
    return p;
}

void abb_imprime(Arv* a) {
    printf("<");
    if (a != NULL) {
        printf("%c", a->info);
        abb_imprime(a->esq);
        abb_imprime(a->dir);
    }
    printf(">");
}

Arv* abb_busca(Arv* a, char caracter, int* v) {
    if (a == NULL) return NULL;
    else if (getPeso(a) > v[caracter]) return abb_busca(a->esq, caracter, v);
    else if (getPeso(a) < v[caracter]) return abb_busca(a->dir, caracter, v);
    else return a;
}

Arv* abb_insere(Arv* a, char caracter, int* v) {
    if (a == NULL) { // árvore vazia 
        a = (Arv*) malloc(sizeof(Arv));
        a->info = caracter;
        a->peso = v[caracter];
        a->esq = NULL;
        a->dir = NULL;

    // inserir na esquerda
    } else if (v[caracter] < a->peso) {
        a->esq = abb_insere(a->esq, caracter, v);

    // inserir na direita
    } else if (v[caracter] > a->peso) { 
        a->dir = abb_insere(a->dir, caracter, v);

    } else if (caracter == a->info) { 
        printf("Caracter %c jah existe na arvore\n", caracter);
    }

    return a;
}

Arv* abb_retira(Arv* a, char caracter, int* v) {
    if (a == NULL) {
        return NULL;

    // procura na subarvore da esquerda
    } else if (a->peso > v[caracter]) {
        a->esq = abb_retira(a->esq, caracter, v);

    // procura na subarvore da direita
    } else if (a->peso < v[caracter]) {
        a->dir = abb_retira(a->dir, caracter, v);

    } else { // RetornaMatAluno(a->aluno) == mat

        if (a->esq == NULL && a->dir == NULL) { // nó folha
            free(a);
            a = NULL;

        // nó só tem filho na direita
        } else if (a->esq == NULL && a->dir != NULL) {
            Arv* t = a;
            a = a->dir;
            free(t);
        
        // nó só tem filho na esquerda
        } else if (a->esq != NULL && a->dir == NULL) {
            Arv* t = a;
            a = a->esq;
            free(t);

        } else { // tem filho nas duas subárvores
            Arv* f = a->esq;
            while (f->dir != NULL) f = f->dir; // procura sucessor de a
            a->info = f->info; // troca as informações
            f->info = caracter;
            a->esq = abb_retira(a->esq, caracter, v);
        }   
    }

    return a;
}

Arv* abb_libera(Arv* a) {
    if (a != NULL) {
        abb_libera(a->esq);
        abb_libera(a->dir);
        free(a);
    }
    return NULL;
}