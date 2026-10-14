// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: 
//  email: 
//  Matrícula: 
//  Semestre: 

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025
// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

// PROTÓTIPOS DAS FUNÇÕES AUXILIARES
int tamanhoString(char str[]);
int ehBissexto(int ano);
int mesValido(char data[], char mesCop[], int *pPosBarra1, int *pPosBarra2);
int anoValido(char data[], char anoCop[], int posBarra2, int *pAnoInt);
int diaValido(char data[], char diaCop[], int posBarra1, int mesInt, int anoInt);
DataQuebrada quebraData(char data[]);
int mHorizEsquerda(char matriz[8][10], char palavra[5], int lin, int col);
int mHorizDireita(char matriz[8][10], char palavra[5], int lin, int col);
int mVertCima(char matriz[8][10], char palavra[5], int lin, int col);
int mVertBaixo(char matriz[8][10], char palavra[5], int lin, int col);
int mDiagonalSupEsq(char matriz[8][10], char palavra[5], int lin, int col);
int mDiagonalSupDir(char matriz[8][10], char palavra[5], int lin, int col);
int mDiagonalInfEsq(char matriz[8][10], char palavra[5], int lin, int col);
int mDiagonalInfDir(char matriz[8][10], char palavra[5], int lin, int col);

// Funções de Teste Fornecidas
int somar(int x, int y) {
    int soma;
    soma = x + y;
    return soma;
}

int fatorial(int x) {
  int i, fat = 1;
  for (i = x; i > 1; i--)
    fat = fat * i;
  return fat;
}

int teste(int a) {
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;
    return val;
}

// IMPLEMENTAÇÃO DAS QUESTÕES (Q1 a Q7)

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
@restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
    char sDia[3];
    char sMes[3];
    char sAno[5];
    int posBarra1 = -1, posBarra2 = -1;
    int anoInt = 0, mesInt = 0;

    if(!mesValido(data, sMes, &posBarra1, &posBarra2)) {
        return 0;
    }

    if(strlen(sMes) == 1) {
        mesInt = sMes[0] - '0';
    } else {
        mesInt = (sMes[0] - '0') * 10 + (sMes[1] - '0');
    }

    if (!anoValido(data, sAno, posBarra2, &anoInt)) {
        return 0;
    }

    if(!diaValido(data, sDia, posBarra1, mesInt, anoInt)) {
        return 0;
    }
 
    return 1;
}

/*
 Q2 = diferença entre duas datas
@objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
@entrada
    uma string datainicial, uma string datafinal. 
@saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
    DiasMesesAnos dma;

    if (q1(datainicial) == 0) {
        dma.retorno = 2;
        return dma;
    } 
    else if (q1(datafinal) == 0) {
        dma.retorno = 3;
        return dma;
    } else {
        DataQuebrada dqIni = quebraData(datainicial);
        DataQuebrada dqFin = quebraData(datafinal);

        int anoInicial = dqIni.iAno;
        int mesInicial = dqIni.iMes;
        int diaInicial = dqIni.iDia;

        int aFinal = dqFin.iAno;
        int mFinal = dqFin.iMes;
        int diaFinal = dqFin.iDia;

        if (aFinal < anoInicial || 
           (aFinal == anoInicial && mFinal < mesInicial) || 
           (aFinal == anoInicial && mFinal == mesInicial && diaFinal < diaInicial)) {
            dma.retorno = 4;
            return dma;
        }

        int diasPorMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (diaFinal >= diaInicial) {
            dma.qtdDias = diaFinal - diaInicial;
        } else {
            int diasNoMesAnterior = diasPorMes[mesInicial];

            if (mesInicial == 2 && ehBissexto(anoInicial)) {
                diasNoMesAnterior = 29;
            }

            dma.qtdDias = (diaFinal + diasNoMesAnterior) - diaInicial;
            mFinal--;
        }

        if (mFinal >= mesInicial) {
            dma.qtdMeses = mFinal - mesInicial;
        } else {
            dma.qtdMeses = (mFinal + 12) - mesInicial;
            aFinal--;
        }

        dma.qtdAnos = aFinal - anoInicial;

        dma.retorno = 1;
        return dma;
    }
}

/*
 Q3 = encontrar caracter em texto
@objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
@entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
    Se isCaseSensitive != 1, a pesquisa não deve considerar diferenças entre maiúsculos e minúsculos.
@saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive) {
    int qtdOcorrencias = 0;

    if(isCaseSensitive == 1) {
        for(int i = 0; texto[i] != '\0'; i++) {
            if(texto[i] == c) {
                qtdOcorrencias++;
            }
        }
    } else {
        if(c >= 'A' && c <= 'Z') {
            c = c + 32;
        }
        for(int i = 0; texto[i] != '\0'; i++) {
            char temp = texto[i];
            if(temp >= 'A' && temp <= 'Z') {
                temp = temp + 32;
            }
            if(temp == c) {
                qtdOcorrencias++;
            }
        }
    }
    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
@objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
@entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
@saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30]) {
    int qtdOcorrencias = 0;
    int tamTexto = strlen(strTexto);
    int tamBusca = strlen(strBusca);

    if(tamTexto == 0 || tamBusca == 0) return 0;

    char novoTexto[tamTexto + 1];
    char novaBusca[tamBusca + 1];
    int map_orig[tamTexto + 1]; // Mapeia o índice limpo de volta para a posição real no strTexto

    // 1. Limpa o texto base e guarda o mapeamento dos índices originais
    int n = 0;
    for(int i = 0; i < tamTexto; i++) {
        if(strTexto[i] != -61) { 
            novoTexto[n] = strTexto[i];
            map_orig[n] = i;
            n++;
        }
    }
    novoTexto[n] = '\0';

    n = 0;
    for(int i = 0; i < tamBusca; i++) {
        if(strBusca[i] != -61) {
            novaBusca[n] = strBusca[i];
            n++;
        }
    }
    novaBusca[n] = '\0';

    int verifica_dois = 0;
    int tamBuscaLimpa = strlen(novaBusca);

    if (tamBuscaLimpa == 0) return 0;

    for(int i = 0; novoTexto[i] != '\0'; i++) {
        if(novoTexto[i] == novaBusca[0]) {
            int j = i + 1;
            int contem = 1;
            for(int k = 1; novaBusca[k] != '\0'; k++) {
                if(novoTexto[j] != novaBusca[k]){
                    contem = 0;
                    break;
                }
                j++;
            }
            
            if(contem == 1) {
                // Utiliza o map_orig para traduzir os índices de volta para o texto original (contando a partir de 1)
                posicoes[verifica_dois] = map_orig[i] + 1;                      // Início
                verifica_dois++;
                posicoes[verifica_dois] = map_orig[i + tamBuscaLimpa - 1] + 1; // Fim
                verifica_dois++;
                qtdOcorrencias++;
            }
        }
    }
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
@objetivo
    Inverter número inteiro
@entrada
    uma int num.
@saida
    Número invertido
 */
int q5(int num) {
    int invertido = 0;
    while(num != 0) {
        invertido = invertido * 10;
        invertido = invertido + (num % 10);
        num = num / 10;
    }
    return invertido;
}

/*
 Q6 = ocorrência de um número em outro
@objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
@entrada
    Um número base (numerobase) e um número de busca (numerobusca).
@saida
    Quantidade de vezes que número de busca ocorre em número base
 */
int q6(int numerobase, int numerobusca) {
    int qtdOcorrencias = 0;
    int qtdVezesBase = 0;
    int qtdeVezesBusca = 0;

    int tempBase = numerobase;
    int tempBusca = numerobusca;

    while (tempBase != 0) {
        qtdVezesBase++;
        tempBase /= 10;
    }

    while (tempBusca != 0) {
        qtdeVezesBusca++;
        tempBusca /= 10;
    }

    if (qtdeVezesBusca > qtdVezesBase || qtdeVezesBusca == 0) {
        return 0;
    }

    int numerobaseVet[qtdVezesBase];
    int numerobuscado[qtdeVezesBusca];

    tempBusca = numerobusca;
    for (int i = qtdeVezesBusca - 1; i >= 0; i--) {
        numerobuscado[i] = tempBusca % 10;
        tempBusca /= 10;
    }

    tempBase = numerobase;
    for (int i = qtdVezesBase - 1; i >= 0; i--) {
        numerobaseVet[i] = tempBase % 10;
        tempBase /= 10;
    }

    for (int i = 0; i <= qtdVezesBase - qtdeVezesBusca; i++) {
        int j;
        for (j = 0; j < qtdeVezesBusca; j++) {
            if (numerobaseVet[i + j] != numerobuscado[j]) {
                break;
            }
        }

        if (j == qtdeVezesBusca) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
@objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
@entrada
    Uma matriz de caracteres e uma string de busca (palavra).
@saida
    1 se achou 0 se não achou
 */
int q7(char matriz[8][10], char palavra[5]) {
    int achou = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 10; j++) {
            if(matriz[i][j] == palavra[0]) {
                if(mHorizEsquerda(matriz, palavra, i, j) ||
                   mHorizDireita(matriz, palavra, i, j) ||
                   mVertCima(matriz, palavra, i, j) ||
                   mVertBaixo(matriz, palavra, i, j) ||
                   mDiagonalSupEsq(matriz, palavra, i, j) ||
                   mDiagonalSupDir(matriz, palavra, i, j) ||
                   mDiagonalInfEsq(matriz, palavra, i, j) ||
                   mDiagonalInfDir(matriz, palavra, i, j)) {
                    achou = 1;
                    return achou;
                }
            }
        }
    }
    return achou;
}

// ==========================================
// IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES
// ==========================================

int tamanhoString(char str[]) {
    int tam = 0;
    while (str[tam] != '\0') {
        tam++;
    }
    return tam;
}

int ehBissexto(int ano) {
    if (ano < 100) {
        ano += 2000;
    }
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        return 1;
    }
    return 0;
}

int mesValido(char data[], char mesCop[], int *pPosBarra1, int *pPosBarra2) {
    int tamStr = 0;
    int p1 = -1, p2 = -1;

    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == '/') {
            if (p1 == -1) 
                p1 = i;
            else if (p2 == -1) { 
                p2 = i; 
                break; 
            }
        }
    }

    if (p1 == -1 || p2 == -1 || p2 <= p1 + 1) 
        return 0;

    *pPosBarra1 = p1;
    *pPosBarra2 = p2;

    for (int i = p1 + 1; i < p2; i++) {
        mesCop[tamStr++] = data[i];
    }
    mesCop[tamStr] = '\0';

    if (tamStr != 1 && tamStr != 2) 
        return 0;

    int mesInt = 0;
    if (tamStr == 1) {
        mesInt = mesCop[0] - '0';
    } else {
        mesInt = (mesCop[0] - '0') * 10 + (mesCop[1] - '0');
    }

    if (mesInt < 1 || mesInt > 12) return 0;

    return 1;
}

int anoValido(char data[], char anoCop[], int posBarra2, int *pAnoInt) {
    int tamStr = 0;

    for (int i = posBarra2 + 1; data[i] != '\0'; i++) {
        anoCop[tamStr++] = data[i];
    }
    anoCop[tamStr] = '\0';

    if (tamStr != 2 && tamStr != 4) return 0;

    for (int i = 0; i < tamStr; i++) {
        if (anoCop[i] < '0' || anoCop[i] > '9') return 0;
    }

    if (tamStr == 2) {
        *pAnoInt = (anoCop[0] - '0') * 10 + (anoCop[1] - '0');
    } else {
        *pAnoInt = (anoCop[0] - '0') * 1000 + (anoCop[1] - '0') * 100 +
                   (anoCop[2] - '0') * 10 + (anoCop[3] - '0');
    }

    return 1;
}

int diaValido(char data[], char diaCop[], int posBarra1, int mesInt, int anoInt) {
    int tamStr = 0;

    for (int i = 0; i < posBarra1; i++) {
        diaCop[tamStr++] = data[i];
    }
    diaCop[tamStr] = '\0';

    if (tamStr != 1 && tamStr != 2) return 0;

    for (int i = 0; i < tamStr; i++) {
        if (diaCop[i] < '0' || diaCop[i] > '9') return 0;
    }

    int diaInt = 0;
    if (tamStr == 1) {
        diaInt = diaCop[0] - '0';
    } else {
        diaInt = (diaCop[0] - '0') * 10 + (diaCop[1] - '0');
    }

    if (diaInt < 1) return 0;

    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mesInt == 2 && ehBissexto(anoInt)) {
        diasPorMes[2] = 29;
    }

    if (diaInt > diasPorMes[mesInt]) return 0;

    return 1;
}

DataQuebrada quebraData(char data[]) {
    DataQuebrada dq;
    char sDia[3];
    char sMes[3];
    char sAno[5];
    int i; 

    for (i = 0; data[i] != '/'; i++){
        sDia[i] = data[i];  
    }
    if(i == 1 || i == 2){ 
        sDia[i] = '\0';  
    }else {
        dq.valido = 0;
        return dq;
    }   

    int j = i + 1; 
    i = 0;

    for (; data[j] != '/'; j++){
        sMes[i] = data[j];
        i++;
    }

    if(i == 1 || i == 2){ 
        sMes[i] = '\0';  
    }else {
        dq.valido = 0;
        return dq;
    }

    j = j + 1; 
    i = 0;
    
    for(; data[j] != '\0'; j++){
        sAno[i] = data[j];
        i++;
    }

    if(i == 2 || i == 4){ 
        sAno[i] = '\0';  
    }else {
        dq.valido = 0;
        return dq;
    }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno); 

    dq.valido = 1;
    
    return dq;
}

int mHorizEsquerda(char matriz[8][10], char palavra[5], int lin, int col)  { // esta indo para esquerda
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (col - i < 0 || matriz[lin][col - i] != palavra[i]) {
            return 0;
        }
    }
    return 1;

}

int mHorizDireita(char matriz[8][10], char palavra[5], int lin, int col) { // esta indo para direita
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (col + i >= 10 || matriz[lin][col + i] != palavra[i]) {
            return 0;
        }
    }
    return 1;
}

int mVertCima(char matriz[8][10], char palavra[5], int lin, int col) { // esta indo para cima
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (lin - i < 0 || matriz[lin - i][col] != palavra[i]) {
            return 0;
        }
    }
    return 1;
}

int mVertBaixo(char matriz[8][10], char palavra[5], int lin, int col) { // esta indo para baixo
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (lin + i >= 8 || matriz[lin + i][col] != palavra[i]) {
            return 0;
        }
    }
    return 1;
}

int mDiagonalSupEsq(char matriz[8][10], char palavra[5], int lin, int col) { // esta indo para cima e para esquerda
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (lin - i < 0 || col - i < 0 || matriz[lin - i][col - i] != palavra[i]) {
            return 0;
        }
    }
    return 1;
}

int mDiagonalSupDir(char matriz[8][10], char palavra[5], int lin, int col) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (lin - i < 0 || col + i >= 10 || matriz[lin - i][col + i] != palavra[i]) {
            return 0;
        }
    }
    return 1;
}



int mDiagonalInfEsq(char matriz[8][10], char palavra[5], int lin, int col) { // esta indo para baixo e para esquerda
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (lin + i >= 10 || col - i < 0 || matriz[lin + i][col - i] != palavra[i]) {
            return 0;
        }
    }
    return 1;
}

int mDiagonalInfDir(char matriz[8][10], char palavra[5], int lin, int col) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (lin + i >= 10 || col + i >= 10 || matriz[lin + i][col + i] != palavra[i]) {
            return 0;
        }
    }
    return 1;
}


