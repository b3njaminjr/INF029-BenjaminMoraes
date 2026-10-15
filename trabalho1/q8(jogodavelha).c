#include <stdio.h>
#include <ctype.h>

void resetarTabuleiro(char tabuleiro[3][3]);
void exibirTabuleiro(char tabuleiro[3][3]);
int validarJogada(char tabuleiro[3][3], char letraLinha, int numColuna);
void executarJogada(char tabuleiro[3][3], char letraLinha, int numColuna, char simboloJogador);
int verificarVencedor(char tabuleiro[3][3], char simboloJogador);
int tabuleiroEstaCheio(char tabuleiro[3][3]);

int main()
{
    char tabuleiro[3][3];
    char letraLinha;
    int numColuna;
    int jogadorAtual = 1;
    char simboloJogador;
    int fimDeJogo = 0;

    resetarTabuleiro(tabuleiro);

    printf("=== JOGO DA VELHA (VERSAO OTIMIZADA) ===\n");
    printf("Instrucoes: Informe a linha (A-C) e a coluna (1-3).\n");
    printf("Exemplo: A1, B3, C2\n");
    printf("Jogador 1: X | Jogador 2: O\n\n");

    while (!fimDeJogo) {
        exibirTabuleiro(tabuleiro);

        simboloJogador = (jogadorAtual == 1) ? 'X' : 'O';

        printf("Vez do Jogador %d (%c). Informe sua jogada: ", jogadorAtual, simboloJogador);
        if (scanf(" %c%d", &letraLinha, &numColuna) != 2) {
            while (getchar() != '\n');
            printf("Entrada invalida! Tente novamente.\n\n");
            continue;
        }

        if (validarJogada(tabuleiro, letraLinha, numColuna)) {
            executarJogada(tabuleiro, letraLinha, numColuna, simboloJogador);

            if (verificarVencedor(tabuleiro, simboloJogador)) {
                exibirTabuleiro(tabuleiro);
                printf("Parabens! O Jogador %d (%c) venceu a partida!\n", jogadorAtual, simboloJogador);
                fimDeJogo = 1;
            } 
            else if (tabuleiroEstaCheio(tabuleiro)) {
                exibirTabuleiro(tabuleiro);
                printf("Fim de jogo! O tabuleiro esta cheio. Empate!\n");
                fimDeJogo = 1;
            } 
            else {
                jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
            }
        } 
        else {
            printf("Jogada invalida ou posicao ocupada!\n");
            printf("Use letras de A a C para linhas e numeros de 1 a 3 para colunas.\n\n");
        }
    }

    return 0;
}

void resetarTabuleiro(char tabuleiro[3][3])
{
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            tabuleiro[r][c] = ' ';
        }
    }
}

void exibirTabuleiro(char tabuleiro[3][3])
{
    printf("\n");
    printf("     1   2   3\n");
    printf(" A   %c | %c | %c\n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
    printf("    ---+---+---\n");
    printf(" B   %c | %c | %c\n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
    printf("    ---+---+---\n");
    printf(" C   %c | %c | %c\n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
    printf("\n");
}

int validarJogada(char tabuleiro[3][3], char letraLinha, int numColuna)
{
    letraLinha = toupper(letraLinha);

    if (letraLinha < 'A' || letraLinha > 'C') return 0;
    if (numColuna < 1 || numColuna > 3) return 0;

    int r = letraLinha - 'A';
    int c = numColuna - 1;

    if (tabuleiro[r][c] != ' ') return 0;

    return 1;
}

void executarJogada(char tabuleiro[3][3], char letraLinha, int numColuna, char simboloJogador)
{
    letraLinha = toupper(letraLinha);
    int r = letraLinha - 'A';
    int c = numColuna - 1;

    tabuleiro[r][c] = simboloJogador;
}

int verificarVencedor(char tabuleiro[3][3], char simboloJogador)
{
    int linhasVencedoras[8][3][2] = {
        // Linhas
        { {0,0}, {0,1}, {0,2} },
        { {1,0}, {1,1}, {1,2} },
        { {2,0}, {2,1}, {2,2} },
        // Colunas
        { {0,0}, {1,0}, {2,0} },
        { {0,1}, {1,1}, {2,1} },
        { {0,2}, {1,2}, {2,2} },
        // Diagonais
        { {0,0}, {1,1}, {2,2} },
        { {0,2}, {1,1}, {2,0} }
    };

    for (int i = 0; i < 8; i++) {
        int r1 = linhasVencedoras[i][0][0];
        int c1 = linhasVencedoras[i][0][1];
        int r2 = linhasVencedoras[i][1][0];
        int c2 = linhasVencedoras[i][1][1];
        int r3 = linhasVencedoras[i][2][0];
        int c3 = linhasVencedoras[i][2][1];

        if (tabuleiro[r1][c1] == simboloJogador && 
            tabuleiro[r2][c2] == simboloJogador && 
            tabuleiro[r3][c3] == simboloJogador) {
            return 1;
        }
    }

    return 0;
}

int tabuleiroEstaCheio(char tabuleiro[3][3])
{
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (tabuleiro[r][c] == ' ') {
                return 0; // Ainda há espaços vazios
            }
        }
    }
    return 1; 
}