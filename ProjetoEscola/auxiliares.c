#include "auxiliares.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 1. Limpeza do Buffer de Entrada
void limparBuffer(void) {
    int c; // Usar int para garantir a comparação correta com EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

// 2. Leitura Segura de Texto (evita Buffer Overflow e remove o '\n')
void lerTexto(char *str, int tamanho) {
    if (fgets(str, tamanho, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0'; // Remove o caractere de nova linha
        } else {
            limparBuffer(); // Limpa o excesso caso o usuário ultrapasse o limite
        }
    }
}

// 3. Leitura Segura de Inteiros (Retorna 1 para SUCESSO, 0 para ERRO)
int lerInt(int *n) {
    if (scanf("%d", n) != 1) {
        limparBuffer(); // Corrigido de limpar_buffer para limparBuffer
        return 0; // Falha
    }
    limparBuffer(); // Garante a remoção do \n residual
    return 1; // Sucesso
}

// 4. Validação de Data (Bissexto + limites)
int validarData(Data d) {
    if (d.ano < 1900 || d.ano > 2026) return 0;
    if (d.mes < 1 || d.mes > 12) return 0;

    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajuste para ano bissexto
    if ((d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0)) {
        diasNoMes[1] = 29;
    }

    if (d.dia < 1 || d.dia > diasNoMes[d.mes - 1]) return 0;

    return 1; // Data válida
}

// 5. Formatação do Nome (Primeira letra Maiúscula, demais Minúsculas)
void formatarNome(char nome[]) {
    int deixarMaiusculo = 1;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isspace((unsigned char)nome[i])) {
            deixarMaiusculo = 1;
        } else if (deixarMaiusculo) {
            nome[i] = (char)toupper((unsigned char)nome[i]);
            deixarMaiusculo = 0;
        } else {
            nome[i] = (char)tolower((unsigned char)nome[i]);
        }
    }
}

// 6. Validação do Sexo (M / F)
char validarSexo(void) {
    char sexo;
    do {
        scanf(" %c", &sexo);
        limparBuffer();
        sexo = (char)toupper((unsigned char)sexo);
        if (sexo != 'M' && sexo != 'F') {
            printf("Opcao invalida! Digite 'M' para Masculino ou 'F' para Feminino: ");
        }
    } while (sexo != 'M' && sexo != 'F');

    return sexo;
}

// 7. Validação do CPF (Tamanho de 11 dígitos numéricos)
int validarCpf(const char *cpf) {
    int tam = strlen(cpf);
    if (tam != 11) return 0;

    for (int i = 0; i < tam; i++) {
        // Corrigido operador && para ||
        if (cpf[i] < '0' || cpf[i] > '9') return 0; 
    }
    return 1;
}