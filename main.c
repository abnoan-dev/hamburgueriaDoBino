#include "hamburgueria.h"
#include <stdio.h>

int main() {
    UserNode* headUsuarios = NULL;
    ItemNode* cardapio = NULL;
    ItemNode* carrinho = NULL;
     ItemNode* itens = NULL;
    int numUsuarios = 0;
    int numCarrinho = 0;
    int opcao;

       // Adicionando hamburgueres ao cardápio
    Item novoItem1 = {"X-Bacon", 15.0, 50};
    Item novoItem2 = {"X-Salada", 12.0, 40};
    Item novoItem3 = {"X-Tudo", 18.0, 30};
    Item novoItem4 = {"Vegetariano", 13.0, 35};
    Item novoItem5 = {"Cheeseburger", 10.0, 45};

    adicionarItem(&itens, novoItem1);
    adicionarItem(&itens, novoItem2);
    adicionarItem(&itens, novoItem3);
    adicionarItem(&itens, novoItem4);
    adicionarItem(&itens, novoItem5);


    carregarUsuarios(&headUsuarios);
    carregarItens(&cardapio);
    boasVindas();

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarUsuario(&headUsuarios, &numUsuarios);
                break;
            case 2: {
                char username[MAX_LENGTH];
                printf("Digite o nome de usuário a ser buscado: ");
                scanf("%s", username);
                buscarCliente(headUsuarios, username);
                break;
            }
            case 3:
                listarCardapio(cardapio);
                break;
            case 4:
                adicionarAoCarrinho(cardapio, &carrinho, &numCarrinho);
                break;
            case 5:
                excluirPedido(&carrinho, &numCarrinho);
                break;
            case 6:
                visualizarCarrinho(carrinho);
                break;
            case 7:
                editarPedido(cardapio, &carrinho, &numCarrinho);
                break;
             case 8:
                ordenarUsuariosAlfabeticamente(&headUsuarios);
                salvarUsuarios(headUsuarios);
                printf("Usuários ordenados em ordem alfabética e salvos no arquivo.\n");
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 9);

    salvarUsuarios(headUsuarios);
    salvarItens(cardapio);
    escreverCarrinhoEmArquivo(carrinho);

    return 0;
}