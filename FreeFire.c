#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define as constantes
#define MAX_TAM1 30
#define MAX_TAM2 20

// estrutura de um nó da lista
typedef struct No
{
    char nome[MAX_TAM1];
    char tipo[MAX_TAM2];
    int quantidades;
    int prioridade;
    struct No *proximo;
} No;

// implementações
void limparBufferEntrada();
void adicionarComponente(No **mochila);
void descartarComponente(No **mochila);
void listarComponentes(No *mochila);
void ordenarMochila(No **mochila, int *ordenadaPorNome);
void buscaBinaria(No *mochila);

int main()
{
    No *mochila = NULL;
    int resp;
    int ordenadaPorNome = 0;

    do
    {
        printf("\n---- MOCHILA ----\n");
        printf("1 - Adicionar componete\n");
        printf("2 - Descartar componete\n");
        printf("3 - Listar componentes (inventario)\n");
        printf("4 - Organizar mochila (ordernar)\n");
        printf("5 - Busca binaria por componente-chave (nome)\n");
        printf("0 - Ativar torre de fuga (sair)\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &resp);
        limparBufferEntrada();

        switch (resp)
        {
        case 0:
            printf("\nSaindo do programa...\n");
            break;
        case 1:
            adicionarComponente(&mochila);
            break;
        case 2:
            descartarComponente(&mochila);
            break;
        case 3:
            listarComponentes(mochila);
            break;
        case 4:
            ordenarMochila(&mochila, &ordenadaPorNome);
            break;
        case 5:
        if(ordenadaPorNome == 0) {
            printf("Para realizar a busca binaria os componentes devem estar ordenadas por ordem alfabetica!\n");
            continue;
        }
            buscaBinaria(mochila);
            break;
        default:
            printf("\nOpcao invalida!\n");
            break;
        }
    } while (resp != 0);

    // libera a memória alocada
    No *aux;
    while (mochila != NULL)
    {
        aux = mochila;
        mochila = mochila->proximo;
        free(aux);
    }

    return 0;
}

// ------------------- FUNÇÕES -------------------

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void adicionarComponente(No **mochila)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    printf("Qual nome do componente? ");
    fgets(novo->nome, MAX_TAM1, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Qual tipo do componente? (estrutural, eletronico, energia) ");
    fgets(novo->tipo, MAX_TAM2, stdin);
    novo->tipo[strcspn(novo->tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->quantidades);
    limparBufferEntrada();

    printf("Prioridade: ");
    scanf("%d", &novo->prioridade);
    limparBufferEntrada();

    novo->proximo = *mochila; // insere no início da lista
    *mochila = novo;

    printf("\nComponente adicionado com sucesso!\n");
}

void descartarComponente(No **mochila)
{
    if (*mochila == NULL)
    {
        printf("\nNao ha componentes para remover!\n");
        return;
    }

    char nome[MAX_TAM1];
    printf("Qual nome do componente que deseja remover? ");
    fgets(nome, MAX_TAM1, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *mochila;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("\ncomponente %s nao encontrado!\n", nome);
        return;
    }

    if (anterior == NULL)
    {
        *mochila = atual->proximo; // remove o primeiro
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("\ncomponente %s removido com sucesso!\n", nome);
}

void listarComponentes(No *mochila)
{
    if (mochila == NULL)
    {
        printf("\nNao ha componentes para listar!\n");
        return;
    }

    printf("\nCOMPONENTES NA MOCHILA:\n");
    int i = 1;
    while (mochila != NULL)
    {
        printf("\nCOMPONENTE #%d:\n", i++);
        printf("NOME: %s\n", mochila->nome);
        printf("TIPO: %s\n", mochila->tipo);
        printf("QUANTIDADE: %d\n", mochila->quantidades);
        printf("PRIORIDADE: %d\n", mochila->prioridade);
        mochila = mochila->proximo;
    }
}

void ordenarMochila(No **mochila, int *ordenadaPorNome)
{
    int resp = 0;
    int trocou;
    No *atual;
    No *ultimo = NULL;

    printf("\nComo deseja ordenar os componentes?\n");
    printf("1 - Por nome (ordem alfabetica)\n");
    printf("2 - Por tipo\n");
    printf("3 - Por prioridade (maior -> menor)\n");
    printf("0 - Cancelar\n");

    printf("\nEscolha uma opcao: ");
    scanf("%d", &resp);
    limparBufferEntrada();

    if (*mochila == NULL || (*mochila)->proximo == NULL)
    {
        printf("\nNao ha itens suficientes para ordenar!\n");
        return;
    }

    switch (resp)
    {
    case 0:
        printf("\nCancelando...\n");
        return;

    case 1: // Ordenar por NOME (A-Z)
        do
        {
            trocou = 0;
            atual = *mochila;

            while (atual->proximo != ultimo)
            {
                if (strcmp(atual->nome, atual->proximo->nome) > 0)
                {
                    char tempNome[MAX_TAM1];
                    char tempTipo[MAX_TAM2];
                    int tempQuant;
                    int tempPrio;

                    strcpy(tempNome, atual->nome);
                    strcpy(tempTipo, atual->tipo);
                    tempQuant = atual->quantidades;
                    tempPrio = atual->prioridade;

                    strcpy(atual->nome, atual->proximo->nome);
                    strcpy(atual->tipo, atual->proximo->tipo);
                    atual->quantidades = atual->proximo->quantidades;
                    atual->prioridade = atual->proximo->prioridade;

                    strcpy(atual->proximo->nome, tempNome);
                    strcpy(atual->proximo->tipo, tempTipo);
                    atual->proximo->quantidades = tempQuant;
                    atual->proximo->prioridade = tempPrio;

                    trocou = 1;
                }
                atual = atual->proximo;
            }
            ultimo = atual;
        } while (trocou);
        printf("\nMochila ordenada por NOME (A-Z)!\n");
        listarComponentes(*mochila);
        *ordenadaPorNome = 1;
        break;

    case 2: // Ordenar por TIPO
        do
        {
            trocou = 0;
            atual = *mochila;

            while (atual->proximo != ultimo)
            {
                if (strcmp(atual->tipo, atual->proximo->tipo) > 0)
                {
                    char tempNome[MAX_TAM1];
                    char tempTipo[MAX_TAM2];
                    int tempQuant;
                    int tempPrio;

                    strcpy(tempNome, atual->nome);
                    strcpy(tempTipo, atual->tipo);
                    tempQuant = atual->quantidades;
                    tempPrio = atual->prioridade;

                    strcpy(atual->nome, atual->proximo->nome);
                    strcpy(atual->tipo, atual->proximo->tipo);
                    atual->quantidades = atual->proximo->quantidades;
                    atual->prioridade = atual->proximo->prioridade;

                    strcpy(atual->proximo->nome, tempNome);
                    strcpy(atual->proximo->tipo, tempTipo);
                    atual->proximo->quantidades = tempQuant;
                    atual->proximo->prioridade = tempPrio;

                    trocou = 1;
                }
                atual = atual->proximo;
            }
            ultimo = atual;
        } while (trocou);
        printf("\nMochila ordenada por TIPO!\n");
        listarComponentes(*mochila);
        break;

    case 3: // Ordenar por PRIORIDADE (maior -> menor)
        do
        {
            trocou = 0;
            atual = *mochila;

            while (atual->proximo != ultimo)
            {
                if (atual->prioridade < atual->proximo->prioridade)
                {
                    char tempNome[MAX_TAM1];
                    char tempTipo[MAX_TAM2];
                    int tempQuant;
                    int tempPrio;

                    strcpy(tempNome, atual->nome);
                    strcpy(tempTipo, atual->tipo);
                    tempQuant = atual->quantidades;
                    tempPrio = atual->prioridade;

                    strcpy(atual->nome, atual->proximo->nome);
                    strcpy(atual->tipo, atual->proximo->tipo);
                    atual->quantidades = atual->proximo->quantidades;
                    atual->prioridade = atual->proximo->prioridade;

                    strcpy(atual->proximo->nome, tempNome);
                    strcpy(atual->proximo->tipo, tempTipo);
                    atual->proximo->quantidades = tempQuant;
                    atual->proximo->prioridade = tempPrio;

                    trocou = 1;
                }
                atual = atual->proximo;
            }
            ultimo = atual;
        } while (trocou);
        printf("\nMochila ordenada por PRIORIDADE (maior -> menor)!\n");
        listarComponentes(*mochila);
        break;

    default:
        printf("\nOpcao invalida!\n");
        break;
    }
}

void buscaBinaria(No *mochila)
{
    if (mochila == NULL)
    {
        printf("\nNao ha componentes na mochila!\n");
        return;
    }

    // Conta quantos elementos há na lista
    int tamanho = 0;
    No *atual = mochila;
    while (atual != NULL)
    {
        tamanho++;
        atual = atual->proximo;
    }

    // Cria um vetor de ponteiros para os nós
    No **vetor = (No **)malloc(tamanho * sizeof(No *));
    if (vetor == NULL)
    {
        printf("Erro ao alocar memoria para busca!\n");
        return;
    }

    // Preenche o vetor com os ponteiros da lista
    atual = mochila;
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = atual;
        atual = atual->proximo;
    }

    // Entrada do nome a ser buscado
    char nomeBusca[MAX_TAM1];
    printf("\nDigite o nome do componente que deseja buscar: ");
    fgets(nomeBusca, MAX_TAM1, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Implementa a busca binária
    int inicio = 0, fim = tamanho - 1, meio;
    int encontrado = 0;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        int cmp = strcmp(nomeBusca, vetor[meio]->nome);
        if (cmp == 0)
        {
            printf("\nComponente encontrado!\n");
            printf("NOME: %s\n", vetor[meio]->nome);
            printf("TIPO: %s\n", vetor[meio]->tipo);
            printf("QUANTIDADE: %d\n", vetor[meio]->quantidades);
            printf("PRIORIDADE: %d\n", vetor[meio]->prioridade);
            encontrado = 1;
            break;
        }
        else if (cmp < 0)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    if (!encontrado)
    {
        printf("\nComponente '%s' nao encontrado na mochila.\n", nomeBusca);
    }
    free(vetor);
}
