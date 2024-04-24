#ifndef HAMBURGUERIA_H
#define HAMBURGUERIA_H

#define MAX_USERS 100
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

typedef struct UserNode {
    User user;
    struct UserNode* next;
} UserNode;

typedef struct ItemNode {
    Item item;
    struct ItemNode* next;
} ItemNode;

void adicionarUsuario(UserNode** head, User novoUsuario);
void adicionarItem(ItemNode** head, Item novoItem);
void salvarUsuarios(UserNode* head);
void escreverCarrinhoEmArquivo(ItemNode* carrinho);
void ordenarUsuariosAlfabeticamente(UserNode** head);
void carregarUsuarios(UserNode** head);
void salvarItens(ItemNode* head);
void carregarItens(ItemNode** head);
void boasVindas();
void menu();
void cadastrarUsuario(UserNode** head, int *numUsers);
int buscarCliente(UserNode* head, char *username);
void listarCardapio(ItemNode* head);
void adicionarAoCarrinho(ItemNode* cardapio, ItemNode** carrinho, int *numCarrinho);
void excluirPedido(ItemNode** carrinho, int *numCarrinho);
void visualizarCarrinho(ItemNode* carrinho);
void editarPedido(ItemNode* cardapio, ItemNode** carrinho, int *numCarrinho);

#endif /* HAMBURGUERIA_H */