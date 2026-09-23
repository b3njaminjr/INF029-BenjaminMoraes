#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "auxiliares.h"

#define TAM_PROFESSORES 50
#define TAM_NOME 50
#define TAM_CPF 15

typedef struct {
    int matricula;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char sexo;
    Data dataNascimento;
    int ativo;
} Professor;

int menuProfessor(void);
int cadastrarProfessor(Professor listaProfessores[], int *qtdProfessor);
void listarProfessores(Professor listaProfessores[], int qtdProfessor);
int buscarProfessorPorMatricula(Professor listaProfessores[], int qtdProfessor, int matricula);
void atualizarProfessor(Professor listaProfessores[], int qtdProfessor);
void excluirProfessor(Professor listaProfessores[], int *qtdProfessor, void *listaDisciplinas, int qtdDisciplina);

#endif