#include <stdio.h>
#include <string.h>
#include "disciplina.h"
#include "auxiliares.h"

int menuDisciplina(void) {
    int opcao;
    printf("\n====== Menu Disciplina ======\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Disciplina\n");
    printf("2 - Listar Disciplinas\n");
    printf("3 - Atualizar Disciplina\n");
    printf("4 - Excluir Disciplina\n");
    printf("5 - Matricular Aluno em Disciplina\n");
    printf("6 - Desmatricular Aluno de Disciplina\n");
    printf("7 - Relatorio de Alunos por Disciplina\n");
    printf("8 - Relatorio de Ocupacao de Vagas\n");
    printf("Escolha uma opcao: ");

    if (!lerInt(&opcao)) {
        return -1;
    }
    return opcao;
}

int formatarNomeDisciplina(char texto[]) {
    int tam = strlen(texto);
    formatarNome(texto);

    for (int i = 0; i < tam; i++) {
        char c = texto[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
            printf("Nome invalido! Use apenas letras e espacos. Tente novamente.\n");
            return -1;
        }
    }
    return 0;
}

int buscarDisciplinaPorCodigo(Disciplina listaDisciplinas[], int qtdDisciplina, int codigo) {
    for (int i = 0; i < qtdDisciplina; i++) {
        if (listaDisciplinas[i].codigo == codigo && listaDisciplinas[i].ativa == 1) {
            return i;
        }
    }
    return -1;
}

int cadastrarDisciplina(Disciplina listaDisciplinas[], int *qtdDisciplina, Professor listaProfessores[], int qtdProfessor) {
    if (*qtdDisciplina >= QTD_MAX_DISCIPLINA) {
        printf("Lista de disciplinas esta cheia!\n");
        return 0;
    }

    // CORREÇÃO DO BUG DO LOOP INFINITO:
    // Verifica se existe ao menos 1 professor ativo cadastrado no sistema antes de prosseguir
    int profsAtivos = 0;
    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].ativo) profsAtivos++;
    }

    if (profsAtivos == 0) {
        printf("\n[ERRO] Nao e possivel cadastrar disciplinas sem antes cadastrar ao menos um professor ativo!\n");
        printf("Cadastre um professor no Modulo de Professores antes de continuar.\n");
        return 0;
    }

    Disciplina novaDisciplina = {0};
    int disciplinaValida = 0;

    do {
        printf("Informe o codigo da disciplina: ");
        int leuComSucesso = lerInt(&novaDisciplina.codigo);

        if (!leuComSucesso) {
            printf("Caracteres nao sao permitidos no codigo. Tente novamente.\n");
        } else if (novaDisciplina.codigo <= 0) {
            printf("Valor invalido! Somente valores positivos maiores que zero. Tente novamente.\n");
        } else if (buscarDisciplinaPorCodigo(listaDisciplinas, *qtdDisciplina, novaDisciplina.codigo) != -1) {
            printf("Erro: Ja existe uma disciplina cadastrada com esse codigo!\n");
        } else {
            disciplinaValida = 1;
        }
    } while (!disciplinaValida);

    int nomeValido = 0;
    do {
        printf("Informe o nome da disciplina: ");
        lerTexto(novaDisciplina.nome, MAX_NOME);

        if (formatarNomeDisciplina(novaDisciplina.nome) == 0) {
            nomeValido = 1;
        }
    } while (!nomeValido);

    int semestreValido = 0;
    do {
        printf("Informe o semestre (ex: 2026.2): ");
        lerTexto(novaDisciplina.semestre, TAM_SEMESTRE);

        if (validarSemestre(novaDisciplina.semestre) == 1) {
            semestreValido = 1;
        } else {
            printf("Semestre invalido! Tente novamente.\n");
        }
    } while (!semestreValido);

    int professorValido = 0;
    do {
        printf("Informe a matricula do professor responsavel: ");
        int leuComSucesso = lerInt(&novaDisciplina.matriculaProfessor);

        if (!leuComSucesso) {
            printf("Caracteres nao sao permitidos. Tente novamente.\n");
        } else if (novaDisciplina.matriculaProfessor <= 0) {
            printf("Valor invalido! Tente novamente.\n");
        } else {
            int indiceProfessor = buscarProfessorPorMatricula(listaProfessores, qtdProfessor, novaDisciplina.matriculaProfessor);

            if (indiceProfessor != -1) {
                professorValido = 1;
            } else {
                printf("Professor nao encontrado ou inativo no sistema! Tente novamente.\n");
            }
        }
    } while (!professorValido);

    int vagasValidas = 0;
    do {
        printf("Informe a quantidade total de vagas da disciplina: ");
        int leuComSucesso = lerInt(&novaDisciplina.vagas);

        if (!leuComSucesso) {
            printf("Caracteres nao sao permitidos. Tente novamente.\n");
        } else if (novaDisciplina.vagas <= 0) {
            printf("A disciplina deve ter no minimo 1 vaga. Tente novamente.\n");
        } else if (novaDisciplina.vagas > MAX_ALUNOS_POR_DISCIPLINA) {
            printf("A quantidade excede o limite permitido (%d vagas). Tente novamente.\n", MAX_ALUNOS_POR_DISCIPLINA);
        } else {
            vagasValidas = 1;
        }
    } while (!vagasValidas);

    novaDisciplina.qtdAlunosMatriculados = 0;
    novaDisciplina.ativa = 1;

    listaDisciplinas[*qtdDisciplina] = novaDisciplina;
    (*qtdDisciplina)++;

    printf("\n>>> Disciplina cadastrada com sucesso! <<<\n");
    return 1;
}

void listarDisciplinas(Disciplina listaDisciplinas[], int qtdDisciplina, Professor listaProfessores[], int qtdProfessores) {
    int cadastradas = 0;
    printf("\n====== Lista de Disciplinas ======\n");
    for (int i = 0; i < qtdDisciplina; i++) {
        if (listaDisciplinas[i].ativa == 1) {
            char nomeProfessor[50] = "Nao encontrado";
            int idxProf = buscarProfessorPorMatricula(listaProfessores, qtdProfessores, listaDisciplinas[i].matriculaProfessor);

            if (idxProf != -1) {
                strcpy(nomeProfessor, listaProfessores[idxProf].nome);
            }

            printf("Codigo: %d | Nome: %-20s | Semestre: %s | Professor: %s | Vagas: %d | Ocupadas: %d\n",
                   listaDisciplinas[i].codigo,
                   listaDisciplinas[i].nome,
                   listaDisciplinas[i].semestre,
                   nomeProfessor,
                   listaDisciplinas[i].vagas,
                   listaDisciplinas[i].qtdAlunosMatriculados);
            cadastradas++;
        }
    }

    if (cadastradas == 0) {
        printf("Lista de disciplinas esta vazia.\n");
    }
}

void atualizarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplina, Professor listaProfessores[], int qtdProfessores) {
    printf("\n====== Atualizar Disciplina ======\n");
    printf("Digite o codigo da disciplina a ser atualizada: ");
    int codigo;
    if (!lerInt(&codigo)) {
        printf("Codigo invalido.\n");
        return;
    }

    int indiceCodigo = buscarDisciplinaPorCodigo(listaDisciplinas, qtdDisciplina, codigo);

    if (indiceCodigo == -1) {
        printf("Disciplina nao encontrada ou inativa.\n");
        return;
    }

    int nomeValido = 0;
    do {
        printf("Digite o novo nome da disciplina: ");
        lerTexto(listaDisciplinas[indiceCodigo].nome, MAX_NOME);
        if (formatarNomeDisciplina(listaDisciplinas[indiceCodigo].nome) == 0) {
            nomeValido = 1;
        }
    } while (!nomeValido);

    int semestreValido = 0;
    do {
        printf("Digite o novo semestre (ex: 2026.2): ");
        lerTexto(listaDisciplinas[indiceCodigo].semestre, TAM_SEMESTRE);
        if (validarSemestre(listaDisciplinas[indiceCodigo].semestre) == 1) {
            semestreValido = 1;
        } else {
            printf("Semestre invalido! Tente novamente.\n");
        }
    } while (!semestreValido);

    int professorValido = 0;
    do {
        printf("Digite a nova matricula do professor responsavel: ");
        int novaMatriculaProf;
        if (lerInt(&novaMatriculaProf)) {
            int idxProf = buscarProfessorPorMatricula(listaProfessores, qtdProfessores, novaMatriculaProf);
            if (idxProf != -1) {
                listaDisciplinas[indiceCodigo].matriculaProfessor = novaMatriculaProf;
                professorValido = 1;
            } else {
                printf("Professor nao encontrado no sistema! Tente novamente.\n");
            }
        } else {
            printf("Matricula invalida. Digite apenas numeros.\n");
        }
    } while (!professorValido);

    int vagasValidas = 0;
    do {
        printf("Digite a nova quantidade de vagas: ");
        int novasVagas;
        if (lerInt(&novasVagas)) {
            if (novasVagas < listaDisciplinas[indiceCodigo].qtdAlunosMatriculados) {
                printf("Erro: A disciplina ja possui %d alunos matriculados. O limite de vagas nao pode ser menor que isso.\n",
                       listaDisciplinas[indiceCodigo].qtdAlunosMatriculados);
            } else if (novasVagas <= 0) {
                printf("A quantidade de vagas deve ser maior que zero.\n");
            } else {
                listaDisciplinas[indiceCodigo].vagas = novasVagas;
                vagasValidas = 1;
            }
        }
    } while (!vagasValidas);

    printf("\n>>> Disciplina atualizada com sucesso! <<<\n");
}

void excluirDisciplina(Disciplina listaDisciplinas[], int *qtdDisciplina) {
    printf("\n====== Excluir Disciplina ======\n");
    printf("Digite o codigo da disciplina a ser excluida: ");

    int codigo;
    if (!lerInt(&codigo)) {
        printf("Codigo invalido.\n");
        return;
    }

    int indiceCodigo = buscarDisciplinaPorCodigo(listaDisciplinas, *qtdDisciplina, codigo);
    if (indiceCodigo == -1) {
        printf("Disciplina nao encontrada ou ja inativa.\n");
        return;
    }

    if (listaDisciplinas[indiceCodigo].qtdAlunosMatriculados > 0) {
        printf("Nao e possivel excluir uma disciplina com alunos matriculados!\n");
        printf("Cancele as matriculas dos alunos antes de prosseguir.\n");
        return;
    }

    listaDisciplinas[indiceCodigo].ativa = 0;

    printf("Disciplina excluida com sucesso (desativada)!\n");
}

int matricularAlunoNaDisciplina(Disciplina listaDisciplinas[], int qtdDisciplina, Aluno listaAlunos[], int qtdAluno) {
    if (qtdDisciplina == 0) {
        printf("Nenhuma disciplina cadastrada no sistema.\n");
        return 0;
    }

    int codigoDisciplina;
    printf("\n====== Matricula de Aluno em Disciplina ======\n");
    printf("Informe o codigo da disciplina: ");
    if (!lerInt(&codigoDisciplina)) {
        printf("Codigo invalido.\n");
        return 0;
    }

    int idxDisciplina = buscarDisciplinaPorCodigo(listaDisciplinas, qtdDisciplina, codigoDisciplina);
    if (idxDisciplina == -1) {
        printf("Disciplina nao encontrada!\n");
        return 0;
    }

    if (listaDisciplinas[idxDisciplina].qtdAlunosMatriculados >= listaDisciplinas[idxDisciplina].vagas) {
        printf("\n[ERRO] Nao ha vagas disponiveis para a disciplina '%s'!\n", listaDisciplinas[idxDisciplina].nome);
        printf("Vagas Ocupadas: %d / %d\n",
               listaDisciplinas[idxDisciplina].qtdAlunosMatriculados,
               listaDisciplinas[idxDisciplina].vagas);
        return 0;
    }

    int matriculaAluno;
    printf("Informe a matricula do aluno: ");
    if (!lerInt(&matriculaAluno)) {
        printf("Matricula invalida.\n");
        return 0;
    }

    int idxAluno = buscarAlunoPorMatricula(listaAlunos, qtdAluno, matriculaAluno);
    if (idxAluno == -1) {
        printf("Aluno nao encontrado ou inativo no sistema!\n");
        return 0;
    }

    for (int i = 0; i < listaDisciplinas[idxDisciplina].qtdAlunosMatriculados; i++) {
        if (listaDisciplinas[idxDisciplina].alunosMatriculados[i] == matriculaAluno) {
            printf("O aluno '%s' ja esta matriculado nesta disciplina!\n", listaAlunos[idxAluno].nome);
            return 0;
        }
    }

    int pos = listaDisciplinas[idxDisciplina].qtdAlunosMatriculados;
    listaDisciplinas[idxDisciplina].alunosMatriculados[pos] = matriculaAluno;
    listaDisciplinas[idxDisciplina].qtdAlunosMatriculados++;

    printf("\nAluno '%s' matriculado com sucesso na disciplina '%s'!\n",
           listaAlunos[idxAluno].nome, listaDisciplinas[idxDisciplina].nome);
    printf("Vagas restantes: %d\n",
           listaDisciplinas[idxDisciplina].vagas - listaDisciplinas[idxDisciplina].qtdAlunosMatriculados);

    return 1;
}

int desmatricularAlunoDaDisciplina(Disciplina listaDisciplinas[], int qtdDisciplina, Aluno listaAlunos[], int qtdAluno) {
    if (qtdDisciplina == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return 0;
    }

    int codigoDisciplina;
    printf("\n====== Cancelamento de Matricula ======\n");
    printf("Informe o codigo da disciplina: ");
    if (!lerInt(&codigoDisciplina)) {
        printf("Codigo invalido.\n");
        return 0;
    }

    int idxDisciplina = buscarDisciplinaPorCodigo(listaDisciplinas, qtdDisciplina, codigoDisciplina);
    if (idxDisciplina == -1) {
        printf("Disciplina nao encontrada!\n");
        return 0;
    }

    if (listaDisciplinas[idxDisciplina].qtdAlunosMatriculados == 0) {
        printf("Esta disciplina nao possui alunos matriculados.\n");
        return 0;
    }

    int matriculaAluno;
    printf("Informe a matricula do aluno a ser removido: ");
    if (!lerInt(&matriculaAluno)) {
        printf("Matricula invalida.\n");
        return 0;
    }

    int posAlunoNoVetor = -1;
    for (int i = 0; i < listaDisciplinas[idxDisciplina].qtdAlunosMatriculados; i++) {
        if (listaDisciplinas[idxDisciplina].alunosMatriculados[i] == matriculaAluno) {
            posAlunoNoVetor = i;
            break;
        }
    }

    if (posAlunoNoVetor == -1) {
        printf("Aluno com matricula %d nao esta cadastrado nesta disciplina.\n", matriculaAluno);
        return 0;
    }

    for (int i = posAlunoNoVetor; i < listaDisciplinas[idxDisciplina].qtdAlunosMatriculados - 1; i++) {
        listaDisciplinas[idxDisciplina].alunosMatriculados[i] = listaDisciplinas[idxDisciplina].alunosMatriculados[i + 1];
    }

    listaDisciplinas[idxDisciplina].qtdAlunosMatriculados--;

    printf("\nAluno removido com sucesso da disciplina '%s'!\n", listaDisciplinas[idxDisciplina].nome);
    printf("Vagas disponiveis atualizadas: %d / %d\n",
           listaDisciplinas[idxDisciplina].vagas - listaDisciplinas[idxDisciplina].qtdAlunosMatriculados,
           listaDisciplinas[idxDisciplina].vagas);

    return 1;
}

void relatorioAlunosPorDisciplina(Disciplina listaDisciplinas[], int qtdDisciplina, Aluno listaAlunos[], int qtdAluno) {
    if (qtdDisciplina == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }

    int codigoDisciplina;
    printf("\n====== Relatorio de Alunos por Disciplina ======\n");
    printf("Informe o codigo da disciplina: ");
    if (!lerInt(&codigoDisciplina)) {
        printf("Codigo invalido.\n");
        return;
    }

    int idxDisc = buscarDisciplinaPorCodigo(listaDisciplinas, qtdDisciplina, codigoDisciplina);
    if (idxDisc == -1) {
        printf("Disciplina nao encontrada!\n");
        return;
    }

    printf("\nDisciplina: %s (%s)\n", listaDisciplinas[idxDisc].nome, listaDisciplinas[idxDisc].semestre);
    printf("Alunos Matriculados (%d/%d):\n", listaDisciplinas[idxDisc].qtdAlunosMatriculados, listaDisciplinas[idxDisc].vagas);
    printf("--------------------------------------------------\n");

    if (listaDisciplinas[idxDisc].qtdAlunosMatriculados == 0) {
        printf("Nenhum aluno matriculado nesta disciplina.\n");
        return;
    }

    for (int i = 0; i < listaDisciplinas[idxDisc].qtdAlunosMatriculados; i++) {
        int mat = listaDisciplinas[idxDisc].alunosMatriculados[i];
        int idxAluno = buscarAlunoPorMatricula(listaAlunos, qtdAluno, mat);

        if (idxAluno != -1) {
            printf("  [%d] Matricula: %d | Nome: %s\n", i + 1, listaAlunos[idxAluno].matricula, listaAlunos[idxAluno].nome);
        } else {
            printf("  [%d] Matricula: %d | Nome: [Aluno Inativo ou Removido]\n", i + 1, mat);
        }
    }
}

void relatorioVagasDisciplinas(Disciplina listaDisciplinas[], int qtdDisciplina) {
    printf("\n====== RELATORIO DE OCUPACAO DE VAGAS ======\n");

    int totalAtivas = 0;
    for (int i = 0; i < qtdDisciplina; i++) {
        if (listaDisciplinas[i].ativa == 1) {
            totalAtivas++;
            int ocupadas = listaDisciplinas[i].qtdAlunosMatriculados;
            int totalVagas = listaDisciplinas[i].vagas;
            int disponiveis = totalVagas - ocupadas;
            float percentual = ((float)ocupadas / totalVagas) * 100.0f;

            printf("Codigo: %d | Disciplina: %-20s | Semestre: %s\n",
                   listaDisciplinas[i].codigo, listaDisciplinas[i].nome, listaDisciplinas[i].semestre);
            printf("  Vagas Totais : %d | Ocupadas: %d | Disponiveis: %d | Ocupacao: %.1f%%\n",
                   totalVagas, ocupadas, disponiveis, percentual);
            printf("---------------------------------------------------------------------\n");
        }
    }

    if (totalAtivas == 0) {
        printf("Nenhuma disciplina ativa encontrada.\n");
    }
}