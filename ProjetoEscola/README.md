# Sistema de Gestão Escolar — Linguagem C

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Course](https://img.shields.io/badge/Curso-ADS%20IFBA-green.svg)
![Subject](https://img.shields.io/badge/Disciplina-INF029%20Laboratório%20de%20Programação-orange.svg)

Sistema modular de Gestão Escolar desenvolvido em **Linguagem C** como requisito da disciplina **INF029 — Laboratório de Programação** do curso de **Análise e Desenvolvimento de Sistemas (ADS)** no Instituto Federal da Bahia (IFBA), sob orientação do Prof. Renato Novais.

```

---

## 📌 Visão Geral

O projeto consiste numa aplicação em modo terminal estruturada para gerir cadastros de alunos, professores e disciplinas, bem como as matrículas e relatórios gerenciais da instituição.

A arquitetura do software adota técnicas de **modularização**, garantindo o reuso de código, isolamento de responsabilidades e tratamento de dados com exclusão lógica (*soft delete*) e validações rigorosas.

---

## 🚀 Funcionalidades

### 🎓 Módulo de Alunos

* **Cadastro Completo:** Inclusão de alunos salvando Matrícula, Nome, Sexo, Data de Nascimento e CPF.
* **Atualização e Exclusão:** Alteração de dados cadastrais e exclusão lógica (*soft delete*).
* **Listagem Básica:** Exibição detalhada de todos os alunos ativos.

### 👨‍🏫 Módulo de Professores

* **Cadastro Completo:** Inclusão de professores salvando Matrícula, Nome, Sexo, Data de Nascimento e CPF.
* **Atualização e Exclusão:** Edição de cadastro e desativação.
* **Validação de Integridade:** Impede a exclusão de professores vinculados a disciplinas ativas.

### 📚 Módulo de Disciplinas & Matrículas

* **Gestão de Disciplinas:** Cadastro, atualização e exclusão de disciplinas (Código, Nome, Semestre, Professor Responsável e Vagas Totais).
* **Matrícula de Alunos:** Inserção e remoção de alunos em turmas.
* **Controle de Vagas:** Validação em tempo real para evitar exceder o limite de vagas disponíveis.

### 📊 Módulo de Relatórios

* **Listagens de Alunos:**
* Alunos cadastrados.
* Alunos filtrados por sexo (Masculino / Feminino).
* Alunos ordenados alfabeticamente por Nome.
* Alunos ordenados por Data de Nascimento.
* Alunos matriculados em menos de 3 disciplinas.


* **Listagens de Professores:**
* Professores cadastrados.
* Professores filtrados por sexo.
* Professores ordenados por Nome.
* Professores ordenados por Data de Nascimento.


* **Listagens de Disciplinas:**
* Disciplinas cadastradas (dados gerais).
* Consulta detalhada de uma disciplina com alunos matriculados.
* Disciplinas que extrapolam 40 vagas (exibindo o nome do professor responsável).


* **Consultas Gerais:**
* Aniversariantes do mês (filtrado por mês informado).
* Busca de pessoas (Alunos/Professores) por substring do nome (mínimo 3 caracteres).



---

## 📁 Estrutura de Arquivos

```
.
├── main.c           # Ponto de entrada do programa e fluxo principal dos menus
├── aluno.h          # Protótipos e estrutura do módulo de Alunos
├── aluno.c          # Implementação das regras de negócio do módulo de Alunos
├── professor.h      # Protótipos e estrutura do módulo de Professores
├── professor.c      # Implementação das regras de negócio do módulo de Professores
├── disciplina.h     # Protótipos e estrutura do módulo de Disciplinas
├── disciplina.c     # Implementação das disciplinas e controle de matrículas
├── relatorios.h     # Protótipos das funções de relatórios e ordenações
├── relatorios.c     # Implementação dos filtros e algoritmos de ordenação
├── auxiliares.h     # Protótipos de utilitários (validação de datas, CPF e buffers)
└── auxiliares.c     # Leitura segura de entradas via fgets, formatadores e validações

```

---

## 🛠️ Requisitos e Validações Implementadas

* **Validação de CPF:** Verificação de tamanho correto (11 dígitos numéricos).
* **Validação de Datas:** Checagem de dias por mês (considerando anos bissextos) e limites de ano.
* **Validação de Entradas:** Uso de `fgets` combinado com `sscanf` para prevenir travamentos de *buffer* do `scanf`.
* **Tratamento de Maiúsculas e Minúsculas:** Normalização automática de nomes para o formato de título.
* **Integridade de Dados:** Exclusão lógica para prevenir acessos indevidos e corrupção de referências entre vetores.

---

## ⚙️ Como Compilar e Executar

### Pré-requisitos

* Compilador **GCC** instalado (`gcc --version`).

### 1. Clonar o repositório

```bash
git clone [https://github.com/seu-usuario/nome-do-repositorio.git](https://github.com/seu-usuario/nome-do-repositorio.git)
cd nome-do-repositorio

```

### 2. Compilação

No terminal, execute o seguinte comando para compilar todos os módulos:

```bash
gcc main.c aluno.c professor.c disciplina.c relatorios.c auxiliares.c -o escola -Wall -Wextra

```

*Ou utilizando o caractere coringa:*

```bash
gcc *.c -o escola -Wall -Wextra

```

### 3. Execução

* **Linux / macOS:**
```bash
./escola

```


* **Windows (CMD / PowerShell):**
```cmd
escola.exe

```



---

## 👤 Autor

* **Estudante:** Benjamin Moraes do Carmo Júnior
* **Curso:** Análise e Desenvolvimento de Sistemas (ADS) — IFBA
* **Disciplina:** INF029 — Laboratório de Programação
* **Docente:** Prof. Renato Novais

```

```