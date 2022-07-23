#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/Arvore_bin.h"

struct arv {
    char info;
    long int peso;
    char* codigo;
    struct arv *esq;
    struct arv *dir;
};

Arv* abb_cria_vazia(void) {
    return NULL;
}

Arv* abb_cria(int ehFolha, char caracter, long int peso, Arv* e, Arv* d) {
    Arv* p = (Arv*) malloc(sizeof(Arv));
    
    // if (ehFolha) p->info = caracter;
    // else p->info = NULL;
    
    p->info = caracter;
    p->codigo = strdup("");
    p->peso = peso;
    p->esq = e;
    p->dir = d;
    return p;
}

void abb_imprime(Arv* a) {
    printf("<");
    if (a != NULL) {
        if (a->info != '-') printf("[%c - %ld - %s]", a->info, a->peso, a->codigo);
        else printf("[%ld]", a->peso);
        abb_imprime(a->esq);
        abb_imprime(a->dir);
    }
    printf(">");
}

void abb_imprime_formato_graphviz(Arv * a) {
    if (a == NULL) printf("-");
    else if (a->esq!=NULL && a->dir!=NULL) {
        printf("%ld -> ", a->peso);
        abb_imprime_formato_graphviz(a->esq);
        printf("%ld -> ", a->peso);
        abb_imprime_formato_graphviz(a->dir);
    } else if (a->info!=' ') printf("%c%ld\n", a->info, a->peso);
    else printf("esp%ld\n", a->peso);
}

//TODO: retirar futuramente?
// Arv* abb_busca(Arv* a, char caracter, long int peso) {
//     if (a == NULL) return NULL;
//     else if (getPeso(a) > peso) return abb_busca(a->esq, caracter, peso);
//     else if (getPeso(a) < peso) return abb_busca(a->dir, caracter, peso);
//     else return a;
// }

Arv* abb_insere(Arv* a, char caracter, long int peso) {
    
    // árvore vazia 
    if (a == NULL) { 
        a = (Arv*) malloc(sizeof(Arv));
        a->info = caracter;
        a->peso = peso;
        a->esq = NULL;
        a->dir = NULL;

    // inserir na esquerda
    } else if (peso < a->peso) {
        a->esq = abb_insere(a->esq, caracter, peso);

    // inserir na direita
    } else if (peso > a->peso) { 
        a->dir = abb_insere(a->dir, caracter, peso);

    } else if (caracter == a->info) { 
        printf("Caracter '%c' jah existe na arvore\n", caracter);
    }

    return a;
}

Arv* abb_retira(Arv* a, char caracter, long int peso) {
    
    //ramo acabou e não achou
    if (a == NULL) {
        return NULL;

    // procura na subarvore da esquerda
    } else if (peso < a->peso ) {
        a->esq = abb_retira(a->esq, caracter, peso);

    // procura na subarvore da direita
    } else if (peso > a->peso) {
        a->dir = abb_retira(a->dir, caracter, peso);

    } else { 

        // nó folha
        if (a->esq == NULL && a->dir == NULL) { 
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
            a->esq = abb_retira(a->esq, caracter, peso);
        }   
    }

    return a;
}

Arv* abb_libera(Arv* a) {
    if (a != NULL) {
        abb_libera(a->esq);
        abb_libera(a->dir);
        free(a->codigo);
        free(a);
    }
    return NULL;
}

void setCodigo(Arv* a, char* codigo) {
    a->codigo = realloc(a->codigo, strlen(codigo));
    strcpy(a->codigo, codigo);
}

long int getPeso(Arv * a) { return a->peso; }

char getChar(Arv * a) { return a->info; }

Arv * getRamoEsq(Arv * a) { return a->esq; }

Arv * getRamoDir(Arv * a) { return a->dir; }

int abb_vazia(Arv* a) { return a == NULL; }

static int max(int a, int b) { return a > b ? a : b; }

int abb_altura(Arv* a) {
    if (abb_vazia(a)) return -1;
    else return 1 + max(abb_altura(a->esq), abb_altura(a->dir));
}

void abb_get_codigo(Arv* a, char caractere, long int peso, char* codigo) {

    printf("getChar: %c - caractere: %c - getPeso: %ld - peso: %ld\n", getChar(a), caractere, getPeso(a), peso);

    if (a == NULL) {
        printf("null\n");
        return;

    }  else if (getChar(a) != caractere && getPeso(a) > peso) {
        printf("direita\n");
        // strcat(codigo, "0"); // esquerda -> 0
        abb_get_codigo(a->dir, caractere, peso, codigo);

    } else if (getChar(a) != caractere && getPeso(a) < peso) {
        printf("esquerda\n");
        // strcat(codigo, "1"); // direita -> 1
        abb_get_codigo(a->esq, caractere, peso, codigo);

    } else if (getPeso(a) == peso && getChar(a) == caractere) { // chegou
        printf("chegou\n");
        return;
    }
}

void add_codigo(Arv* a, char* codigo) {
    // printf("%d\n", strlen(a->codigo));
    a->codigo = (char*)realloc(a->codigo, sizeof(char)*(strlen(a->codigo) + 1));
    a->codigo = strcat(a->codigo, codigo);
}

void abb_codifica_nos(Arv* a, char* codigo) {
    if (a->esq == NULL && a->dir == NULL) { // no folha
        setCodigo(a, codigo);

    } else if (a->esq == NULL && a->dir != NULL) { // vai pra direita
        a->dir->codigo = realloc(a->dir->codigo, sizeof(char)*(strlen(a->codigo) + 1));
        codigo = realloc(codigo, sizeof(char)*(strlen(codigo) + 1));
        strcat(codigo, "1");
        abb_codifica_nos(a->dir, codigo);

    } else if (a->esq != NULL && a->dir == NULL) { // vai pra esquerda
        a->esq->codigo = realloc(a->esq->codigo, sizeof(char)*(strlen(a->codigo) + 1));
        codigo = realloc(codigo, sizeof(char)*(strlen(codigo) + 1));
        strcat(codigo, "0");
        abb_codifica_nos(a->esq, codigo);

    } else {
        char* aux = strdup(codigo);

        a->esq->codigo = realloc(a->esq->codigo, sizeof(char)*(strlen(a->codigo) + 1));
        codigo = realloc(codigo, sizeof(char)*(strlen(codigo) + 1));
        strcat(codigo, "0");
        abb_codifica_nos(a->esq, codigo);
        
        a->dir->codigo = realloc(a->dir->codigo, sizeof(char)*(strlen(a->codigo) + 1));
        codigo = realloc(codigo, sizeof(char)*(strlen(codigo) + 1));
        strcat(aux, "1");
        abb_codifica_nos(a->dir, aux);

        free(aux);
    }
}








