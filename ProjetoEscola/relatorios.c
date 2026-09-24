#include <stdio.h>
#include <string.h>
#include "relatorios.h"
#include "auxiliares.h"

int menuRelatorios(void) {
    int opcao;
    printf("\n--- MENU DE RELATORIOS ---\n");
    printf("0 - Voltar ao Menu Principal\n");
    printf("1 - Listar Alunos por Sexo\n");
    printf("2 - Listar Alunos Ordenados por Nome\n");
    printf("3 - Listar Alunos Ordenados por Data de Nascimento\n");
    printf("4 - Listar Professores por Sexo\n");
    printf("5 - Listar Professores Ordenados por Nome\n");
    printf("6 - Listar Professores Ordenados por Data de Nascimento\n");
    printf("7 - Listar Aniversariantes do Mes\n");
    printf("8 - Buscar Aluno/Professor por Nome (minimo 3 letras)\n");
    printf("9 - Listar Alunos Matriculados em Menos de 3 Disciplinas\n");
    printf("10 - Listar Disciplinas que Extrapolam 40 Vagas\n");
    printf("Escolha uma opcao: ");

    if (!lerInt(&opcao)) {
        return -1;
    }
    return opcao;
}

void listarAlunosPorSexo(Aluno listaAlunos[], int qtdAluno) {
    printf("Digite o sexo para busca (M/F): ");
    char sexo = validarSexo();

    printf("\n--- ALUNOS DO SEXO (%c) ---\n", sexo);
    int encontrados = 0;
    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].ativo && listaAlunos[i].sexo == sexo) {
            printf("Matricula: %d | Nome: %-20s | CPF: %s | Data Nasc: %02d/%02d/%04d\n",
                   listaAlunos[i].matricula, listaAlunos[i].nome, listaAlunos[i].cpf,
                   listaAlunos[i].dataNascimento.dia, listaAlunos[i].dataNascimento.mes, listaAlunos[i].dataNascimento.ano);
            encontrados++;
        }
    }
    if (encontrados == 0) printf("Nenhum aluno encontrado para esse sexo.\n");
}

void listarAlunosPorNome(Aluno listaAlunos[], int qtdAluno) {
    Aluno copia[TAM_ALUNOS];
    int qtdAtivos = 0;

    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].ativo) {
            copia[qtdAtivos++] = listaAlunos[i];
        }
    }

    if (qtdAtivos == 0) {
        printf("Nenhum aluno ativo cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdAtivos - 1; i++) {
        for (int j = 0; j < qtdAtivos - i - 1; j++) {
            if (strcmp(copia[j].nome, copia[j + 1].nome) > 0) {
                Aluno temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    printf("\n--- ALUNOS ORDENADOS POR NOME ---\n");
    for (int i = 0; i < qtdAtivos; i++) {
        printf("Nome: %-25s | Matricula: %d | Sexo: %c\n",
               copia[i].nome, copia[i].matricula, copia[i].sexo);
    }
}

void listarAlunosPorDataNascimento(Aluno listaAlunos[], int qtdAluno) {
    Aluno copia[TAM_ALUNOS];
    int qtdAtivos = 0;

    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].ativo) copia[qtdAtivos++] = listaAlunos[i];
    }

    if (qtdAtivos == 0) {
        printf("Nenhum aluno ativo cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdAtivos - 1; i++) {
        for (int j = 0; j < qtdAtivos - i - 1; j++) {
            Data d1 = copia[j].dataNascimento;
            Data d2 = copia[j + 1].dataNascimento;

            if ((d1.ano > d2.ano) ||
                (d1.ano == d2.ano && d1.mes > d2.mes) ||
                (d1.ano == d2.ano && d1.mes == d2.mes && d1.dia > d2.dia)) {
                Aluno temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    printf("\n--- ALUNOS ORDENADOS POR DATA DE NASCIMENTO ---\n");
    for (int i = 0; i < qtdAtivos; i++) {
        printf("Data: %02d/%02d/%04d | Nome: %-25s | Matricula: %d\n",
               copia[i].dataNascimento.dia, copia[i].dataNascimento.mes, copia[i].dataNascimento.ano,
               copia[i].nome, copia[i].matricula);
    }
}

void listarProfessoresPorSexo(Professor listaProfessores[], int qtdProfessor) {
    printf("Digite o sexo para busca (M/F): ");
    char sexo = validarSexo();

    printf("\n--- PROFESSORES DO SEXO (%c) ---\n", sexo);
    int encontrados = 0;
    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].ativo && listaProfessores[i].sexo == sexo) {
            printf("Matricula: %d | Nome: %-20s | CPF: %s\n",
                   listaProfessores[i].matricula, listaProfessores[i].nome, listaProfessores[i].cpf);
            encontrados++;
        }
    }
    if (encontrados == 0) printf("Nenhum professor encontrado.\n");
}

void listarProfessoresPorNome(Professor listaProfessores[], int qtdProfessor) {
    Professor copia[TAM_PROFESSORES];
    int qtdAtivos = 0;

    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].ativo) copia[qtdAtivos++] = listaProfessores[i];
    }

    if (qtdAtivos == 0) {
        printf("Nenhum professor ativo cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdAtivos - 1; i++) {
        for (int j = 0; j < qtdAtivos - i - 1; j++) {
            if (strcmp(copia[j].nome, copia[j + 1].nome) > 0) {
                Professor temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    printf("\n--- PROFESSORES ORDENADOS POR NOME ---\n");
    for (int i = 0; i < qtdAtivos; i++) {
        printf("Nome: %-25s | Matricula: %d\n", copia[i].nome, copia[i].matricula);
    }
}

void listarProfessoresPorDataNascimento(Professor listaProfessores[], int qtdProfessor) {
    Professor copia[TAM_PROFESSORES];
    int qtdAtivos = 0;

    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].ativo) copia[qtdAtivos++] = listaProfessores[i];
    }

    if (qtdAtivos == 0) {
        printf("Nenhum professor ativo cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdAtivos - 1; i++) {
        for (int j = 0; j < qtdAtivos - i - 1; j++) {
            Data d1 = copia[j].dataNascimento;
            Data d2 = copia[j + 1].dataNascimento;

            if ((d1.ano > d2.ano) ||
                (d1.ano == d2.ano && d1.mes > d2.mes) ||
                (d1.ano == d2.ano && d1.mes == d2.mes && d1.dia > d2.dia)) {
                Professor temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    printf("\n--- PROFESSORES ORDENADOS POR DATA DE NASCIMENTO ---\n");
    for (int i = 0; i < qtdAtivos; i++) {
        printf("Data: %02d/%02d/%04d | Nome: %-25s | Matricula: %d\n",
               copia[i].dataNascimento.dia, copia[i].dataNascimento.mes, copia[i].dataNascimento.ano,
               copia[i].nome, copia[i].matricula);
    }
}

void listarAniversariantesDoMes(Aluno listaAlunos[], int qtdAluno, Professor listaProfessores[], int qtdProfessor) {
    int mes;
    printf("Digite o numero do mes (1-12): ");
    if (!lerInt(&mes) || mes < 1 || mes > 12) {
        printf("Mes invalido!\n");
        return;
    }

    printf("\n--- ANIVERSARIANTES DO MES %02d ---\n", mes);

    printf("\n[Alunos]:\n");
    int achou = 0;
    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].ativo && listaAlunos[i].dataNascimento.mes == mes) {
            printf("- Dia %02d: %s (Matricula: %d)\n",
                   listaAlunos[i].dataNascimento.dia, listaAlunos[i].nome, listaAlunos[i].matricula);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum aluno aniversariante neste mes.\n");

    printf("\n[Professores]:\n");
    achou = 0;
    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].ativo && listaProfessores[i].dataNascimento.mes == mes) {
            printf("- Dia %02d: %s (Matricula: %d)\n",
                   listaProfessores[i].dataNascimento.dia, listaProfessores[i].nome, listaProfessores[i].matricula);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum professor aniversariante neste mes.\n");
}

void buscarPessoaPorTexto(Aluno listaAlunos[], int qtdAluno, Professor listaProfessores[], int qtdProfessor) {
    char busca[TAM_NOME];
    printf("Digite o nome ou parte dele para buscar (minimo 3 letras): ");
    lerTexto(busca, TAM_NOME);
    formatarNome(busca);

    if (strlen(busca) < 3) {
        printf("Digite no minimo 3 caracteres para realizar a busca.\n");
        return;
    }

    printf("\n--- RESULTADOS DA BUSCA POR '%s' ---\n", busca);

    printf("\n[Alunos]:\n");
    int achou = 0;
    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].ativo && strstr(listaAlunos[i].nome, busca) != NULL) {
            printf("- Nome: %-25s | Matricula: %d\n", listaAlunos[i].nome, listaAlunos[i].matricula);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum aluno encontrado.\n");

    printf("\n[Professores]:\n");
    achou = 0;
    for (int i = 0; i < qtdProfessor; i++) {
        if (listaProfessores[i].ativo && strstr(listaProfessores[i].nome, busca) != NULL) {
            printf("- Nome: %-25s | Matricula: %d\n", listaProfessores[i].nome, listaProfessores[i].matricula);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum professor encontrado.\n");
}

// NOVO (Exigência do PDF): Alunos matriculados em menos de 3 disciplinas
void listarAlunosMenosDeTresDisciplinas(Aluno listaAlunos[], int qtdAluno, Disciplina listaDisciplinas[], int qtdDisciplina) {
    printf("\n--- ALUNOS MATRICULADOS EM MENOS DE 3 DISCIPLINAS ---\n");
    int encontrados = 0;

    for (int i = 0; i < qtdAluno; i++) {
        if (listaAlunos[i].ativo) {
            int contDisciplinas = 0;

            for (int d = 0; d < qtdDisciplina; d++) {
                if (listaDisciplinas[d].ativa) {
                    for (int a = 0; a < listaDisciplinas[d].qtdAlunosMatriculados; a++) {
                        if (listaDisciplinas[d].alunosMatriculados[a] == listaAlunos[i].matricula) {
                            contDisciplinas++;
                            break;
                        }
                    }
                }
            }

            if (contDisciplinas < 3) {
                printf("Matricula: %d | Nome: %-25s | Disciplinas Matriculadas: %d\n",
                       listaAlunos[i].matricula, listaAlunos[i].nome, contDisciplinas);
                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        printf("Nenhum aluno encontrado matriculado em menos de 3 disciplinas.\n");
    }
}

// NOVO (Exigência do PDF): Disciplinas que extrapolam 40 vagas (com nome do professor)
void listarDisciplinasExtrapolamQuarentaVagas(Disciplina listaDisciplinas[], int qtdDisciplina, Professor listaProfessores[], int qtdProfessor) {
    printf("\n--- DISCIPLINAS QUE EXTRAPOLAM 40 VAGAS ---\n");
    int encontradas = 0;

    for (int i = 0; i < qtdDisciplina; i++) {
        if (listaDisciplinas[i].ativa && listaDisciplinas[i].vagas > 40) {
            char nomeProf[50] = "Professor nao encontrado";
            int idxProf = buscarProfessorPorMatricula(listaProfessores, qtdProfessor, listaDisciplinas[i].matriculaProfessor);
            
            if (idxProf != -1) {
                strcpy(nomeProf, listaProfessores[idxProf].nome);
            }

            printf("Codigo: %d | Disciplina: %-20s | Semestre: %s | Prof: %-20s | Vagas: %d\n",
                   listaDisciplinas[i].codigo, listaDisciplinas[i].nome, listaDisciplinas[i].semestre,
                   nomeProf, listaDisciplinas[i].vagas);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma disciplina cadastrada com mais de 40 vagas.\n");
    }
}