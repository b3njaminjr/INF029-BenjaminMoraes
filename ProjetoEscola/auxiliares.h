#ifndef AUXILIARES_H
#define AUXILIARES_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

void limparBuffer(void);
void lerTexto(char *str, int tamanho);
int validarData(Data d);
int validarCpf(const char *cpf);
char validarSexo(void);
void formatarNome(char *nome);
void formatarSemestre(); //ideia de novaDisciplina.semestre ser uma string e precisar ser formatada

#endif