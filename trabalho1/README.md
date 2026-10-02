# 🛠️ Trabalho 1 — Lógica de Programação e Jogos em C

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Curso](https://img.shields.io/badge/Curso-ADS%20IFBA-green.svg)
![Disciplina](https://img.shields.io/badge/Disciplina-INF029%20Laboratório%20de%20Programação-orange.svg)

Este repositório contém a resolução do **Trabalho Prático 1** da disciplina **INF029 — Laboratório de Programação** do curso de **Análise e Desenvolvimento de Sistemas (ADS)** no Instituto Federal da Bahia (IFBA), sob a orientação do Prof. Renato Novais.

```

---

## 📌 Visão Geral

O objetivo principal desta atividade é aplicar conceitos essenciais de lógica de programação utilizando a **Linguagem C**, contemplando validação de dados, manipulação de strings/matrizes, algoritmos matemáticos e criação de jogos interativos em ambiente CLI (Interface de Linha de Comando).

---

## 📋 Estrutura das Questões

O trabalho é composto por 9 questões divididas entre funções de teste automatizado (usando a estrutura do `corretor.c`) e programas independentes com interação com o utilizador:

### 🧩 Módulo de Funções e Testes (Q1 a Q7)

* **Q1 — Validação de Data:** Função que verifica a validade de datas no formato `dd/mm/aaaa` (e variações curtas), considerando anos bissextos.
* **Q2 — Diferença entre Datas:** Algoritmo para calcular a diferença exata em anos, meses e dias entre duas datas (ex.: data de nascimento e data atual), sem utilizar bibliotecas prontas de datas.
* **Q3 — Contagem de Caracteres:** Função que conta a ocorrência de uma letra num texto (até 250 caracteres), ignorando acentuações nas vogais (ex.: `'á'` equivale a `'a'`).
* **Q4 — Busca de Palavras:** Localização de uma palavra num texto, retornando as posições iniciais e finais de todas as suas ocorrências.
* **Q5 — Inversão de Números:** Função que inverte a ordem dos dígitos de um número inteiro $N$ (ex.: $456 \rightarrow 654$).
* **Q6 — Ocorrência de Números:** Algoritmo que identifica quantas vezes um número $K$ de qualquer quantidade de dígitos ocorre num número natural $N$.
* **Q7 — Caça-Palavras:** Função para procurar uma string dentro de uma matriz de caracteres em todos os sentidos possíveis (horizontal, vertical e diagonais — para a frente e para trás).

---

### 🎮 Jogos Interativos (Q8 e Q9)

#### ❌⭕ Q8 — Jogo da Velha

* Interface gráfica em modo texto com tabuleiro $3 \times 3$ (linhas A-C e colunas 1-3).
* Suporte para 2 jogadores alternados (`X` e `O`).
* Validação de jogadas e verificação automática de vitória ou empate.

#### 🚢 Q9 — Batalha Naval

* Tabuleiro $10 \times 10$ para cada jogador.
* Posicionamento estratégico de frota configurável (barcos de tamanhos 1 a 4).
* Representação gráfica do mapa em tempo real:
* `[ ]` Espaço em branco (mar)
* `[N]` Navio posicionado (visível apenas ao dono)
* `[0]` Tiro certeiro (navio atingido)
* `[X]` Tiro na água (inválido/agualado)


* Alternância de turnos até um dos jogadores afundar toda a frota adversária.

---

## 📁 Estrutura do Repositório

```
.
├── BenjaminMoraes-2026100000-T1.c     # Implementação das questões Q1 a Q7
├── BenjaminMoraes-2026100000-Q8.c     # Programa do Jogo da Velha
├── BenjaminMoraes-2026100000-Q9.c     # Programa da Batalha Naval
├── aluno2.h                            # Cabeçalho dos testes das funções
└── corretor.c                          # Script principal de testes das funções Q1-Q7

```

---

## ⚙️ Como Compilar e Executar

### Pré-requisitos

* Compilador **GCC** instalado (`gcc --version`).

### 1. Testar as Questões Q1 a Q7 (com o `corretor.c`)

```bash
gcc corretor.c BenjaminMoraes-2026100000-T1.c -o teste_t1 -Wall
./teste_t1

```

### 2. Executar o Jogo da Velha (Q8)

```bash
gcc BenjaminMoraes-2026100000-Q8.c -o jogo_da_velha -Wall
./jogo_da_velha

```

### 3. Executar a Batalha Naval (Q9)

```bash
gcc BenjaminMoraes-2026100000-Q9.c -o batalha_naval -Wall
./batalha_naval

```

---

## 👤 Autor

* **Estudante:** Benjamin Moraes do Carmo Júnior
* **Curso:** Análise e Desenvolvimento de Sistemas (ADS) — IFBA
* **Disciplina:** INF029 — Laboratório de Programação
* **Docente:** Prof. Renato Novais

```

```