#include <stdio.h>
#include "aluno.h" // Inclui o contrato e a struct

int menuAluno(void) {
    int opcao;
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Listar Alunos\n");
    printf("3 - Atualizar Aluno\n");
    printf("4 - Excluir Aluno\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void cadastrarAluno(Aluno listaAlunos[], int *qtdAluno) {
    if (*qtdAluno == TAM_ALUNO) {
        printf("Lista de alunos cheia\n");
    } else {
        printf("Digite a matricula: ");
        int matricula;
        scanf("%d", &matricula);

        if (matricula < 0) {
            printf("Matricula invalida\n");
        } else {
            listaAlunos[*qtdAluno].matricula = matricula;
            listaAlunos[*qtdAluno].ativo = 1;
            (*qtdAluno)++;
            printf("Aluno cadastrado com sucesso\n");
        }
    }
}

void listarAlunos(Aluno listaAlunos[], int qtdAluno) {
    if (qtdAluno == 0) {
        printf("Lista aluno vazia\n");
    } else {
        for (int i = 0; i < qtdAluno; i++) {
            if (listaAlunos[i].ativo == 1) {
                printf("Aluno %d: %d\n", i + 1, listaAlunos[i].matricula);
            }
        }
    }
}

void atualizarAluno(Aluno listaAlunos[], int qtdAluno) {
    printf("Digite a matricula: ");
    int matricula;
    scanf("%d", &matricula);
    int achou = 0;

    if (matricula < 0) {
        printf("Matricula invalida\n");
    } else {
        for (int i = 0; i < qtdAluno; i++) {
            if (matricula == listaAlunos[i].matricula) {
                printf("Digite o novo sexo (M/F): ");
                char sexo;
                scanf(" %c", &sexo);
                listaAlunos[i].sexo = sexo;
                achou = 1;
                break;
            }
        }
        if (achou) {
            printf("Aluno atualizado com sucesso\n");
        } else {
            printf("Matricula inexistente\n");
        }
    }
}

void excluirAluno(Aluno listaAlunos[], int *qtdAluno) {
    printf("Digite a matricula: ");
    int matricula;
    scanf("%d", &matricula);
    int achou = 0;

    if (matricula < 0) {
        printf("Matricula invalida\n");
    } else {
        for (int i = 0; i < *qtdAluno; i++) {
            if (matricula == listaAlunos[i].matricula && listaAlunos[i].ativo == 1) {
                listaAlunos[i].ativo = 0; // Marca como inativo
                achou = 1;
                break;
            }
        }
        if (achou) {
            printf("Aluno excluido com sucesso\n");
        } else {
            printf("Matricula inexistente\n");
        }
    }
}
