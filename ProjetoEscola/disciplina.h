#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "aluno.h"
#include "professor.h"

#define QTD_MAX_DISCIPLINA 20
#define MAX_NOME 50
#define TAM_SEMESTRE 10
#define MAX_ALUNOS_POR_DISCIPLINA 60

typedef struct Disciplina {
    int codigo;
    char nome[MAX_NOME];
    char semestre[TAM_SEMESTRE];
    int matriculaProfessor;
    int vagas;
    int qtdAlunosMatriculados;
    int alunosMatriculados[MAX_ALUNOS_POR_DISCIPLINA];
    int ativa;
} Disciplina;

int menuDisciplina(void);
int cadastrarDisciplina(Disciplina listaDisciplinas[], int *qtdDisciplina, Professor listaProfessores[], int qtdProfessores);
int buscarDisciplinaPorCodigo(Disciplina listaDisciplinas[], int qtdDisciplina, int codigo);
int formatarNomeDisciplina(char texto[]);
void listarDisciplinas(Disciplina listaDisciplinas[], int qtdDisciplina, Professor listaProfessores[], int qtdProfessores);
void atualizarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplina, Professor listaProfessores[], int qtdProfessores);
void excluirDisciplina(Disciplina listaDisciplinas[], int *qtdDisciplina);

int matricularAlunoNaDisciplina(Disciplina listaDisciplinas[], int qtdDisciplina, Aluno listaAlunos[], int qtdAluno);
int desmatricularAlunoDaDisciplina(Disciplina listaDisciplinas[], int qtdDisciplina, Aluno listaAlunos[], int qtdAluno);
void relatorioAlunosPorDisciplina(Disciplina listaDisciplinas[], int qtdDisciplina, Aluno listaAlunos[], int qtdAluno);
void relatorioVagasDisciplinas(Disciplina listaDisciplinas[], int qtdDisciplina);

#endif