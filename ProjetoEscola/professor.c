#include <stdio.h>
#include "professor.h"

int menuProfessor(void) {
    int opcao;
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Professor\n");
    printf("2 - Listar Professores\n");
    printf("3 - Atualizar Professor\n");
    printf("4 - Excluir Professor\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void cadastrarProfessores(Professor listaProfessores[], int *qtdProfessores) {
    if (*qtdProfessores == TAM_PROFESSOR) {
        printf("Lista de professores cheia\n");
    } else {
        printf("Digite o registro:");
        int registro;
        scanf("%d", &registro);
        listaProfessores[*qtdProfessores].registro = registro;
        listaProfessores[*qtdProfessores].ativo = 1;
        (*qtdProfessores)++;
        printf("Professor cadastrado com sucesso\n");
    }

}

void listarProfessores(Professor listaProfessores[], int qtdProfessores) {
    
}
