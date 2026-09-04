#ifndef ALUNO_H
#define ALUNO_H

#define TAM_ALUNO 3

typedef struct { 
    int matricula;
    char sexo;
    int ativo;
} Aluno;

// Protótipos das funções
int menuAluno(void);
void moduloAluno(Aluno listaAlunos[], int *qtdAluno);
void cadastrarAluno(Aluno listaAlunos[], int *qtdAluno);
void listarAlunos(Aluno listaAlunos[], int qtdAluno);
void atualizarAluno(Aluno listaAlunos[], int qtdAluno);
void excluirAluno(Aluno listaAlunos[], int *qtdAluno);


#endif // ALUNO_H