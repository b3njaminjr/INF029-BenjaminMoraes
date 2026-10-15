#include <stdio.h>
#include <ctype.h>

#define TAMANHO_GRADE 10
#define TOTAL_NAVIOS 5

#define SIMBOLO_AGUA ' '
#define SIMBOLO_NAVIO 'N'
#define SIMBOLO_ACERTO 'O'
#define SIMBOLO_ERRO 'X'

void limparGrade(char grade[TAMANHO_GRADE][TAMANHO_GRADE]);
void imprimirGrade(char grade[TAMANHO_GRADE][TAMANHO_GRADE]);
void configurarTamanhosNavios(int tamanhos[TOTAL_NAVIOS]);
int posicionarNavio(char grade[TAMANHO_GRADE][TAMANHO_GRADE], int linha, int coluna, int tamanho, char orientacao);
void posicionarFrota(char grade[TAMANHO_GRADE][TAMANHO_GRADE], int tamanhos[TOTAL_NAVIOS], int idJogador);
int efetuarDisparo(char gradeAdversario[TAMANHO_GRADE][TAMANHO_GRADE], char gradeAtaques[TAMANHO_GRADE][TAMANHO_GRADE], int linha, int coluna);
int verificarVitoria(char grade[TAMANHO_GRADE][TAMANHO_GRADE]);
int executarTurno(int idJogador, char gradePropria[TAMANHO_GRADE][TAMANHO_GRADE], char gradeAtaques[TAMANHO_GRADE][TAMANHO_GRADE], char gradeAdversario[TAMANHO_GRADE][TAMANHO_GRADE]);

int main(void) {
    char gradeJogador1[TAMANHO_GRADE][TAMANHO_GRADE];
    char gradeJogador2[TAMANHO_GRADE][TAMANHO_GRADE];

    char ataquesJogador1[TAMANHO_GRADE][TAMANHO_GRADE];
    char ataquesJogador2[TAMANHO_GRADE][TAMANHO_GRADE];

    int tamanhosNavios[TOTAL_NAVIOS];
    int vencedor = 0;

    limparGrade(gradeJogador1);
    limparGrade(gradeJogador2);
    limparGrade(ataquesJogador1);
    limparGrade(ataquesJogador2);

    configurarTamanhosNavios(tamanhosNavios);

    printf("================================\n");
    printf("         BATALHA NAVAL          \n");
    printf("================================\n");

    printf("\nJogador 1: Posicione os seus navios.\n");
    posicionarFrota(gradeJogador1, tamanhosNavios, 1);

    printf("\nJogador 2: Posicione os seus navios.\n");
    posicionarFrota(gradeJogador2, tamanhosNavios, 2);

    while (vencedor == 0) {
        if (executarTurno(1, gradeJogador1, ataquesJogador1, gradeJogador2)) {
            vencedor = 1;
        } else {
            if (executarTurno(2, gradeJogador2, ataquesJogador2, gradeJogador1)) {
                vencedor = 2;
            }
        }
    }

    printf("\n================================\n");
    printf("     FIM DE JOGO! JOGADOR %d VENCEU!\n", vencedor);
    printf("================================\n");

    return 0;
}

void limparGrade(char grade[TAMANHO_GRADE][TAMANHO_GRADE]) {
    int i, j;
    for (i = 0; i < TAMANHO_GRADE; i++) {
        for (j = 0; j < TAMANHO_GRADE; j++) {
            grade[i][j] = SIMBOLO_AGUA;
        }
    }
}

void imprimirGrade(char grade[TAMANHO_GRADE][TAMANHO_GRADE]) {
    int i, j;

    printf("\n    ");
    for (j = 0; j < TAMANHO_GRADE; j++) {
        printf(" %d  ", j);
    }
    printf("\n");

    for (i = 0; i < TAMANHO_GRADE; i++) {
        printf("%2d  ", i);

        for (j = 0; j < TAMANHO_GRADE; j++) {
            printf("| %c ", grade[i][j]);
        }
        printf("|\n    ");

        for (j = 0; j < TAMANHO_GRADE; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

void configurarTamanhosNavios(int tamanhos[TOTAL_NAVIOS]) {
    int i;

    tamanhos[0] = 4;
    tamanhos[1] = 3;
    tamanhos[2] = 1;
    tamanhos[3] = 1;
    tamanhos[4] = 1;

    for (i = 5; i < TOTAL_NAVIOS; i++) {
        tamanhos[i] = 2;
    }
}

int posicionarNavio(char grade[TAMANHO_GRADE][TAMANHO_GRADE], int linha, int coluna, int tamanho, char orientacao) {
    int i;

    if (orientacao != 'H' && orientacao != 'V') {
        return 0;
    }

    if (linha < 0 || linha >= TAMANHO_GRADE || coluna < 0 || coluna >= TAMANHO_GRADE) {
        return 0;
    }

    if (orientacao == 'H' && coluna + tamanho > TAMANHO_GRADE) {
        return 0;
    }
    if (orientacao == 'V' && linha + tamanho > TAMANHO_GRADE) {
        return 0;
    }

    for (i = 0; i < tamanho; i++) {
        if (orientacao == 'H' && grade[linha][coluna + i] != SIMBOLO_AGUA) {
            return 0;
        }
        if (orientacao == 'V' && grade[linha + i][coluna] != SIMBOLO_AGUA) {
            return 0;
        }
    }

    for (i = 0; i < tamanho; i++) {
        if (orientacao == 'H') {
            grade[linha][coluna + i] = SIMBOLO_NAVIO;
        } else {
            grade[linha + i][coluna] = SIMBOLO_NAVIO;
        }
    }

    return 1;
}

void posicionarFrota(char grade[TAMANHO_GRADE][TAMANHO_GRADE], int tamanhos[TOTAL_NAVIOS], int idJogador) {
    int i, linha, coluna, posValida;
    char orientacao;

    for (i = 0; i < TOTAL_NAVIOS; i++) {
        posValida = 0;

        while (posValida == 0) {
            printf("\nJogador %d - Navio %d de %d\n", idJogador, i + 1, TOTAL_NAVIOS);
            printf("Tamanho do navio: %d\n", tamanhos[i]);

            printf("Linha inicial (0 a 9): ");
            scanf("%d", &linha);

            printf("Coluna inicial (0 a 9): ");
            scanf("%d", &coluna);

            printf("Orientacao (H = Horizontal, V = Vertical): ");
            scanf(" %c", &orientacao);

            orientacao = toupper(orientacao);

            posValida = posicionarNavio(grade, linha, coluna, tamanhos[i], orientacao);

            if (posValida == 0) {
                printf("\nPosicionamento invalido! Verifique limites ou sobreposicoes.\n");
            }
        }

        printf("\nEstado atual da sua grade:\n");
        imprimirGrade(grade);
    }
}

int efetuarDisparo(char gradeAdversario[TAMANHO_GRADE][TAMANHO_GRADE], char gradeAtaques[TAMANHO_GRADE][TAMANHO_GRADE], int linha, int coluna) {
    if (linha < 0 || linha >= TAMANHO_GRADE || coluna < 0 || coluna >= TAMANHO_GRADE) {
        printf("Coordenadas fora dos limites!\n");
        return 0;
    }

    if (gradeAtaques[linha][coluna] == SIMBOLO_ACERTO || gradeAtaques[linha][coluna] == SIMBOLO_ERRO) {
        printf("Ja efetuou um disparo nesta posicao anteriormente!\n");
        return 0;
    }

    if (gradeAdversario[linha][coluna] == SIMBOLO_NAVIO) {
        printf("\n>>> ACERTOU UM NAVIO! <<<\n");
        gradeAdversario[linha][coluna] = SIMBOLO_ACERTO;
        gradeAtaques[linha][coluna] = SIMBOLO_ACERTO;
    } else {
        printf("\n>>> TIRO NA AGUA! <<<\n");
        gradeAdversario[linha][coluna] = SIMBOLO_ERRO;
        gradeAtaques[linha][coluna] = SIMBOLO_ERRO;
    }

    return 1;
}

int verificarVitoria(char grade[TAMANHO_GRADE][TAMANHO_GRADE]) {
    int i, j;
    for (i = 0; i < TAMANHO_GRADE; i++) {
        for (j = 0; j < TAMANHO_GRADE; j++) {
            if (grade[i][j] == SIMBOLO_NAVIO) {
                return 0; // Ainda há navios inteiros/não atingidos
            }
        }
    }
    return 1; // Todos os navios foram destruídos
}

int executarTurno(int idJogador, char gradePropria[TAMANHO_GRADE][TAMANHO_GRADE], char gradeAtaques[TAMANHO_GRADE][TAMANHO_GRADE], char gradeAdversario[TAMANHO_GRADE][TAMANHO_GRADE]) {
    int linha, coluna;
    int tiroValido = 0;

    while (tiroValido == 0) {
        printf("\n================================\n");
        printf("          TURNO DO JOGADOR %d\n", idJogador);
        printf("================================\n");

        printf("\nA sua grade:\n");
        imprimirGrade(gradePropria);

        printf("\nO seu registro de ataques:\n");
        imprimirGrade(gradeAtaques);

        printf("\nEscolha as coordenadas do disparo:\n");
        printf("Linha (0 a 9): ");
        scanf("%d", &linha);

        printf("Coluna (0 a 9): ");
        scanf("%d", &coluna);

        tiroValido = efetuarDisparo(gradeAdversario, gradeAtaques, linha, coluna);
    }

    return verificarVitoria(gradeAdversario);
}