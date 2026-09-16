#include <stdio.h>
#include "aluno.h" // Inclui o contrato e a struct
#include "auxiliares.h" // Inclui a função limparBuffer

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

int cadastrarAluno(Aluno listaAlunos[], int qtdAluno) {
    if (qtdAluno == TAM_ALUNOS) {
        printf("Lista de alunos cheia\n");
        return 0;
    }

    Aluno novoAluno;
        printf("====== Cadastro de Aluno =====\n");
        printf("Digite a matricula: ");
        scanf("%d", &novoAluno.matricula);
        limparBuffer();

        if(buscarAlunoPorMatricula(listaAlunos, qtdAluno, novoAluno.matricula) == -1) {
            printf("Matricula ja cadastrada\n");
            return 0;
        }

        printf("Digite o nome: \n");
        lerTexto(novoAluno.nome);
        formatarNome(novoAluno.nome);

        printf("Digite o sexo (M/F/): \n");
        novoAluno.sexo = validarSexo(novoAluno.sexo);

        do {
            printf("Digite a data de nascimento (DD/MM/AAAA): \n");
            scanf("%d/%d/%d", &novoAluno.dataNascimento.dia, &novoAluno.dataNascimento.mes, &novoAluno.dataNascimento.ano);
            limparBuffer();
        } while(!validarData(novoAluno.dataNascimento));
        
        printf("Digite o CPF (somente numeros): \n");
        lerTexto(novoAluno.cpf);
        validarCpf(novoAluno.cpf);

        novoAluno.ativo = 1; 
        listaAlunos[qtdAluno] = novoAluno;
        (qtdAluno)++;
        printf("Aluno cadastrado com sucesso\n");
        return 1;

}

void listarAlunos(Aluno listaAlunos[], int qtdAluno) {
    int cadastrados = 0;
    if (cadastrados == 0) {
        printf("Lista aluno esta vazia\n");
    } else {
        for (int i = 0; i < qtdAluno; i++) {
            if (listaAlunos[i].ativo == 1) {
                printf("Matricula: %d | Nome: %s | Sexo: %c | Data de Nascimento: %02d/%02d/%d | CPF: %s\n",
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
    }
}

int buscarAlunoPorMatricula(Aluno listaAlunos[], int qtdAluno, int matricula) {
    for(int i = 0; i < qtdAluno; i++) {
        if(listaAlunos[i].matricula == matricula) 
            return i;
    }
    return -1;
}

void atualizarAluno(Aluno listaAlunos[], int qtdAluno) {
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);

    int indiceMatricula = buscarAlunoPorMatricula(listaAlunos, qtdAluno, matricula);

    if(indiceMatricula == -1) {
        printf("Aluno nao encontrado\n");
        return;
    }

    printf("Digite o novo nome: \n");
    lerTexto(listaAlunos[indiceMatricula].nome);
    formatarNome(listaAlunos[indiceMatricula].nome);

    
    listaAlunos[indiceMatricula].sexo = validarSexo(listaAlunos[indiceMatricula].sexo);

    do {
        printf("Digite a nova data de nascimento (DD/MM/AAAA): \n");
        scanf("%d/%d/%d\n", &listaAlunos[indiceMatricula].dataNascimento.dia, 
                            &listaAlunos[indiceMatricula].dataNascimento.mes, 
                            &listaAlunos[indiceMatricula].dataNascimento.ano);

        if(!validarData(listaAlunos[indiceMatricula].dataNascimento))
            printf("Data invalida! Tente novamente\n");

    } while(!validarData(listaAlunos[indiceMatricula].dataNascimento));


    // printf("Digite o CPF (somente numeros): \n"); Fazer a parte do cpf tambem
    // lerTexto(novoAluno.cpf);
    // validarCpf(novoAluno.cpf);

 }


void excluirAluno(Aluno listaAlunos[], int *qtdAluno) {
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    
    int indiceMatricula = buscarAlunoPorMatricula(listaAlunos, qtdAluno, matricula);

    if(indiceMatricula == - 1) {
        printf("Aluno nao encontrado\n");
        return;
    }

    for(int i = 0; i < qtdAluno - 1; i++) {
        listaAlunos[i] = listaAlunos[i + 1];
    }

    qtdAluno--;
}
