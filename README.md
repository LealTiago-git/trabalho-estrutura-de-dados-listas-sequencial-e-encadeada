# Explicação do Código em C

## 1. Diretivas de Pré-processamento e Constantes

```c
#include <stdio.h>    // Para funções de entrada/saída (printf, scanf, fgets)
#include <stdlib.h>   // Para alocação dinâmica (malloc, free)
#include <string.h>   // Para manipulação de strings (strcpy, strcspn)
#define MAX_ALUNOS 60 // Capacidade máxima da lista de alunos
```

**Propósito:**

- Inclui bibliotecas essenciais para operações básicas de E/S, gerenciamento de memória e manipulação de strings.
- Define o tamanho máximo da lista sequencial de alunos (`MAX_ALUNOS = 60`).

## 2. Definição de Estruturas

### 2.1 Estrutura `NoDisciplina` (Lista Encadeada)

```c
typedef struct NoDisciplina {
    char nome[50];              
    struct NoDisciplina *proximo; 
} NoDisciplina;
```

**Propósito:** Representa uma disciplina em uma lista encadeada.

**Campos:**

- `nome[50]`: Armazena o nome da disciplina.
- `proximo`: Ponteiro para o próximo nó da lista.

### 2.2 Estrutura `Aluno` (Lista Sequencial)

```c
typedef struct {
    int rgm;                   
    char nome[50];             
    NoDisciplina *disciplinas; 
} Aluno;
```

**Propósito:** Armazena dados de um aluno.

**Campos:**

- `rgm`: Número único de identificação.
- `nome[50]`: Nome do aluno.
- `disciplinas`: Ponteiro para a lista encadeada de disciplinas.

## 3. Variáveis Globais

```c
Aluno alunos[MAX_ALUNOS];
int totalAlunos = 0;
```

**Propósito:**

- `alunos`: Array para armazenar alunos.
- `totalAlunos`: Contador de alunos cadastrados.

## 4. Funções de Manipulação de Disciplinas

### 4.1 `adicionarDisciplina`

```c
void adicionarDisciplina(NoDisciplina **lista, char nome[]) {
    NoDisciplina *novoNo = (NoDisciplina *)malloc(sizeof(NoDisciplina));
    if (!novoNo) {
        printf("Erro ao alocar memória para disciplina.\n");
        return;
    }
    strcpy(novoNo->nome, nome);
    novoNo->proximo = *lista;
    *lista = novoNo;
}
```

**Passo a Passo:**

1. Aloca memória para um novo nó.
2. Verifica a alocação.
3. Copia o nome da disciplina.
4. Encadeia o novo nó.
5. Atualiza o início da lista.

### 4.2 `listarDisciplinas`

```c
void listarDisciplinas(NoDisciplina *lista) {
    if (lista == NULL) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }
    printf("Disciplinas: ");
    while (lista != NULL) {
        printf("%s", lista->nome);
        lista = lista->proximo;
        if (lista != NULL) printf(", ");
    }
    printf("\n");
}
```

**Funcionamento:**

- Verifica se a lista está vazia.
- Imprime os nomes das disciplinas.

### 4.3 `liberarDisciplinas`

```c
void liberarDisciplinas(NoDisciplina **lista) {
    NoDisciplina *atual = *lista;
    while (atual != NULL) {
        NoDisciplina *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *lista = NULL;
}
```

**Propósito:** Libera toda a memória alocada para disciplinas.

## 5. Funções de Gerenciamento de Alunos

### 5.1 `buscarAlunoPorRGM`

```c
int buscarAlunoPorRGM(int rgm) {
    for (int i = 0; i < totalAlunos; i++) {
        if (alunos[i].rgm == rgm) return i;
    }
    return -1;
}
```

### 5.2 `inserirAlunoOrdenado`

```c
int inserirAlunoOrdenado(Aluno novo) {
    if (totalAlunos >= MAX_ALUNOS) {
        printf("Limite máximo de alunos atingido.\n");
        return 0;
    }
    if (buscarAlunoPorRGM(novo.rgm) != -1) {
        printf("Erro: RGM já cadastrado.\n");
        return 0;
    }
    int posicao = totalAlunos - 1;
    while (posicao >= 0 && alunos[posicao].rgm > novo.rgm) {
        alunos[posicao + 1] = alunos[posicao];
        posicao--;
    }
    alunos[posicao + 1] = novo;
    alunos[posicao + 1].disciplinas = NULL;
    totalAlunos++;
    printf("Aluno cadastrado com sucesso.\n");
    return 1;
}
```

### 5.3 `removerAlunoPorRGM`

```c
int removerAlunoPorRGM(int rgm) {
    int indice = buscarAlunoPorRGM(rgm);
    if (indice == -1) {
        printf("Aluno não encontrado.\n");
        return 0;
    }
    liberarDisciplinas(&alunos[indice].disciplinas);
    for (int i = indice; i < totalAlunos - 1; i++) {
        alunos[i] = alunos[i + 1];
    }
    totalAlunos--;
    printf("Aluno removido com sucesso.\n");
    return 1;
}
```

## 6. Funções Auxiliares

### 6.1 `listarTodosAlunos`

```c
void listarTodosAlunos() {
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    printf("\nLista de Alunos:\n");
    for (int i = 0; i < totalAlunos; i++) {
        printf("\n%dº Aluno:\n", i + 1);
        printf("Nome: %s\n", alunos[i].nome);
        printf("RGM: %d\n", alunos[i].rgm);
        listarDisciplinas(alunos[i].disciplinas);
    }
}
```

### 6.2 `limparBuffer`

```c
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```

## 7. Função Principal (`main`)

Trecho principal do programa, exibindo menu, recebendo entradas e chamando funções.

## 8. Casos do Switch (Menu)

### Caso 1: Cadastrar Aluno

Código para cadastrar aluno, ler dados, verificar duplicidade e adicionar disciplinas.

## 9. Conceitos Chave

### 9.1 Lista Sequencial vs. Lista Encadeada

- **Lista Sequencial:** Acesso direto, mas requer deslocamentos.
- **Lista Encadeada:** Inserção rápida, acesso sequencial.

### 9.2 Gerenciamento de Memória

Uso de `malloc`/`free`, prevenção de vazamentos.

### 9.3 Tratamento de Entradas

- `limparBuffer` para entradas residuais.
- Validação de dados.

## 10. Diagrama de Fluxo

```
[Menu Principal]
       |
 +-----+-----+
 |           |
[Operações] [Sair]
 |     |     |     |
 Cadastrar, Adicionar, Listar, Remover
```
