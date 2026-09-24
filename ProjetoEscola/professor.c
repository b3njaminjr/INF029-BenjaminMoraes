#include <stdio.h>
#include "professor.h"
#include "disciplina.h"
#include "auxiliares.h"

int menuProfessor(void) {
    int opcao;
    printf("\n--- MENU PROFESSOR ---\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Professor\n");
    printf("2 - Listar Professores\n");
    printf("3 - Atualizar Professor\n");
    printf("4 - Excluir Professor\n");
    printf("Escolha uma opcao: ");

    if (!lerInt(&opcao)) {
        return -1;
    }
    return opcao;
}

int buscarProfessorPorMatricula(Professor listaProfessores[], int qtdProfessor, int matricula) {
    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].matricula == matricula && listaProfessores[i].ativo == 1) {
            return i;
        }
    }
    return -1;
}

int cadastrarProfessor(Professor listaProfessores[], int *qtdProfessor) {
    if (*qtdProfessor >= TAM_PROFESSORES) {
        printf("Lista de professores cheia!\n");
        return 0;
    }

    Professor novoProfessor = {0};

    printf("\n====== Cadastro de Professor ======\n");
    printf("Digite a matricula: ");
    if (!lerInt(&novoProfessor.matricula) || novoProfessor.matricula <= 0) {
        printf("Matricula invalida!\n");
        return 0;
    }

    if (buscarProfessorPorMatricula(listaProfessores, *qtdProfessor, novoProfessor.matricula) != -1) {
        printf("Matricula ja cadastrada!\n");
        return 0;
    }

    printf("Digite o nome: ");
    lerTexto(novoProfessor.nome, TAM_NOME);
    formatarNome(novoProfessor.nome);

    printf("Digite o sexo (M/F): ");
    novoProfessor.sexo = validarSexo();

    do {
        printf("Digite a data de nascimento (DD/MM/AAAA): ");
        if (!lerData(&novoProfessor.dataNascimento) || !validarData(novoProfessor.dataNascimento)) {
            printf("Data invalida! Tente novamente.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Digite o CPF (11 numeros): ");
        lerTexto(novoProfessor.cpf, TAM_CPF);
        if (!validarCpf(novoProfessor.cpf)) {
            printf("CPF invalido! Digite exatamente 11 numeros.\n");
        }
    } while (!validarCpf(novoProfessor.cpf));

    novoProfessor.ativo = 1;
    listaProfessores[*qtdProfessor] = novoProfessor;
    (*qtdProfessor)++;

    printf("Professor cadastrado com sucesso!\n");
    return 1;
}

void listarProfessores(Professor listaProfessores[], int qtdProfessor) {
    int cadastrados = 0;
    printf("\n--- LISTA DE PROFESSORES ---\n");

    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].ativo == 1) {
            printf("Matricula: %d | Nome: %-20s | Sexo: %c | Data Nasc: %02d/%02d/%04d | CPF: %s\n",
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
        printf("Lista de professores esta vazia ou nenhum ativo.\n");
    }
}

void atualizarProfessor(Professor listaProfessores[], int qtdProfessor) {
    printf("Digite a matricula do professor a atualizar: ");
    int matricula;
    if (!lerInt(&matricula)) {
        printf("Matricula invalida!\n");
        return;
    }

    int indice = buscarProfessorPorMatricula(listaProfessores, qtdProfessor, matricula);

    if (indice == -1) {
        printf("Professor nao encontrado ou inativo.\n");
        return;
    }

    printf("Digite o novo nome: ");
    lerTexto(listaProfessores[indice].nome, TAM_NOME);
    formatarNome(listaProfessores[indice].nome);

    printf("Digite o novo sexo (M/F): ");
    listaProfessores[indice].sexo = validarSexo();

    do {
        printf("Digite a nova data de nascimento (DD/MM/AAAA): ");
        if (!lerData(&listaProfessores[indice].dataNascimento) || !validarData(listaProfessores[indice].dataNascimento)) {
            printf("Data invalida! Tente novamente.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Digite o novo CPF (11 numeros): ");
        lerTexto(listaProfessores[indice].cpf, TAM_CPF);
        if (!validarCpf(listaProfessores[indice].cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (!validarCpf(listaProfessores[indice].cpf));

    printf("Professor atualizado com sucesso!\n");
}

void excluirProfessor(Professor listaProfessores[], int *qtdProfessor, void *listaDisciplinasPtr, int qtdDisciplina) {
    Disciplina *listaDisciplinas = (Disciplina*) listaDisciplinasPtr;

    printf("Digite a matricula do professor a excluir: ");
    int matricula;
    if (!lerInt(&matricula)) {
        printf("Matricula invalida!\n");
        return;
    }

    int indice = buscarProfessorPorMatricula(listaProfessores, *qtdProfessor, matricula);

    if (indice == -1) {
        printf("Professor nao encontrado ou ja inativo.\n");
        return;
    }

    for (int i = 0; i < qtdDisciplina; i++) {
        if (listaDisciplinas[i].ativa && listaDisciplinas[i].matriculaProfessor == matricula) {
            printf("Erro: O professor nao pode ser excluido pois e o responsavel pela disciplina '%s'!\n",
                   listaDisciplinas[i].nome);
            printf("Altere o professor da disciplina antes de realizar a exclusao.\n");
            return;
        }
    }

    listaProfessores[indice].ativo = 0;
    printf("Professor excluido com sucesso (desativado)!\n");
}