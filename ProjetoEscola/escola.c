#include <stdio.h>
#define TAM_ALUNO 3
int main() {

    int listaAlunos[TAM_ALUNO];
    int opcao;
    int qtdAluno = 0;
    
    int sair = 0; // falso

    while (!sair) {
        printf("Projeto Escola\n");
        printf("0- Sair\n");
        printf("1- Aluno\n");
        printf("2- Professor\n");
        printf("3- Disciplina\n");

        scanf("%d", &opcao);

        switch(opcao) {
            case 0: {
                sair = 1;
                break;
            }
            case 1: {
                printf("Modulo Aluno\n");
                int sairAluno = 0; // falso
                int opcaoAluno;
                while(!sairAluno) {
                    printf("0- Voltar\n");
                    printf("1- Cadastrar Aluno\n");
                    printf("2- Listar Aluno\n");
                    printf("3- Atualizar Aluno\n");
                    printf("4- Excluir Aluno\n");

                    scanf("%d", &opcaoAluno);
                    
                    switch (opcaoAluno) {
                        case 0: {
                            sairAluno = 1;
                            break;
                        }
                        case 1: {
                            printf("Cadastrar Aluno\n");
                            if (qtdAluno == TAM_ALUNO) {
                                printf("Lista de alunos cheia\n");

                            } else {
                                printf("Digite a matricula: ");
                                int matricula;
                                scanf("%d", &matricula);

                                if(matricula < 0) {
                                    printf("Matricula invalida\n");
                                }

                                else {
                                    listaAlunos[qtdAluno] = matricula;
                                    qtdAluno++;
                                    printf("Aluno cadastrado com sucesso\n");
                                }
                            }
                            break;
                        }
                        case 2: {
                            printf("Listar Aluno\n");
                            if(qtdAluno == 0) {
                                printf("Lista aluno vazia\n");
                            } else {
                                for(int i = 0; i < qtdAluno; i++) {
                                    printf("Aluno %d: %d\n", i + 1, listaAlunos[i]);
                                }
                            }
                            break;
                        }
                        case 3: {
                            printf("Atualizar Aluno\n");
                            break;
                        }
                        case 4: {
                            printf("Excluir Aluno\n");
                            break;
                        }
                        default: {
                            printf("Opcao invalida\n");
                            break;
                        }
                    }
                }
                break;
            }

            case 2: {
                printf("Modulo Professor\n");
                break;

            }

            case 3: {
                printf("Modulo Disciplina\n");
                break;
            }
            default: {
                printf("Opcao invalida\n");
                break;
            }
        }
    }

    return 0;
}