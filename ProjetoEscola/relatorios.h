#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "aluno.h"
#include "professor.h"
#include "disciplina.h"

int menuRelatorios(void);

// Relatórios de Alunos
void listarAlunosPorSexo(Aluno listaAlunos[], int qtdAluno);
void listarAlunosPorNome(Aluno listaAlunos[], int qtdAluno);
void listarAlunosPorDataNascimento(Aluno listaAlunos[], int qtdAluno);

// Relatórios de Professores
void listarProfessoresPorSexo(Professor listaProfessores[], int qtdProfessor);
void listarProfessoresPorNome(Professor listaProfessores[], int qtdProfessor);
void listarProfessoresPorDataNascimento(Professor listaProfessores[], int qtdProfessor);

// Relatórios Gerais
void listarAniversariantesDoMes(Aluno listaAlunos[], int qtdAluno, Professor listaProfessores[], int qtdProfessor);
void buscarPessoaPorTexto(Aluno listaAlunos[], int qtdAluno, Professor listaProfessores[], int qtdProfessor);
void listarAlunosMenosDeTresDisciplinas(Aluno listaAlunos[], int qtdAluno, Disciplina listaDisciplinas[], int qtdDisciplina);
void listarDisciplinasExtrapolamQuarentaVagas(Disciplina listaDisciplinas[], int qtdDisciplina, Professor listaProfessores[], int qtdProfessor);

#endif