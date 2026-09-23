#include "auxiliares.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerTexto(char *str, int tamanho) {
    if (fgets(str, tamanho, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        } else {
            limparBuffer();
        }
    }
}

int lerInt(int *num) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%d", num) == 1) {
            return 1;
        }
    }
    return 0;
}

int lerData(Data *data) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%d/%d/%d", &data->dia, &data->mes, &data->ano) == 3) {
            return 1;
        }
    }
    return 0;
}

int validarData(Data data) {
    if (data.ano < 1900 || data.ano > 2100) return 0;
    if (data.mes < 1 || data.mes > 12) return 0;

    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((data.ano % 4 == 0 && data.ano % 100 != 0) || (data.ano % 400 == 0)) {
        diasNoMes[1] = 29;
    }

    if (data.dia < 1 || data.dia > diasNoMes[data.mes - 1]) return 0;

    return 1;
}

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

char validarSexo(void) {
    char sexo;
    char buffer[100];
    do {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, " %c", &sexo) == 1) {
                sexo = (char)toupper((unsigned char)sexo);
                if (sexo == 'M' || sexo == 'F') {
                    return sexo;
                }
            }
        }
        printf("Opcao invalida! Digite 'M' para Masculino ou 'F' para Feminino: ");
    } while (1);
}

int validarCpf(const char *cpf) {
    int tam = strlen(cpf);
    if (tam != 11) return 0;
    for (int i = 0; i < tam; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }
    return 1;
}

int validarSemestre(const char *semestre) {
    int ano, sem;
    if (sscanf(semestre, "%d.%d", &ano, &sem) == 2) {
        if (ano >= 1900 && ano <= 2100 && (sem == 1 || sem == 2)) {
            return 1;
        }
    }
    return 0;
}