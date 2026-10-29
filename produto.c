#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "produto.h"
#include "util.h"

int cadastrarProduto(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias)
{
    int codigo;
    int codigoCategoria;
    int posCat;

    if (totalProdutos >= MAX_PRODUTOS)
    {
        printf("\nA lista de produtos esta cheia. Nao e possivel cadastrar mais produtos.\n");
        return totalProdutos;
    }

    printf("\n========== CADASTRO DE PRODUTO ==========\n");

    do
    {
        printf("Digite o codigo do produto: ");
        scanf("%d", &codigo);

        if (!inteiroPositivo(codigo))
        {
            printf("Codigo invalido. Digite um codigo maior que zero.\n");
        }
        else if (buscarPorCodigo(produtos, totalProdutos, codigo) != -1)
        {
            printf("Esse codigo ja esta cadastrado. Digite outro codigo.\n");
            codigo = -1;
        }

    } while (!inteiroPositivo(codigo));

    produtos[totalProdutos].codigo = codigo;

    getchar();

    do
    {
        printf("Digite o nome do produto: ");
        fgets(produtos[totalProdutos].nome, 50, stdin);

        produtos[totalProdutos].nome[
            strcspn(produtos[totalProdutos].nome, "\n")
        ] = '\0';

        if (!textoPreenchido(produtos[totalProdutos].nome))
        {
            printf("Nome invalido.\n");
        }

    } while (!textoPreenchido(produtos[totalProdutos].nome));

    do
    {
        printf("Digite a prateleira (A, B, C ou D): ");
        scanf(" %c", &produtos[totalProdutos].prateleira);

        produtos[totalProdutos].prateleira =
            toupper((unsigned char)produtos[totalProdutos].prateleira);

        if (produtos[totalProdutos].prateleira != 'A' &&
            produtos[totalProdutos].prateleira != 'B' &&
            produtos[totalProdutos].prateleira != 'C' &&
            produtos[totalProdutos].prateleira != 'D')
        {
            printf("Prateleira invalida.\n");
        }

    } while (produtos[totalProdutos].prateleira != 'A' &&
             produtos[totalProdutos].prateleira != 'B' &&
             produtos[totalProdutos].prateleira != 'C' &&
             produtos[totalProdutos].prateleira != 'D');

    do
    {
        printf("Digite o preco unitario: ");
        scanf("%f", &produtos[totalProdutos].preco);

        if (!numeroRealPositivo(produtos[totalProdutos].preco))
        {
            printf("Preco invalido.\n");
        }

    } while (!numeroRealPositivo(produtos[totalProdutos].preco));

    do
    {
        printf("Digite a quantidade em estoque: ");
        scanf("%d", &produtos[totalProdutos].quantidade);

        if (!quantidadeValida(produtos[totalProdutos].quantidade))
        {
            printf("Quantidade invalida.\n");
        }

    } while (!quantidadeValida(produtos[totalProdutos].quantidade));

    printf("\nCategorias disponiveis:\n");
    listarCategorias(categorias, totalCategorias);

    do
    {
        printf("Digite o codigo da categoria do produto: ");
        scanf("%d", &codigoCategoria);

        posCat = buscarCategoriaPorCodigo(categorias, totalCategorias, codigoCategoria);

        if (posCat == -1)
        {
            printf("Categoria nao encontrada. Digite um codigo valido.\n");
        }

    } while (posCat == -1);

    produtos[totalProdutos].codigoCategoria = codigoCategoria;

    if (produtos[totalProdutos].quantidade > 0)
    {
        produtos[totalProdutos].disponivel = 1;
    }
    else
    {
        produtos[totalProdutos].disponivel = 0;
    }

    printf("\n========== PRODUTO CADASTRADO ==========\n");
    exibirProduto(produtos[totalProdutos], categorias, totalCategorias);

    return totalProdutos + 1;
}

void listarProdutos(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias)
{
    int i;

    printf("\n========== LISTA DE PRODUTOS ==========\n");

    if (totalProdutos == 0)
    {
        printf("Nenhum produto foi cadastrado.\n");
        return;
    }

    for (i = 0; i < totalProdutos; i++)
    {
        printf("\nProduto %d de %d\n", i + 1, totalProdutos);
        exibirProduto(produtos[i], categorias, totalCategorias);
    }
}

void exibirProduto(struct Produto produto, struct Categoria categorias[], int totalCategorias)
{
    int posCat;

    printf("----------------------------\n");
    printf("Codigo: %d\n", produto.codigo);
    printf("Nome: %s\n", produto.nome);
    printf("Prateleira: %c\n", produto.prateleira);
    printf("Preco unitario: R$ %.2f\n", produto.preco);
    printf("Quantidade em estoque: %d\n", produto.quantidade);

    posCat = buscarCategoriaPorCodigo(categorias, totalCategorias, produto.codigoCategoria);
    if (posCat != -1)
    {
        printf("Categoria: %s\n", categorias[posCat].nome);
    }
    else
    {
        printf("Categoria: Desconhecida\n");
    }

    if (produto.disponivel == 1)
    {
        printf("Disponivel para venda: Sim\n");
    }
    else
    {
        printf("Disponivel para venda: Nao\n");
    }

    printf("----------------------------\n");
}

int buscarPorCodigo(struct Produto produtos[], int total, int codigo)
{
    int i;

    for (i = 0; i < total; i++)
    {
        if (produtos[i].codigo == codigo)
        {
            return i;
        }
    }

    return -1;
}

int buscarPorNome(struct Produto produtos[], int total, char nome[])
{
    int i;

    for (i = 0; i < total; i++)
    {
        if (strcmp(produtos[i].nome, nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

void pesquisarProduto(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias)
{
    int subopcao;
    int codigo;
    int posicao;
    char nome[50];

    printf("\n========== PESQUISAR PRODUTO ==========\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
    printf("Digite uma opcao: ");
    scanf("%d", &subopcao);

    if (subopcao == 1)
    {
        do
        {
            printf("Digite o codigo do produto: ");
            scanf("%d", &codigo);

            if (!inteiroPositivo(codigo))
            {
                printf("Codigo invalido.\n");
            }

        } while (!inteiroPositivo(codigo));

        posicao = buscarPorCodigo(produtos, totalProdutos, codigo);

        if (posicao != -1)
        {
            exibirProduto(produtos[posicao], categorias, totalCategorias);
        }
        else
        {
            printf("\nNenhum produto foi encontrado.\n");
        }
    }
    else if (subopcao == 2)
    {
        getchar();

        do
        {
            printf("Digite o nome do produto: ");
            fgets(nome, sizeof(nome), stdin);

            nome[strcspn(nome, "\n")] = '\0';

            if (!textoPreenchido(nome))
            {
                printf("Nome invalido.\n");
            }

        } while (!textoPreenchido(nome));

        posicao = buscarPorNome(produtos, totalProdutos, nome);

        if (posicao != -1)
        {
            exibirProduto(produtos[posicao], categorias, totalCategorias);
        }
        else
        {
            printf("\nNenhum produto foi encontrado.\n");
        }
    }
    else
    {
        printf("\nOpcao de pesquisa invalida.\n");
    }
}

int cadastrarCategoria(struct Categoria categorias[], int totalCategorias)
{
    int codigo;

    if (totalCategorias >= MAX_CATEGORIAS)
    {
        printf("\nA lista de categorias esta cheia. Nao e possivel cadastrar mais categorias.\n");
        return totalCategorias;
    }

    printf("\n========== CADASTRO DE CATEGORIA ==========\n");

    do
    {
        printf("Digite o codigo da categoria: ");
        scanf("%d", &codigo);

        if (!inteiroPositivo(codigo))
        {
            printf("Codigo invalido. Digite um codigo maior que zero.\n");
        }
        else if (buscarCategoriaPorCodigo(categorias, totalCategorias, codigo) != -1)
        {
            printf("Esse codigo ja esta cadastrado. Digite outro codigo.\n");
            codigo = -1;
        }

    } while (!inteiroPositivo(codigo));

    categorias[totalCategorias].codigo = codigo;

    getchar();

    do
    {
        printf("Digite o nome da categoria: ");
        fgets(categorias[totalCategorias].nome, 30, stdin);

        categorias[totalCategorias].nome[
            strcspn(categorias[totalCategorias].nome, "\n")
        ] = '\0';

        if (!textoPreenchido(categorias[totalCategorias].nome))
        {
            printf("Nome invalido.\n");
        }

    } while (!textoPreenchido(categorias[totalCategorias].nome));

    printf("\nCategoria cadastrada com sucesso!\n");

    return totalCategorias + 1;
}

void listarCategorias(struct Categoria categorias[], int totalCategorias)
{
    int i;

    printf("\n========== LISTA DE CATEGORIAS ==========\n");

    if (totalCategorias == 0)
    {
        printf("Nenhuma categoria foi cadastrada.\n");
        return;
    }

    for (i = 0; i < totalCategorias; i++)
    {
        printf("Codigo: %d | Nome: %s\n", categorias[i].codigo, categorias[i].nome);
    }
}

int buscarCategoriaPorCodigo(struct Categoria categorias[], int totalCategorias, int codigo)
{
    int i;

    for (i = 0; i < totalCategorias; i++)
    {
        if (categorias[i].codigo == codigo)
        {
            return i;
        }
    }

    return -1;
}

int carregarCategorias(struct Categoria categorias[])
{
    FILE *arq = fopen("categorias.txt", "r");
    int total = 0;

    if (arq == NULL)
    {
        return 0;
    }

    while (fscanf(arq, "%d;%29[^\n]\n", &categorias[total].codigo, categorias[total].nome) == 2)
    {
        total++;
    }

    fclose(arq);
    return total;
}

void salvarCategorias(struct Categoria categorias[], int totalCategorias)
{
    FILE *arq = fopen("categorias.txt", "w");
    int i;

    if (arq == NULL)
    {
        return;
    }

    for (i = 0; i < totalCategorias; i++)
    {
        fprintf(arq, "%d;%s\n", categorias[i].codigo, categorias[i].nome);
    }

    fclose(arq);
}

int carregarProdutos(struct Produto produtos[])
{
    FILE *arq = fopen("produtos.txt", "r");
    int total = 0;

    if (arq == NULL)
    {
        return 0;
    }

    while (fscanf(arq, "%d;%49[^;];%c;%f;%d;%d;%d\n",
                  &produtos[total].codigo,
                  produtos[total].nome,
                  &produtos[total].prateleira,
                  &produtos[total].preco,
                  &produtos[total].quantidade,
                  &produtos[total].disponivel,
                  &produtos[total].codigoCategoria) == 7)
    {
        total++;
    }

    fclose(arq);
    return total;
}

void salvarProdutos(struct Produto produtos[], int totalProdutos)
{
    FILE *arq = fopen("produtos.txt", "w");
    int i;

    if (arq == NULL)
    {
        return;
    }

    for (i = 0; i < totalProdutos; i++)
    {
        fprintf(arq, "%d;%s;%c;%.2f;%d;%d;%d\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].prateleira,
                produtos[i].preco,
                produtos[i].quantidade,
                produtos[i].disponivel,
                produtos[i].codigoCategoria);
    }

    fclose(arq);
}
