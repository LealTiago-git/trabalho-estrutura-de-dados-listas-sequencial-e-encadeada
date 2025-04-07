#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 60

typedef struct NoDisciplina
{
    char nome[50];
    struct NoDisciplina *proximo;
} NoDisciplina;

typedef struct Aluno
{
    int rgm;
    char nome[50];
    NoDisciplina *disciplinas;
} Aluno;

Aluno alunos[MAX_ALUNOS];

int totalAlunos = 0;

void adicionarDisciplina(NoDisciplina **lista, char nome[])
{
    NoDisciplina *novoNo = (NoDisciplina *)malloc(sizeof(NoDisciplina));
    if (!novoNo)
    {
        printf("Erro ao alocar memória para disciplina.\n");
        return;
    }
    strcpy(novoNo->nome, nome);
    novoNo->proximo = *lista;
    *lista = novoNo;
}

void listarDisciplinas(NoDisciplina *lista)
{
    if (lista == NULL)
    {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }
    printf("Disciplinas: ");
    while (lista != NULL)
    {
        printf("%s", lista->nome);
        lista = lista->proximo;
        if (lista != NULL)
            printf(", ");
    }
    printf("\n");
}

void liberarDisciplinas(NoDisciplina **lista)
{
    NoDisciplina *atual = *lista;
    while (atual != NULL)
    {
        NoDisciplina *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *lista = NULL;
}

int buscarAlunoPorRGM(int rgm)
{
    for (int i = 0; i < totalAlunos; i++)
    {
        if (alunos[i].rgm == rgm)
            return i;
    }
    return -1;
}

int inserirAlunoOrdenado(Aluno novo)
{
    if (totalAlunos >= MAX_ALUNOS)
    {
        printf("Limite máximo de alunos atingido.\n");
        return 0;
    }

    if (buscarAlunoPorRGM(novo.rgm) != -1)
    {
        printf("Erro: RGM já cadastrado.\n");
        return 0;
    }

    int posicao = totalAlunos - 1;
    while (posicao >= 0 && alunos[posicao].rgm > novo.rgm)
    {
        alunos[posicao + 1] = alunos[posicao];
        posicao--;
    }

    alunos[posicao + 1] = novo;
    alunos[posicao + 1].disciplinas = NULL;
    totalAlunos++;

    printf("Aluno cadastrado com sucesso.\n");
    return 1;
}

int removerAlunoPorRGM(int rgm)
{
    int indice = buscarAlunoPorRGM(rgm);
    if (indice == -1)
    {
        printf("Aluno não encontrado.\n");
        return 0;
    }

    liberarDisciplinas(&alunos[indice].disciplinas);

    for (int i = indice; i < totalAlunos - 1; i++)
    {
        alunos[i] = alunos[i + 1];
    }

    totalAlunos--;
    printf("Aluno removido com sucesso.\n");
    return 1;
}

void listarTodosAlunos()
{
    if (totalAlunos == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\nLista de Alunos:\n");
    for (int i = 0; i < totalAlunos; i++)
    {
        printf("\n%dº Aluno:\n", i + 1);
        printf("Nome: %s\n", alunos[i].nome);
        printf("RGM: %d\n", alunos[i].rgm);
        listarDisciplinas(alunos[i].disciplinas);
    }
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    int opcao = -1;

    do
    {
        printf("\nMENU PRINCIPAL\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Adicionar disciplina a aluno\n");
        printf("3 - Buscar aluno por RGM\n");
        printf("4 - Listar todos os alunos\n");
        printf("5 - Remover aluno\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada inválida! Digite apenas números.\n");
            limparBuffer();
            opcao = -1;
            continue;
        }
        limparBuffer();

        switch (opcao)
        {
        case 1:
        {
            Aluno novo;
            printf("\nNome do aluno: ");
            fgets(novo.nome, 50, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';

            printf("RGM do aluno: ");
            scanf("%d", &novo.rgm);
            limparBuffer();

            int cadastroSucesso = inserirAlunoOrdenado(novo);

            if (cadastroSucesso)
            {
                char resposta;
                do
                {
                    printf("\nAdicionar disciplina para este aluno? (S/N): ");
                    scanf("%c", &resposta);
                    limparBuffer();

                    if (resposta == 'S' || resposta == 's')
                    {
                        char nomeDisciplina[50];
                        printf("Nome da disciplina: ");
                        fgets(nomeDisciplina, 50, stdin);
                        nomeDisciplina[strcspn(nomeDisciplina, "\n")] = '\0';

                        int indice = buscarAlunoPorRGM(novo.rgm);
                        adicionarDisciplina(&alunos[indice].disciplinas, nomeDisciplina);
                        printf("Disciplina adicionada com sucesso.\n");
                    }
                } while (resposta == 'S' || resposta == 's');
            }
            break;
        }

        case 2:
        {
            int rgm;
            printf("\nDigite o RGM do aluno: ");
            scanf("%d", &rgm);
            limparBuffer();

            int indice = buscarAlunoPorRGM(rgm);
            if (indice == -1)
            {
                printf("Aluno não encontrado.\n");
            }
            else
            {
                char nomeDisciplina[50];
                printf("Nome da disciplina: ");
                fgets(nomeDisciplina, 50, stdin);
                nomeDisciplina[strcspn(nomeDisciplina, "\n")] = '\0';

                adicionarDisciplina(&alunos[indice].disciplinas, nomeDisciplina);
                printf("Disciplina adicionada com sucesso.\n");
            }
            break;
        }

        case 3:
        {
            int rgm;
            printf("\nDigite o RGM para busca: ");
            scanf("%d", &rgm);
            limparBuffer();

            int indice = buscarAlunoPorRGM(rgm);
            if (indice == -1)
            {
                printf("Aluno não encontrado.\n");
            }
            else
            {
                printf("\nAluno encontrado:\n");
                printf("Nome: %s\n", alunos[indice].nome);
                printf("RGM: %d\n", alunos[indice].rgm);
                listarDisciplinas(alunos[indice].disciplinas);
            }
            break;
        }

        case 4:
            listarTodosAlunos();
            break;

        case 5:
        {
            int rgm;
            printf("\nDigite o RGM para remoção: ");
            scanf("%d", &rgm);
            limparBuffer();

            int resultado = removerAlunoPorRGM(rgm);
            if (resultado)
            {
                listarTodosAlunos();
            }
            break;
        }

        case 0:
            printf("Encerrando programa...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < totalAlunos; i++)
    {
        liberarDisciplinas(&alunos[i].disciplinas);
    }

    return 0;
}