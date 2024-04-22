#include <stdio.h>
#include <string.h>
#include "hamburgueria.h"

int main() {
    User users[MAX_USERS];
    int numUsers = 0;
    Item cardapio[MAX_ITEMS];
    int numCardapio = 0;
    Item carrinho[MAX_ITEMS];
    int numCarrinho = 0;
    int opcao;
    
    // Adicionando hamburgueres ao cardápio
    strcpy(cardapio[numCardapio].nome, "X-Bacon");
    cardapio[numCardapio].preco = 15.0;
    cardapio[numCardapio].quantidade = 50;
    numCardapio++;

    strcpy(cardapio[numCardapio].nome, "X-Salada");
    cardapio[numCardapio].preco = 12.0;
    cardapio[numCardapio].quantidade = 40;
    numCardapio++;

    strcpy(cardapio[numCardapio].nome, "X-Tudo");
    cardapio[numCardapio].preco = 18.0;
    cardapio[numCardapio].quantidade = 30;
    numCardapio++;

    strcpy(cardapio[numCardapio].nome, "Vegetariano");
    cardapio[numCardapio].preco = 13.0;
    cardapio[numCardapio].quantidade = 35;
    numCardapio++;

    strcpy(cardapio[numCardapio].nome, "Cheeseburger");
    cardapio[numCardapio].preco = 10.0;
    cardapio[numCardapio].quantidade = 45;
    numCardapio++;

    // Carregar usuários do arquivo
    numUsers = carregarUsuarios(users);

    // Boas-vindas
    boasVindas();

    // Loop do menu
    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarUsuario(users, &numUsers);
                break;
            case 2: {
                char username[MAX_LENGTH];
                printf("Digite o nome de usuario para buscar: ");
                scanf("%s", username);
                buscarCliente(users, numUsers, username);
                break;
            }
            case 3:
                listarCardapio(cardapio, numCardapio);
                break;
            case 4:
                adicionarAoCarrinho(cardapio, numCardapio, carrinho, &numCarrinho);
                break;
            case 5:
                excluirPedido(carrinho, &numCarrinho);
                break;
            case 6:
                visualizarCarrinho(carrinho, numCarrinho);
                break;
            case 7:
                editarPedido(cardapio, numCardapio, carrinho, &numCarrinho);
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao!= 8);

    // Salvar itens em arquivo
    salvarItens(cardapio, numCardapio);

    return 0;
}