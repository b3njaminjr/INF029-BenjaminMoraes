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

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

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

// 5. Função Principal Q1
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
    int tamBusca = strlen(strBusca);

    if (tamBusca == 0) return 0; 

    for(int i = 0; strTexto[i] != '\0'; i++) {
        int contem = 1;
        for(int j = 0; strBusca[j] != '\0' && contem; j++) {
            if(strTexto[i + j] != strBusca[j]) {
                contem = 0;
            }
        }
        if(contem) {
            posicoes[qtdOcorrencias * 2] = i + 1;
            posicoes[qtdOcorrencias * 2 + 1] = i + tamBusca;
            qtdOcorrencias++;
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

 int q7(char matriz[8][10], char palavra[5])
 {
     int achou = 0;
     return achou;
 }



DataQuebrada quebraData(char data[]){
    DataQuebrada dq;
    char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
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
