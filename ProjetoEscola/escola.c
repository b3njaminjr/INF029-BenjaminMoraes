#include <stdio.h>
#include "aluno.h"
#include "auxiliares.h"
#include "professor.h"
#include "disciplina.h"
#include "relatorios.h"

int menuPrincipal(void);

int main(void) {
    Aluno listaAlunos[TAM_ALUNOS];
    int qtdAluno = 0;

    Professor listaProfessores[TAM_PROFESSORES];
    int qtdProfessor = 0;

    int opcao;
    int sair = 0;

    while (!sair) {
        opcao = menuPrincipal();
        switch (opcao) {
            case 0:
                sair = 1;
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
                            excluirProfessor(listaProfessores, &qtdProfessor);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            }

            case 3: {
                printf("\n====== Modulo Disciplina ======\n");
                int sairDisciplina = 0;
                while (!sairDisciplina) {
                    int opcaoDisciplina = menuDisciplina();

                    switch (opcaoDisciplina) {
                        case 0:
                            sairDisciplina = 1;
                            break;
                        case 1:
                            printf("Cadastrar Disciplina\n");
                            break;
                        case 2:
                            printf("Listar Disciplina\n");
                            break;
                        case 3:
                            printf("Atualizar Disciplina\n");
                            break;
                        case 4:
                            printf("Excluir Disciplina\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            }

            case 4:
                printf("\n====== Modulo Relatorios ======\n");
                break;

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
    printf("    ESCOLA MUNDO EDUCACAO    \n");
    printf("=============================\n");
    printf("0 - Sair\n");
    printf("1 - Modulo Alunos\n");
    printf("2 - Modulo Professores\n");
    printf("3 - Modulo Disciplinas\n");
    printf("4 - Relatorios\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
    return opcao;
}