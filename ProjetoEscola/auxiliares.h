#ifndef AUXILIARES_H
#define AUXILIARES_H
#include "aluno.h"
#include "auxiliares.c"

void limparBuffer();
void lerTexto(char *texto);
int validarData(Data d);
void formatarNome(char nome[]);
char validarSexo();
int validarCpf(char *cpf);

#endif // AUXILIARES_H