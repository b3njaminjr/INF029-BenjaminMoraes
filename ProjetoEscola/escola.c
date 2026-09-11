#include <stdio.h>
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"

int main(void) {
    Aluno listaAlunos[TAM_ALUNO];
    int opcao;
    int qtdAluno = 0;
    int sair = 0;

    while (!sair) {
        printf("Projeto Escola\n");
        printf("0- Sair\n");
        printf("1- Aluno\n");
        printf("2- Professor\n");
        printf("3- Disciplina\n");

        scanf("%d", &opcao);

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
                            cadastrarAluno(listaAlunos, &qtdAluno);
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

                while(!sairProfessor) {
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

                while(!sairDisciplina) {
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
    }

    return 0;
}