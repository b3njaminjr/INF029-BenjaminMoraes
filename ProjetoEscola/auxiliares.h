#ifndef AUXILIARES_H
#define AUXILIARES_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

void limparBuffer(void);
void lerTexto(char *str, int tamanho);
int lerInt(int *num);
int lerData(Data *data);
int validarData(Data d);
void formatarNome(char nome[]);
char validarSexo(void);
int validarCpf(const char *cpf);
int validarSemestre(const char *semestre);

#endif