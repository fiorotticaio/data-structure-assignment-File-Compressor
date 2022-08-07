#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../headers/Arvore_bin.h"

struct arv {
    unsigned char info;
    long int peso;
    unsigned char* codigo;
    struct arv *esq;
    struct arv *dir;
};

Arv* abb_cria_vazia(void) {
    return NULL;
}

Arv* abb_cria(unsigned char caracter, long int peso, Arv* e, Arv* d) {
    Arv* p = (Arv*) malloc(sizeof(Arv));
    
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
        if (a->info != '-') printf("[%d - %ld - %s]", a->info, a->peso, a->codigo);
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
    } else {
        printf("char%d_%ld\n", a->info,a->peso);
    }
}

void preenche_bitmap(Arv* a, unsigned char caractere, bitmap* bm) {
    int i = 0;

    if (a == NULL) return;
    else if (getChar(a) == caractere) {
        while(a->codigo[i]) {
            bitmapAppendLeastSignificantBit(bm, a->codigo[i]);
            // print 1
            // print a->codido
            i++;
        }

    } else {
        preenche_bitmap(a->esq, caractere, bm);
        // print 0
        preenche_bitmap(a->dir, caractere, bm);
        // print 0
    }

}

Arv* abb_insere(Arv* a, unsigned char caracter, long int peso) {
    
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
        printf("Caracter '%c' já existe na arvore\n", caracter);
    }

    return a;
}

void abb_preenche_codigos(Arv* a, unsigned char * codigo, int indice, char letra){
    //caso seja o ultimo bit do codigo
    if (indice == strlen(codigo)) {
        a->info=letra;

    //caso seja o bit 1 (criar um ramo na direita)
    } else if (codigo[indice]=='1') {
        if (a->dir==NULL) a->dir = abb_cria('-', indice+((int)letra), abb_cria_vazia(), abb_cria_vazia());
        abb_preenche_codigos(a->dir, codigo, indice+1, letra);
    
    //caso seja o bit 0 (criar um ramo na esquerda)
    } else if (codigo[indice]=='0'){
        if (a->esq==NULL) a->esq = abb_cria('-', indice+((int)letra), abb_cria_vazia(), abb_cria_vazia());
        abb_preenche_codigos(a->esq, codigo, indice+1, letra);
    }

}

Arv* abb_retira(Arv* a, unsigned char caracter, long int peso) {
    
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

void setCodigo(Arv* a, unsigned char* codigo) {
    a->codigo = realloc(a->codigo, strlen(codigo));
    strcpy(a->codigo, codigo);
}

long int getPeso(Arv * a) { return a->peso; }

unsigned char getChar(Arv * a) { return a->info; }

Arv * getRamoEsq(Arv * a) { return a->esq; }

Arv * getRamoDir(Arv * a) { return a->dir; }

int abb_vazia(Arv* a) { return a == NULL; }

static int max(int a, int b) { return a > b ? a : b; }

int abb_altura(Arv* a) {
    if (abb_vazia(a)) return -1;
    else return 1 + max(abb_altura(a->esq), abb_altura(a->dir));
}

void abb_codifica_nos(Arv* a, unsigned char* codigo) {
    if (a->esq == NULL && a->dir == NULL) { // no folha
        setCodigo(a, codigo);

    } else if (a->esq == NULL && a->dir != NULL) { // vai pra direita
        a->dir->codigo = realloc(a->dir->codigo, sizeof(unsigned char)*(strlen(a->codigo) + 1));
        codigo = realloc(codigo, sizeof(unsigned char)*(strlen(codigo) + 1));
        strcat(codigo, "1");
        abb_codifica_nos(a->dir, codigo);

    } else if (a->esq != NULL && a->dir == NULL) { // vai pra esquerda
        a->esq->codigo = realloc(a->esq->codigo, sizeof(unsigned char)*(strlen(a->codigo) + 1));
        codigo = realloc(codigo, sizeof(unsigned char)*(strlen(codigo) + 1));
        strcat(codigo, "0");
        abb_codifica_nos(a->esq, codigo);

    } else {
        unsigned char* aux = strdup(codigo);

        a->esq->codigo = realloc(a->esq->codigo, sizeof(unsigned char)*(strlen(a->codigo) + 1));
        codigo = realloc(codigo, sizeof(unsigned char)*(strlen(codigo) + 1));
        strcat(codigo, "0");
        abb_codifica_nos(a->esq, codigo);

        a->dir->codigo = realloc(a->dir->codigo, sizeof(unsigned char)*(strlen(a->codigo) + 1));
        codigo = realloc(codigo, sizeof(unsigned char)*(strlen(codigo) + 1));
        strcat(aux, "1");
        abb_codifica_nos(a->dir, aux);

        free(aux);
    }
}

unsigned char** alocaTabela(int colunas) {
    /* tabela: vetor de strings */
    unsigned char** tabela = (unsigned char**) malloc(sizeof(unsigned char*)*256);
    for (int i = 0; i < 256; i++) {
        tabela[i] = (unsigned char*) calloc(colunas, sizeof(unsigned char));
        // calloc: ao mesmo tempo que aloca espaço também inicializa
    }
    return tabela;
}

void geraTabCode(unsigned char** tabela, Arv* a, char* caminho, int colunas) {
    char esq[colunas], dir[colunas];

    // verficando se é nó folha
    if (a->esq == NULL && a->dir == NULL) {
        strcpy(tabela[a->info], caminho);

    // gerando caminhos para subárvores
    } else {
        strcpy(esq, caminho);
        strcpy(dir, caminho);
        strcat(esq, "0");
        strcat(dir, "1");
        geraTabCode(tabela, a->esq, esq, colunas);
        geraTabCode(tabela, a->dir, dir, colunas);
    }
}

void imprimeTabCode(unsigned char** tabela) {
    int i = 0;
    for (i = 0; i < 256; i++) {
        if (strlen(tabela[i]) > 0) printf("%d - %c: %s\n", i, i, tabela[i]); // imprimir os que não são zero
    }
}

void liberaTabCode(unsigned char** tabela) {
    for (int i = 0; i < 256; i++) {
        free(tabela[i]);
    }
    free(tabela);
}

void codifica(unsigned char** tabela, bitmap* bm, unsigned char caractere) {
    int i = 0;
    while(tabela[caractere][i] != '\0') {
        if (tabela[caractere][i] == '0') {
            // printf("inserindo 0 da posicao %d de [%s]\n", i, tabela[caractere]);
            bitmapAppendLeastSignificantBit(bm, 0);
        } else {
            bitmapAppendLeastSignificantBit(bm, 1);
            // printf("inserindo 1 da posicao %d de [%s]\n", i, tabela[caractere]);
        }
        i++;
    }
    
}

void decodifica(Arv * a, bitmap* bm, FILE * saida) {
    int k;
    Arv* aux=a;

    //passando por cada bit no bitmap
    for (k=0;k<bitmapGetLength(bm)-1;k++) {
        
        //caso o bit seja 1, ramo da direita da arvore
        if ((int)bitmapGetBit(bm, k)) aux = getRamoDir(aux);
        
        //caso o bit seja 0, ramo da esquerda da arvore
        else aux = getRamoEsq(aux);
        
        //caso o nó seja um nó folha
        if (abb_vazia(getRamoDir(aux)) && abb_vazia(getRamoEsq(aux))){
            fprintf(saida, "%c", getChar(aux));
            aux = a;
        }        
    }


    //TODO: retirar
    // int k;
    // printf("\n(decodifica) imprimindo bitmap\n");
    // for(k=0;k<bitmapGetLength(bm);k++) {
    //     printf("%d", bitmapGetBit(bm, k));
    // }

}

char * decimal_para_binario(int num) {   
    char bin_invertido[9]; 

    char * bin = malloc(sizeof(char) * 9);
    int i=0, j, k=0;
    for(k=0;k<9; k++) bin_invertido[k] = '0';
    
    for ( ;num > 0; ){
        if (num%2) bin_invertido[i++] = '1';
        else bin_invertido[i++] = '0';
        num /= 2;
    }
    
    k=0;
    for (j = 7; j >= 0; j--){
        bin[k] = bin_invertido[j];
        k++;
    }
    bin[k]='\0';

    return bin;
}

void abb_serializa(Arv * a, bitmap * bm){
    int i;

    //nó folha, faz append do bit 1, e em seguida faz o append do codigo decimal ascii do char (em binario)
    if (a->dir==NULL && a->esq==NULL){
        bitmapAppendLeastSignificantBit(bm, 1);
        char * binario = decimal_para_binario((int)a->info);
        
        for(i=0;i<8;i++) {
            if (binario[i] == '1') bitmapAppendLeastSignificantBit(bm, 1);
            else if (binario[i] == '0') bitmapAppendLeastSignificantBit(bm, 0);
        }

        free(binario);
    } else {
        bitmapAppendLeastSignificantBit(bm, 0);
        abb_serializa(a->esq,bm);
        abb_serializa(a->dir,bm);
    }
}

int abb_desserializa(Arv *a, char * serielizacao, int indice){
    if(serielizacao[indice]=='0'){
        Arv * esq = abb_cria('-', 0, abb_cria_vazia(), abb_cria_vazia());
        a->esq = esq;

        Arv * dir = abb_cria('-', 0, abb_cria_vazia(), abb_cria_vazia());
        a->dir = dir;

        indice = abb_desserializa(a->esq, serielizacao, indice+1);
        indice = abb_desserializa(a->dir, serielizacao, indice+1);
    } else {
        indice+=1;
        int i, k=0, num=0;
        char * bin = malloc(sizeof(char) * 8) ;
        for(i=0;i<8; i++) bin[i]=serielizacao[indice++];
        for(i=7;i>=0;i--){
            if (bin[k]=='1') {
                num+=pow(2,i);
            }
            k++;
        }
        free(bin);
        a->info=(char)num;
        return indice-1;
    }
}










