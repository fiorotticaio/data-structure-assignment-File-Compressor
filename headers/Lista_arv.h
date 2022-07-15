#ifndef LISTA_H
#define LISTA_H

#include "Aluno.h"

typedef struct lista Lista;

Lista* InicializaListaVazia();

void DestroiLista(Lista* lista);

void ImprimeLista(Lista* lista);

void InsereAlunoUlt(Lista* lista, Aluno* aluno);

void InsereAlunoPrim(Lista* lista, Aluno* aluno);

Aluno* RetiraAlunoLista(Lista* lista, char* nome);

#endif // LISTA_H