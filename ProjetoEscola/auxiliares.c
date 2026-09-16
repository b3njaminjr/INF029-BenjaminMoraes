#include "auxiliares.h"
#include <stdio.h>
#include <string.h>
#include "aluno.h"


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Limpa o buffer de entrada
    }
}

void lerTexto(char *texto){
    scanf(" %[^\n]", texto);
}


// validacoes 
int validarData(Data d) {
    if(d.ano < 1900 || d.ano > 2026) return 0;
    if(d.mes < 1 || d.mes > 12) return 0;

    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(d.ano % 4 == 0 && (d.ano % 100 != 0 || d.ano % 400 == 0)) {
        diasNoMes[1] = 29; // Ano bissexto
    }

    if(d.dia < 1 || d.dia > diasNoMes[d.mes - 1]) return 0;

    return 1; // Data válida
}

void formatarNome(char nome[]) {
    int tam = strlen(nome);
    if(tam > 0 && nome[tam - 1] == '\n') {
            nome[tam - 1] = '\0'; 
    }

    int deixarMaisculo = 1;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isspace(nome[i])) {
            deixarMaisculo = 1;
        } else if (deixarMaisculo) {
            nome[i] = toupper(nome[i]);
            deixarMaisculo = 0;
        } else {
            nome[i] = tolower(nome[i]);
        }
    }
}

char validarSexo(char sexo) {
    do {
        printf("Digite o novo sexo (M/F): ");
        scanf(" %c", &sexo);
        sexo = toupper(sexo);
        if(sexo != 'M' && sexo != 'F')
            printf("Opcao invalida! Digite 'M' para (masculino) e 'F' para (feminino)");
        limparBuffer();
    } while(sexo != 'M' && sexo != 'F');

    return sexo;
}

int validarCpf(char *cpf) {
    int tam = strlen(cpf);
    if(tam != 11) return 0;
    for(int i = 0; i < tam; i++) {
        if(cpf[i] < '0' && cpf[i] > '9') return 0;
    }
    return 1;
}
