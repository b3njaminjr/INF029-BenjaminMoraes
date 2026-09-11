#ifndef PROFESSOR_H
#define PROFESSOR_H

#define TAM_PROFESSOR 3

typedef struct { 
    int registro;
    char sexo;
    int ativo;
} Professor;

void cadastrarProfessores(Professor listaProfessores[], int *qtdProfessores);
void listarProfessores(Professor listaProfessores[], int qtdProfessores);
void atualizarProfessores(Professor listaProfessores[], int qtdProfessores);
void excluirProfessores(Professor listaProfessores[], int *qtdProfessores);


#endif // PROFESSOR_H