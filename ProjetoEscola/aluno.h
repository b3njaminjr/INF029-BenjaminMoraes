#ifndef ALUNO_H
#define ALUNO_H
#define TAM_ALUNOS 50
#define TAM_NOME 50
#define TAM_CPF 15

typedef struct {  
    int dia;
    int mes;
    int ano;
} Data;



typedef struct { 
    int matricula;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char sexo;
    Data dataNascimento;
    int ativo;
} Aluno;

// Protótipos das funções
int menuAluno(void);
int cadastrarAluno(Aluno *listaAlunos, int *qtdAluno);
void listarAlunos(Aluno listaAlunos[], int qtdAluno);
int buscarAlunoPorMatricula(Aluno listaAlunos[], int *qtdAluno, int matricula);
void atualizarAluno(Aluno listaAlunos[], int qtdAluno);
void excluirAluno(Aluno listaAlunos[], int *qtdAluno);

#endif // ALUNO_H