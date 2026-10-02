# INF029 — Laboratório de Programação

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Institution](https://img.shields.io/badge/Instituição-IFBA-green.svg)
![Course](https://img.shields.io/badge/Curso-ADS%20(Análise%20e%20Desenvolvimento%20de%20Sistemas)-orange.svg)

Repositório destinado aos projetos, trabalhos práticos e exercícios desenvolvidos na disciplina **INF029 — Laboratório de Programação** do curso superior de Análise e Desenvolvimento de Sistemas (ADS) no Instituto Federal de Educação, Ciência e Tecnologia da Bahia (IFBA), sob orientação do Prof. Renato Novais.

```

---

## 📌 Sobre a Disciplina

A disciplina de **Laboratório de Programação** tem como foco aprofundar os conhecimentos em desenvolvimento de software utilizando a **Linguagem C**. O percurso formativo abrange desde o fortalecimento da lógica de programação e tratamento de cadeias de caracteres até conceitos avançados de modularização, manipulação direta de memória (ponteiros) e alocação dinâmica de dados.

### Principais Competências Desenvolvidas:

* **Modularização e Arquitetura de Software:** Divisão do código em arquivos `.c` e `.h`, garantindo acoplamento fraco e reutilização.
* **Validação de Dados e Tratamento de Erros:** Leitura segura via `fgets`, parse de strings, prevenção de *buffer overflows* e bugs de execução.
* **Estruturas de Dados e Algoritmos:** Manipulação de vetores, matrizes multidimensionais, ordenação, busca e estruturas de dados dinâmicas.
* **Gestão de Memória com Ponteiros:** Uso de alocação dinâmica (`malloc`, `realloc`, `free`) e vetores de ponteiros para estruturas auxiliares flexíveis.

---

## 🚀 Projetos e Trabalhos Práticos

### 1. Sistema de Gestão Escolar (Projeto Escola)

Desenvolvimento de uma aplicação modular em modo terminal para o gerenciamento de uma instituição de ensino.

* **Módulo Alunos:** Inclusão, atualização, listagem e exclusão lógica (*soft delete*) de alunos (Matrícula, Nome, Sexo, Data de Nascimento e CPF).
* **Módulo Professores:** Cadastro, edição e remoção de professores, com validação de integridade para impedir a exclusão de docentes vinculados a disciplinas ativas.
* **Módulo Disciplinas & Matrículas:** Cadastro de matérias (Código, Nome, Semestre, Professor Responsável e Vagas Totais), com controlo de matrícula/desmatrícula e limites de ocupação em tempo real.
* **Módulo de Relatórios Gerenciais:**
* Filtros de alunos e professores por sexo, ordenação alfabética e por data de nascimento.
* Consulta detalhada de turmas com alunos inscritos.
* Aniversariantes do mês e busca textual de pessoas por *substring* (mínimo de 3 caracteres).
* Relatórios específicos: alunos matriculados em menos de 3 disciplinas e turmas com mais de 40 vagas.



---

### 2. Trabalho 1 — Lógica de Programação, Matrizes e Jogos

Série de exercícios e algoritmos aplicados para consolidar a manipulação de strings, datas e jogos em terminal.

* **Q1 & Q2 — Algoritmo de Validação e Cálculo de Idade:** Validação de datas (incluindo anos bissextos) e cálculo da diferença em anos, meses e dias entre duas datas, sem o uso de funções prontas.
* **Q3 & Q4 — Processamento de Texto:** Contagem de frequência de caracteres (desconsiderando acentuação) e localização de posições iniciais e finais de palavras em textos.
* **Q5 & Q6 — Manipulação Numérica:** Funções para inversão de números inteiros e contagem de ocorrências de padrões numéricos dentro de outros números inteiros.
* **Q7 — Caça-Palavras:** Algoritmo de busca em matrizes de caracteres contemplando todas as direções (horizontal, vertical e diagonais diretas e inversas).
* **Q8 — Jogo da Velha:** Aplicação interativa para dois jogadores (`X` e `O`), com validação de jogadas por coordenadas de grelha e verificação automática de vitória ou empate.
* **Q9 — Batalha Naval:** Simulação completa de combate naval sobre matrizes $10 \times 10$, suporte a múltiplos barcos configuráveis globalmente (tamanhos 1, 2, 3 e 4), controlo de disparos e renderização de mapas restritos por jogador.

---

### 3. Trabalho 2 — Ponteiros e Alocação Dinâmica de Memória

Desenvolvimento de uma estrutura de dados customizada em memória utilizando vetores de ponteiros e estruturas auxiliares flexíveis.

* **Estrutura Principal:** Um vetor fixo de 10 posições onde cada elemento aponta para um vetor auxiliar dinâmico.
* **Alocação sob Demanda:** Criação dinâmica das estruturas auxiliares mediante solicitação do utilizador com o tamanho definido no momento da inserção.
* **Operações Disponíveis:**
1. Inserção de elementos individuais em posições específicas.
2. Exibição de todas as estruturas e respetivos conteúdos.
3. Ordenação interna dos elementos dentro de cada vetor auxiliar.
4. Ordenação global contendo todos os números registados no sistema.
5. Remoção do primeiro valor encontrado sem reduzir a capacidade do vetor.
6. Redimensionamento de estruturas auxiliares (`realloc`) para expansão do tamanho de posições disponíveis.



---

## 📁 Estrutura do Repositório

```
.
├── ProjetoEscola/
│   ├── main.c           # Ponto de entrada do sistema
│   ├── aluno.c / .h     # Módulo de gestão de alunos
│   ├── professor.c / .h # Módulo de gestão de professores
│   ├── disciplina.c / .h# Módulo de disciplinas e matrículas
│   ├── relatorios.c / .h# Gerador de relatórios e ordenação
│   └── auxiliares.c / .h# Leitura segura de buffers e validações
│
├── Trabalho1/
│   ├── NomeAluno-Matricula-T1.c # Resolução das questões Q1 a Q6
│   ├── NomeAluno-Matricula-Q8.c # Implementação do Jogo da Velha
│   └── NomeAluno-Matricula-Q9.c # Implementação da Batalha Naval
│
└── Trabalho2/
    └── main.c           # Gerenciador de estruturas auxiliares com ponteiros

```

---

## ⚙️ Como Compilar e Executar

### Pré-requisitos

* Compilador **GCC** instalado (`gcc --version`).

### Compilando o Projeto Escola

```bash
cd ProjetoEscola
gcc *.c -o escola -Wall -Wextra
./escola

```

### Compilando os Módulos do Trabalho 1

```bash
cd Trabalho1
# Para o programa de testes/questões base:
gcc NomeAluno-Matricula-T1.c corretor.c -o trabalho1 -Wall
./trabalho1

# Para os jogos isolados (Ex: Jogo da Velha):
gcc NomeAluno-Matricula-Q8.c -o jogo_da_velha -Wall
./jogo_da_velha

```

### Compilando o Trabalho 2 (Ponteiros)

```bash
cd Trabalho2
gcc main.c -o ponteiros -Wall -Wextra
./ponteiros

```

---

## 👤 Autor

* **Estudante:** Benjamin Moraes do Carmo Júnior
* **Curso:** Análise e Desenvolvimento de Sistemas (ADS) — IFBA
* **Disciplina:** INF029 — Laboratório de Programação
* **Orientador:** Prof. Renato Novais

```

```