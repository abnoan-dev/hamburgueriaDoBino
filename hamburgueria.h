#ifndef HAMBURGUERIA_H
#define HAMBURGUERIA_H

#define MAX_USERS 10
#define MAX_ITEMS 100
#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

typedef struct {
    char nome[MAX_LENGTH];
    float preco;
    int quantidade;
} Item;

void salvarUsuarios(User users[], int numUsers);
int carregarUsuarios(User users[]);
void salvarItens(Item items[], int numItems);
int carregarItens(Item items[]);
void boasVindas();
void menu();
void cadastrarUsuario(User users[], int *numUsers);
int buscarCliente(User users[], int numUsers, char *username);
void listarCardapio(Item items[], int numItems);
void adicionarAoCarrinho(Item cardapio[], int numItems, Item carrinho[], int *numCarrinho);
void excluirPedido(Item carrinho[], int *numCarrinho);
void visualizarCarrinho(Item carrinho[], int numCarrinho);
void editarPedido(Item cardapio[], int numCardapio, Item carrinho[], int *numCarrinho);

#endif /* HAMBURGUERIA_H */