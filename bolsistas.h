#ifndef BOLSISTAS_H
#define BOLSISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJETOS 0
#define ALUNOS 1
#define PROFESSORES 2

typedef struct Lista lista;
typedef struct Alunos alunos;
typedef struct Professores professores;
typedef struct Projetos projetos;
typedef struct Vinculos vinculos;


void* cria_novo_lista();
char* inicializa_nomes();
void* acha_ultimo(lista* minha_lista);
void* acha_na_lista(lista* minha_lista, int n, int tipo);
void* busca_e_remove_vinculo(lista* minha_lista, alunos* aluno, projetos* projeto);
alunos* parametros_alunos();
professores* parametros_professores();
projetos* parametros_projetos();
void* insere_no_final(void* parametro, lista* minha_lista);
void* insere_novo_lista(void* parametro, lista* minha_lista);
void* cria_novo_lista();
lista* exclui_vinculo(lista* lista_vinculos, lista* lista_alunos, lista* lista_projetos);
vinculos* parametros_vinculos(lista* lista_alunos, lista* lista_projetos);

#endif
