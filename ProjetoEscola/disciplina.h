#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "aluno.h"
#include "professor.h"

#define TAM_DISCIPLINA 20
#define MAX_ALUNOS_POR_DISCIPLINA 45

typedef struct {
    int codigo;
    char nome[50];
    int semestre;
    int matriculaProfessor; // -1 se não houver professor
    int matriculasAlunos[MAX_ALUNOS_POR_DISCIPLINA];
    int qtdAlunos;
    int ativa;
} Disciplina;

int menuDisciplina(void);
int cadastrarDisciplina(Disciplina lista[], int *qtdDisc, Professor listaProf[], int qtdProf);
void listarDisciplinas(Disciplina lista[], int qtdDisc, Professor listaProf[], int qtdProf);
void atualizarDisciplina(Disciplina lista[], int qtdDisc, Professor listaProf[], int qtdProf);
void excluirDisciplina(Disciplina lista[], int *qtdDisc);

void matricularAlunoNaDisciplina(Disciplina listaDisc[], int qtdDisc, Aluno listaAlunos[], int qtdAlunos);
void desmatricularAlunoDaDisciplina(Disciplina listaDisc[], int qtdDisc);
void listarAlunosDaDisciplina(Disciplina listaDisc[], int qtdDisc, Aluno listaAlunos[], int qtdAlunos);

#endif