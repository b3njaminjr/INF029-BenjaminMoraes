#include <stdio.h>
#include "professor.h"
#include "auxiliares.h" // Garante acesso às funções auxiliares

// 1. Menu com leitura segura de inteiro
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
        return -1; // Retorna opcao invalida caso o usuario digite texto
    }
    return opcao;
}

// 2. Cadastro de Professor
int cadastrarProfessor(Professor listaProfessores[], int *qtdProfessor) {
    if (*qtdProfessor == TAM_PROFESSORES) {
        printf("Lista de professores cheia\n");
        return 0;
    }

    Professor novoProfessor;

    printf("\n====== Cadastro de Professor =====\n");
    printf("Digite a matricula: ");
    if (!lerInt(&novoProfessor.matricula)) {
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

    // validarSexo() cuida do loop e leitura do caractere
    novoProfessor.sexo = validarSexo();

    // Validação de Data sem repetição de função
    int dataValida = 0;
    do {
        printf("Digite a data de nascimento (DD/MM/AAAA): ");
        if (scanf("%d/%d/%d", &novoProfessor.dataNascimento.dia, 
                             &novoProfessor.dataNascimento.mes, 
                             &novoProfessor.dataNascimento.ano) == 3) {
            limparBuffer();
            dataValida = validarData(novoProfessor.dataNascimento);
        } else {
            limparBuffer(); // Limpa se o usuario digitar caracteres invalidos
            dataValida = 0;
        }

        if (!dataValida) {
            printf("Data invalida! Tente novamente.\n");
        }
    } while (!dataValida);

    // Validação de CPF
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

// 3. Listagem de Professores
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
        printf("Lista de professores esta vazia.\n");
    }
}

// 4. Busca por Matrícula
int buscarProfessorPorMatricula(Professor listaProfessores[], int qtdProfessor, int matricula) {
    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].matricula == matricula && listaProfessores[i].ativo == 1) {
            return i;
        }
    }
    return -1;
}

// 5. Atualização de Professor
void atualizarProfessor(Professor listaProfessores[], int qtdProfessor) {
    printf("Digite a matricula do professor a atualizar: ");
    int matricula;
    if (!lerInt(&matricula)) {
        printf("Matricula invalida!\n");
        return;
    }

    int indice = buscarProfessorPorMatricula(listaProfessores, qtdProfessor, matricula);

    if (indice == -1) {
        printf("Professor nao encontrado.\n");
        return;
    }

    printf("Digite o novo nome: ");
    lerTexto(listaProfessores[indice].nome, TAM_NOME);
    formatarNome(listaProfessores[indice].nome);

    listaProfessores[indice].sexo = validarSexo();

    int dataValida = 0;
    do {
        printf("Digite a nova data de nascimento (DD/MM/AAAA): ");
        if (scanf("%d/%d/%d", &listaProfessores[indice].dataNascimento.dia, 
                             &listaProfessores[indice].dataNascimento.mes, 
                             &listaProfessores[indice].dataNascimento.ano) == 3) {
            limparBuffer();
            dataValida = validarData(listaProfessores[indice].dataNascimento);
        } else {
            limparBuffer();
            dataValida = 0;
        }

        if (!dataValida) {
            printf("Data invalida! Tente novamente.\n");
        }
    } while (!dataValida);

    do {
        printf("Digite o novo CPF (11 numeros): ");
        lerTexto(listaProfessores[indice].cpf, TAM_CPF);
        if (!validarCpf(listaProfessores[indice].cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (!validarCpf(listaProfessores[indice].cpf));

    printf("Professor atualizado com sucesso!\n");
}

// 6. Exclusão de Professor (Remoção física deslocando elementos)
void excluirProfessor(Professor listaProfessores[], int *qtdProfessor) {
    printf("Digite a matricula do professor a excluir: ");
    int matricula;
    if (!lerInt(&matricula)) {
        printf("Matricula invalida!\n");
        return;
    }

    int indice = buscarProfessorPorMatricula(listaProfessores, *qtdProfessor, matricula);

    if (indice == -1) {
        printf("Professor nao encontrado.\n");
        return;
    }

    // Desloca os elementos para cobrir a posição removida
    for (int i = indice; i < *qtdProfessor - 1; i++) {
        listaProfessores[i] = listaProfessores[i + 1];
    }

    (*qtdProfessor)--;
    printf("Professor excluido com sucesso!\n");
}