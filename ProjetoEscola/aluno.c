#include <stdio.h>
#include "aluno.h" // Inclui o contrato e a struct

int menuAluno(void) {
    int opcao;
    printf("\n--- Modulo Aluno ---\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Listar Alunos\n");
    printf("3 - Atualizar Aluno\n");
    printf("4 - Excluir Aluno\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}
