#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 50
#define MAX_CATEGORIAS 20

struct Categoria
{
    int codigo;
    char nome[30];
};

struct Produto
{
    int codigo;
    char nome[50];
    char prateleira;
    float preco;
    int quantidade;
    int disponivel;
    int codigoCategoria;
};

int cadastrarProduto(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias);
void listarProdutos(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias);
void exibirProduto(struct Produto produto, struct Categoria categorias[], int totalCategorias);
int buscarPorCodigo(struct Produto produtos[], int total, int codigo);
int buscarPorNome(struct Produto produtos[], int total, char nome[]);
void pesquisarProduto(struct Produto produtos[], int totalProdutos, struct Categoria categorias[], int totalCategorias);

int cadastrarCategoria(struct Categoria categorias[], int totalCategorias);
void listarCategorias(struct Categoria categorias[], int totalCategorias);
int buscarCategoriaPorCodigo(struct Categoria categorias[], int totalCategorias, int codigo);

int carregarCategorias(struct Categoria categorias[]);
void salvarCategorias(struct Categoria categorias[], int totalCategorias);
int carregarProdutos(struct Produto produtos[]);
void salvarProdutos(struct Produto produtos[], int totalProdutos);

#endif
