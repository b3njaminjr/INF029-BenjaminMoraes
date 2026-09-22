#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "aluno.h"
#include "professor.h"
#include "disciplina.h"

int menuRelatorios(void);
void listarAlunosPorSexo(Aluno listaAlunos[], int qtdAluno);
void listarAlunosPorNome(Aluno listaAlunos[], int qtdAluno);
void listarAniversariantesDoMes(Aluno listaAlunos[], int qtdAluno);
void buscarAlunoPorTexto(Aluno listaAlunos[], int qtdAluno);

#endif