#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define as constantes
#define MAX_TAM1 30
#define MAX_TAM2 20
#define QTE_ITENS 10

// defina a estrutura de um item
typedef struct
{
    char nome[MAX_TAM1];
    char tipo[MAX_TAM2];
    int quantidades;
} Item;

// funcoes a serem chamadas
void limparBufferEntrada();
void adicionarItem(Item *mochila, int *quant);
void removerItem(Item *mochila, int *quant);
void listarItens(Item *mochila, int *quant);
void buscarItem(Item *mochila, int *quant);

int main()
{
    // declara um vetor que ira conter itens e cont para contar quantos itens a mochila possui
    Item mochila[QTE_ITENS];
    int cont = 0;
    int resp;

    do
    {

        printf("MOCHILA [%d/%d]: \n", cont, QTE_ITENS);
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("5 - Sair\n");

        printf("\nEscolha alguma acao para sua mochila: ");
        scanf("%d", &resp);
        limparBufferEntrada();
        
        if (resp > 5 || resp < 0)
        {
            printf("Programa encerrado, opcao invalida!\n");
            break;
        }

        switch (resp)
        {
        case 1:
            adicionarItem(mochila, &cont);
            break;
        case 2:
            removerItem(mochila, &cont);
            break;
        case 3:
            listarItens(mochila, &cont);
            break;
        case 4:
            buscarItem(mochila, &cont);
            break;
        default:
            printf("opcao indisponivel");
            break;
        }
    } while (resp != 5);
    return 0;
}

// Implementacao das funcoes
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void adicionarItem(Item *mochila, int *quant)
{
    Item *item;

    if (*quant == QTE_ITENS)
    {
        printf("\nSua mochila esta cheia, impossivel adicionar novo item\n");
        return;
    }
    printf("Qual nome do item? ");
    fgets(mochila[*quant].nome, MAX_TAM1, stdin);
    mochila[*quant].nome[strcspn(mochila[*quant].nome, "\n")] = '\0'; // remove \n

    printf("Qual tipo do item? ");
    fgets(mochila[*quant].tipo, MAX_TAM2, stdin);
    mochila[*quant].tipo[strcspn(mochila[*quant].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*quant].quantidades);
    limparBufferEntrada();

    (*quant)++;

    printf("\nItem adicionado com sucesso!\n\n");
}

void removerItem(Item *mochila, int *quant)
{
    char nome[MAX_TAM1];
    int pos = -1;

    if (*quant == 0)
    {
        printf("\nNão ha itens para remover!\n");
        return;
    }
    printf("Qual nome do item que deseja remover? ");
    fgets(nome, MAX_TAM1, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *quant; i++)
    {
        if (strcmp(mochila[i].nome, nome) == 0)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        printf("\nItem %s nao encontrado na lista\n", nome);
        return;
    }

    for (int i = pos; i < *quant - 1; i++)
    {
        mochila[i] = mochila[i + 1];
    }

    (*quant)--;

    printf("\nItem %s removido com sucesso.\n", nome);
}

void listarItens(Item *mochila, int *quant)
{
    if (*quant == 0)
    {
        printf("Nao ha itens para ser listados\n");
        return;
    }

    printf("\nITENS NA MOCHILA:\n");
    for (int i = 0; i < *quant; i++)
    {
        printf("\nITEM #%d:\n", i + 1);
        printf("NOME: %s\n", mochila[i].nome);
        printf("TIPO: %s\n", mochila[i].tipo);
        printf("QUANTIDADE: %d\n", mochila[i].quantidades);
    }
}

void buscarItem(Item *mochila, int *quant)
{
    char nome[MAX_TAM1];
    int pos = -1;

    if (*quant == 0)
    {
        printf("Não há itens na lista!\n");
        return;
    }
    printf("Qual nome do item que deseja buscar? ");
    fgets(nome, MAX_TAM1, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *quant; i++)
    {
        if (strcmp(mochila[i].nome, nome) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Item não encontrado!\n");
        return;
    }

    printf("\nITEM BUSCADO:\n");
    printf("NOME: %s\n", mochila[pos].nome);
    printf("TIPO: %s\n", mochila[pos].tipo);
    printf("QUANTIDADE: %d\n", mochila[pos].quantidades);
}