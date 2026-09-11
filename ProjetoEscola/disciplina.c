#include <stdio.h>
#include "disciplina.h"

int menuDisciplina(void) {
    int opcao;
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Disciplina\n");
    printf("2 - Listar Disciplinas\n");
    printf("3 - Atualizar Disciplina\n");
    printf("4 - Excluir Disciplina\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}