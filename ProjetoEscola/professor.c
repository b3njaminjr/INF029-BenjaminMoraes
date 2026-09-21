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

int cadastrarProfessor(Professor listaProfessores[], int *qtdProfessor) {
    if (*qtdProfessor == TAM_PROFESSORES) {
        printf("Lista de professores cheia\n");
        return 0;
    }

    Professor novoProfessor;

    printf("====== Cadastro de Professor =====\n");
    printf("Digite a matricula: ");
    scanf("%d", &novoProfessor.matricula);
    limparBuffer();

    if (buscarProfessorPorMatricula(listaProfessores, *qtdProfessor, novoProfessor.matricula) != -1) {
        printf("Matricula ja cadastrada\n");
        return 0;
    }

    printf("Digite o nome: \n");
    lerTexto(novoProfessor.nome, TAM_NOME);
    formatarNome(novoProfessor.nome);

    printf("Digite o sexo (M/F): \n");
    novoProfessor.sexo = validarSexo();

    do {
        printf("Digite a data de nascimento (DD/MM/AAAA): \n");
        scanf("%d/%d/%d",  &novoProfessor.dataNascimento.dia, 
                           &novoProfessor.dataNascimento.mes, 
                           &novoProfessor.dataNascimento.ano);
        limparBuffer();        
        if (!validarData(novoProfessor.dataNascimento)) {
            printf("Data invalida! Tente novamente\n");
        }
    } while (!validarData(novoProfessor.dataNascimento));

    do {
        printf("Digite o CPF (somente numeros): \n");
        lerTexto(novoProfessor.cpf, TAM_CPF); // Ajustado para TAM_CPF
        if (!validarCpf(novoProfessor.cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (!validarCpf(novoProfessor.cpf));

    novoProfessor.ativo = 1; 
    listaProfessores[*qtdProfessor] = novoProfessor;
    (*qtdProfessor)++;
    printf("Professor cadastrado com sucesso\n");
    return 1;
}

void listarProfessores(Professor listaProfessores[], int qtdProfessor) {
    int cadastrados = 0;
    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].ativo == 1) {
            printf("Matricula: %d | Nome: %s | Sexo: %c | Data de Nascimento: %02d/%02d/%d | CPF: %s\n",
                   listaProfessores[i].matricula, 
                   listaProfessores[i].nome, 
                   listaProfessores[i].sexo,
                   listaProfessores[i].dataNascimento.dia, 
                   listaProfessores[i].dataNascimento.mes, 
                   listaProfessores[i].dataNascimento.ano,
                   listaProfessores[i].cpf);
            cadastrados++;
        }
    }

    if (cadastrados == 0) {
        printf("Lista de professores esta vazia\n");
    }
}

int buscarProfessorPorMatricula(Professor listaProfessores[], int qtdProfessor, int matricula) {
    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].matricula == matricula && listaProfessores[i].ativo == 1) 
            return i;
    }
    return -1;
}

void atualizarProfessor(Professor listaProfessores[], int qtdProfessor) {
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    limparBuffer();

    int indiceMatricula = buscarProfessorPorMatricula(listaProfessores, qtdProfessor, matricula);

    if (indiceMatricula == -1) {
        printf("Professor nao encontrado\n");
        return;
    }

    printf("Digite o novo nome: \n");
    lerTexto(listaProfessores[indiceMatricula].nome, TAM_NOME);
    formatarNome(listaProfessores[indiceMatricula].nome);

    listaProfessores[indiceMatricula].sexo = validarSexo();

    do {
        printf("Digite a nova data de nascimento (DD/MM/AAAA): \n");
        scanf("%d/%d/%d", &listaProfessores[indiceMatricula].dataNascimento.dia, 
                           &listaProfessores[indiceMatricula].dataNascimento.mes, 
                           &listaProfessores[indiceMatricula].dataNascimento.ano);
        limparBuffer();
        if (!validarData(listaProfessores[indiceMatricula].dataNascimento))
            printf("Data invalida! Tente novamente\n");

    } while (!validarData(listaProfessores[indiceMatricula].dataNascimento));

    do {
        printf("Digite o CPF (somente numeros): \n");
        lerTexto(listaProfessores[indiceMatricula].cpf, TAM_CPF);
        if (!validarCpf(listaProfessores[indiceMatricula].cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (!validarCpf(listaProfessores[indiceMatricula].cpf));

    printf("Professor atualizado com sucesso!\n");
}

void excluirProfessor(Professor listaProfessores[], int *qtdProfessor) {
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    limparBuffer();

    int indiceMatricula = buscarProfessorPorMatricula(listaProfessores, *qtdProfessor, matricula);

    if (indiceMatricula == -1) {
        printf("Professor nao encontrado\n");
        return;
    }

    int i = indiceMatricula;
    while (i < *qtdProfessor - 1) {
        listaProfessores[i] = listaProfessores[i + 1];
        i++;
    }
    (*qtdProfessor)--;
    printf("Professor excluido com sucesso!\n");
}