#include <stdio.h>
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"
#include "relatorios.h"
#include "auxiliares.h"

int menuPrincipal(void);

int main(void) {
    Aluno listaAlunos[TAM_ALUNOS];
    int qtdAluno = 0;

    Professor listaProfessores[TAM_PROFESSORES];
    int qtdProfessor = 0;

    Disciplina listaDisciplinas[QTD_MAX_DISCIPLINA];
    int qtdDisciplina = 0;

    int opcao;
    int sair = 0;

    while (!sair) {
        opcao = menuPrincipal();
        switch (opcao) {
            case 0:
                sair = 1;
                printf("\nSaindo do sistema... Ate logo!\n");
                break;

            case 1: {
                int sairAluno = 0;
                while (!sairAluno) {
                    int opcaoAluno = menuAluno();

                    switch (opcaoAluno) {
                        case 0:
                            sairAluno = 1;
                            break;
                        case 1:
                            cadastrarAluno(listaAlunos, &qtdAluno);
                            break;
                        case 2:
                            listarAlunos(listaAlunos, qtdAluno);
                            break;
                        case 3:
                            atualizarAluno(listaAlunos, qtdAluno);
                            break;
                        case 4:
                            excluirAluno(listaAlunos, &qtdAluno);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            }

            case 2: {
                int sairProfessor = 0;
                while (!sairProfessor) {
                    int opcaoProfessor = menuProfessor();

                    switch (opcaoProfessor) {
                        case 0:
                            sairProfessor = 1;
                            break;
                        case 1:
                            cadastrarProfessor(listaProfessores, &qtdProfessor);
                            break;
                        case 2:
                            listarProfessores(listaProfessores, qtdProfessor);
                            break;
                        case 3:
                            atualizarProfessor(listaProfessores, qtdProfessor);
                            break;
                        case 4:
                            excluirProfessor(listaProfessores, &qtdProfessor, listaDisciplinas, qtdDisciplina);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            }

            case 3: {
                int sairDisciplina = 0;
                while (!sairDisciplina) {
                    int opcaoDisciplina = menuDisciplina();

                    switch (opcaoDisciplina) {
                        case 0:
                            sairDisciplina = 1;
                            break;
                        case 1:
                            cadastrarDisciplina(listaDisciplinas, &qtdDisciplina, listaProfessores, qtdProfessor);
                            break;
                        case 2:
                            listarDisciplinas(listaDisciplinas, qtdDisciplina, listaProfessores, qtdProfessor);
                            break;
                        case 3:
                            atualizarDisciplina(listaDisciplinas, qtdDisciplina, listaProfessores, qtdProfessor);
                            break;
                        case 4:
                            excluirDisciplina(listaDisciplinas, &qtdDisciplina);
                            break;
                        case 5:
                            matricularAlunoNaDisciplina(listaDisciplinas, qtdDisciplina, listaAlunos, qtdAluno);
                            break;
                        case 6:
                            desmatricularAlunoDaDisciplina(listaDisciplinas, qtdDisciplina, listaAlunos, qtdAluno);
                            break;
                        case 7:
                            relatorioAlunosPorDisciplina(listaDisciplinas, qtdDisciplina, listaAlunos, qtdAluno);
                            break;
                        case 8:
                            relatorioVagasDisciplinas(listaDisciplinas, qtdDisciplina);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            }

            case 4: {
                int sairRelatorios = 0;
                while (!sairRelatorios) {
                    int opcaoRelatorio = menuRelatorios();

                    switch (opcaoRelatorio) {
                        case 0:
                            sairRelatorios = 1;
                            break;
                        case 1:
                            listarAlunosPorSexo(listaAlunos, qtdAluno);
                            break;
                        case 2:
                            listarAlunosPorNome(listaAlunos, qtdAluno);
                            break;
                        case 3:
                            listarAlunosPorDataNascimento(listaAlunos, qtdAluno);
                            break;
                        case 4:
                            listarProfessoresPorSexo(listaProfessores, qtdProfessor);
                            break;
                        case 5:
                            listarProfessoresPorNome(listaProfessores, qtdProfessor);
                            break;
                        case 6:
                            listarProfessoresPorDataNascimento(listaProfessores, qtdProfessor);
                            break;
                        case 7:
                            listarAniversariantesDoMes(listaAlunos, qtdAluno, listaProfessores, qtdProfessor);
                            break;
                        case 8:
                            buscarPessoaPorTexto(listaAlunos, qtdAluno, listaProfessores, qtdProfessor);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            }

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    return 0;
}

int menuPrincipal(void) {
    int opcao;
    printf("\n=============================\n");
    printf("     ESCOLA MUNDO EDUCACAO   \n");
    printf("=============================\n");
    printf("0 - Sair\n");
    printf("1 - Modulo Alunos\n");
    printf("2 - Modulo Professores\n");
    printf("3 - Modulo Disciplinas\n");
    printf("4 - Relatorios\n");
    printf("Escolha uma opcao: ");

    if (!lerInt(&opcao)) {
        return -1;
    }
    return opcao;
}