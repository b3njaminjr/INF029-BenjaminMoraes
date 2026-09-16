#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#define TAM_DISCIPLINA 3
#define TAM_NOME 50

typedef struct {
    int codigo;
    char nome[TAM_NOME];
    int ativa;
    int vagas;
    int qtdAlunos;
} Disciplina;


int menuDisciplina(void);



#endif // DISCIPLINA_H