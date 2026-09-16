#include <stdio.h>
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"
#include "auxiliares.h"
#include "relatorios.h"


int menuPrincipal();
int menuDisciplina();

int main(void) {
    Aluno listaAlunos[TAM_ALUNOS];
    int opcao;
    int qtdAluno = 0;
    int sair = 0;

    while (!sair) {
        opcao = menuPrincipal();
        switch (opcao) {
            case 0:
                sair = 1;
                break;

            case 1: {
                printf("\n====== Modulo Aluno ======\n");
                int sairAluno = 0;
                int opcaoAluno;

                while (!sairAluno) {
                    opcaoAluno = menuAluno();

                    switch (opcaoAluno) {
                        case 0:
                            sairAluno = 1;
                            break;

                        case 1:
                            printf("Cadastrar Aluno\n");
                            cadastrarAluno(listaAlunos, qtdAluno);
                            
                            break;

                        case 2:
                            printf("Listar Aluno\n");
                            listarAlunos(listaAlunos, qtdAluno);
                            break;

                        case 3:
                            printf("Atualizar Aluno\n");
                            atualizarAluno(listaAlunos, qtdAluno);
                            break;

                        case 4:
                            printf("Excluir Aluno\n");
                            excluirAluno(listaAlunos, &qtdAluno);
                            break;

                        default:
                            printf("Opcao invalida\n");
                            break;
                    }
                }
                break;
            }

            case 2: {
                printf("====== Modulo Professor ======\n");
                int sairProfessor = 0;
                int opcaoProfessor;

                while (!sairProfessor) {
                    opcaoProfessor = menuProfessor();

                    switch (opcaoProfessor) {
                        case 0:
                            sairProfessor = 1;
                            break;

                        case 1:
                            printf("Cadastrar Professor\n");
                            break;

                        case 2:
                            printf("Listar Professor\n");
                            break;

                        case 3:
                            printf("Atualizar Professor\n");
                            break;

                        case 4:
                            printf("Excluir Professor\n");
                            break;

                        default:
                            printf("Opcao invalida\n");
                            break;
                    }
                }
                break;
            }

            case 3: {
                printf("====== Modulo Disciplina ======\n");
                int sairDisciplina = 0;
                int opcaoDisciplina;

                while (!sairDisciplina) {
                    opcaoDisciplina = menuDisciplina();

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
                            printf("Opcao invalida\n");
                            break;
                    }
                }
                break;
            }

            default:
                printf("Opcao invalida\n");
                break;
        }
    }

    return 0;
}

// funcao do menu geral
int menuPrincipal() {
    int opcao;
    printf("ESCOLA MUNDO EDUCACAO \n"); // nome qualquer
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