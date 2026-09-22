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

    if (!lerInt(&opcao)) {
        return -1; // Retorna opção inválida caso digite letras
    }
    return opcao;
}

int buscarAlunoPorMatricula(Aluno listaAlunos[], int qtdAluno, int matricula) {
    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].matricula == matricula && listaAlunos[i].ativo == 1) {
            return i;
        }
    }
    return -1;
}

int cadastrarAluno(Aluno listaAlunos[], int *qtdAluno) {
    if (*qtdAluno >= TAM_ALUNOS) {
        printf("Lista de alunos cheia!\n");
        return 0;
    }

    Aluno novoAluno = {0};
    printf("\n====== Cadastro de Aluno ======\n");

    // 1. Matrícula com validação de inteiros e duplicidade
    int matriculaValida = 0;
    do {
        printf("Digite a matricula: ");
        if (!lerInt(&novoAluno.matricula)) {
            printf("Apenas numeros sao permitidos para a matricula. Tente novamente.\n");
        } else if (novoAluno.matricula <= 0) {
            printf("A matricula deve ser um numero positivo. Tente novamente.\n");
        } else if (buscarAlunoPorMatricula(listaAlunos, *qtdAluno, novoAluno.matricula) != -1) {
            printf("Erro: Matricula ja cadastrada no sistema!\n");
            return 0; // Cancela cadastro duplicado
        } else {
            matriculaValida = 1;
        }
    } while (!matriculaValida);

    // 2. Nome
    printf("Digite o nome: ");
    lerTexto(novoAluno.nome, TAM_NOME);
    formatarNome(novoAluno.nome);

    // 3. Sexo
    printf("Digite o sexo (M/F): ");
    novoAluno.sexo = validarSexo();

    // 4. Data de Nascimento
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

    // 5. CPF
    do {
        printf("Digite o CPF (somente numeros): ");
        lerTexto(novoAluno.cpf, TAM_CPF);
        if (!validarCpf(novoAluno.cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (!validarCpf(novoAluno.cpf));

    novoAluno.ativo = 1; 
    listaAlunos[*qtdAluno] = novoAluno;
    (*qtdAluno)++;
    
    printf("\n>>> Aluno cadastrado com sucesso! <<<\n");
    return 1;
}

void listarAlunos(Aluno listaAlunos[], int qtdAluno) {
    int cadastrados = 0;
    printf("\n====== Lista de Alunos ======\n");
    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].ativo == 1) {
            printf("Matricula: %d | Nome: %-20s | Sexo: %c | Data Nasc: %02d/%02d/%d | CPF: %s\n",
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

void atualizarAluno(Aluno listaAlunos[], int qtdAluno) {
    printf("\n====== Atualizar Aluno ======\n");
    printf("Digite a matricula do aluno a ser atualizado: ");
    int matricula;
    
    if (!lerInt(&matricula)) {
        printf("Matricula invalida.\n");
        return;
    }

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
        scanf("%d/%d/%d",  &listaAlunos[indiceMatricula].dataNascimento.dia, 
                           &listaAlunos[indiceMatricula].dataNascimento.mes, 
                           &listaAlunos[indiceMatricula].dataNascimento.ano);
        limparBuffer();
        if (!validarData(listaAlunos[indiceMatricula].dataNascimento)) {
            printf("Data invalida! Tente novamente.\n");
        }
    } while (!validarData(listaAlunos[indiceMatricula].dataNascimento));

    do {
        printf("Digite o novo CPF (somente numeros): ");
        lerTexto(listaAlunos[indiceMatricula].cpf, TAM_CPF);
        if (!validarCpf(listaAlunos[indiceMatricula].cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (!validarCpf(listaAlunos[indiceMatricula].cpf));

    printf("\n>>> Aluno atualizado com sucesso! <<<\n");
}

void excluirAluno(Aluno listaAlunos[], int *qtdAluno) {
    printf("\n====== Excluir Aluno ======\n");
    printf("Digite a matricula do aluno a ser excluido: ");
    int matricula;
    
    if (!lerInt(&matricula)) {
        printf("Matricula invalida.\n");
        return;
    }

    int indiceMatricula = buscarAlunoPorMatricula(listaAlunos, *qtdAluno, matricula);

    if (indiceMatricula == -1) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    // Remoção Física do Vetor (Hard Delete)
    for (int i = indiceMatricula; i < *qtdAluno - 1; i++) {
        listaAlunos[i] = listaAlunos[i + 1];
    }
    (*qtdAluno)--;

    printf("\n>>> Aluno excluido com sucesso! <<<\n");
}