#include <stdio.h>
#include "aluno.h"
#include "auxiliares.h"

int menuAluno(void) {
    int opcao;
    printf("\n--- Menu Aluno ---\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Listar Alunos\n");
    printf("3 - Atualizar Aluno\n");
    printf("4 - Excluir Aluno\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
    return opcao;
}

int cadastrarAluno(Aluno listaAlunos[], int *qtdAluno) {
    if (*qtdAluno == TAM_ALUNOS) {
        printf("Lista de alunos cheia\n");
        return 0;
    }

    Aluno novoAluno;
    printf("\n====== Cadastro de Aluno =====\n");
    printf("Digite a matricula: ");
    scanf("%d", &novoAluno.matricula);
    limparBuffer();

    if (buscarAlunoPorMatricula(listaAlunos, *qtdAluno, novoAluno.matricula) != -1) {
        printf("Matricula ja cadastrada\n");
        return 0;
    }

    printf("Digite o nome: ");
    lerTexto(novoAluno.nome, TAM_NOME);
    formatarNome(novoAluno.nome);

    printf("Digite o sexo (M/F): ");
    novoAluno.sexo = validarSexo();

    do {
        printf("Digite a data de nascimento (DD/MM/AAAA): ");
        scanf("%d/%d/%d", &novoAluno.dataNascimento.dia, 
                           &novoAluno.dataNascimento.mes, 
                           &novoAluno.dataNascimento.ano);
        limparBuffer();        
        if (!validarData(novoAluno.dataNascimento)) {
            printf("Data invalida! Tente novamente.\n");
        }
    } while (!validarData(novoAluno.dataNascimento));

    do {
        printf("Digite o CPF (somente numeros): ");
        lerTexto(novoAluno.cpf, TAM_CPF); // Corrigido para TAM_CPF
        if (!validarCpf(novoAluno.cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (!validarCpf(novoAluno.cpf));

    novoAluno.ativo = 1; 
    listaAlunos[*qtdAluno] = novoAluno;
    (*qtdAluno)++;
    printf("Aluno cadastrado com sucesso!\n");
    return 1;
}

void listarAlunos(Aluno listaAlunos[], int qtdAluno) {
    int cadastrados = 0;
    printf("\n====== Lista de Alunos ======\n");
    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].ativo == 1) {
            printf("Matricula: %d | Nome: %s | Sexo: %c | Data Nasc: %02d/%02d/%d | CPF: %s\n",
                   listaAlunos[i].matricula, 
                   listaAlunos[i].nome, 
                   listaAlunos[i].sexo,
                   listaAlunos[i].dataNascimento.dia, 
                   listaAlunos[i].dataNascimento.mes, 
                   listaAlunos[i].dataNascimento.ano,
                   listaAlunos[i].cpf);
            cadastrados++;
        }
    }

    if (cadastrados == 0) {
        printf("Lista de alunos esta vazia.\n");
    }
}

int buscarAlunoPorMatricula(Aluno listaAlunos[], int qtdAluno, int matricula) {
    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].matricula == matricula && listaAlunos[i].ativo == 1) 
            return i;
    }
    return -1;
}

void atualizarAluno(Aluno listaAlunos[], int qtdAluno) {
    printf("\nDigite a matricula do aluno a ser atualizado: ");
    int matricula;
    scanf("%d", &matricula);
    limparBuffer();

    int indiceMatricula = buscarAlunoPorMatricula(listaAlunos, qtdAluno, matricula);

    if (indiceMatricula == -1) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    printf("Digite o novo nome: ");
    lerTexto(listaAlunos[indiceMatricula].nome, TAM_NOME);
    formatarNome(listaAlunos[indiceMatricula].nome);

    printf("Digite o novo sexo (M/F): ");
    listaAlunos[indiceMatricula].sexo = validarSexo();

    do {
        printf("Digite a nova data de nascimento (DD/MM/AAAA): ");
        scanf("%d/%d/%d", &listaAlunos[indiceMatricula].dataNascimento.dia, 
                           &listaAlunos[indiceMatricula].dataNascimento.mes, 
                           &listaAlunos[indiceMatricula].dataNascimento.ano);
        limparBuffer();
        if (!validarData(listaAlunos[indiceMatricula].dataNascimento))
            printf("Data invalida! Tente novamente.\n");

    } while (!validarData(listaAlunos[indiceMatricula].dataNascimento));

    do {
        printf("Digite o novo CPF (somente numeros): ");
        lerTexto(listaAlunos[indiceMatricula].cpf, TAM_CPF); // Corrigido para TAM_CPF
        if (!validarCpf(listaAlunos[indiceMatricula].cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (!validarCpf(listaAlunos[indiceMatricula].cpf));

    printf("Aluno atualizado com sucesso!\n");
}

void excluirAluno(Aluno listaAlunos[], int *qtdAluno) {
    printf("\nDigite a matricula do aluno a ser excluido: ");
    int matricula;
    scanf("%d", &matricula);
    limparBuffer();

    int indiceMatricula = buscarAlunoPorMatricula(listaAlunos, *qtdAluno, matricula);

    if (indiceMatricula == -1) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    for (int i = indiceMatricula; i < *qtdAluno - 1; i++) {
        listaAlunos[i] = listaAlunos[i + 1];
    }
    (*qtdAluno)--;
    printf("Aluno excluido com sucesso!\n");
}