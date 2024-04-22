#include "hamburgueria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void salvarUsuarios(User users[], int numUsers) {
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for (int i = 0; i < numUsers; i++) {
        fprintf(arquivo, "%s %s %s\n", users[i].username, users[i].password, users[i].email);
    }
    fclose(arquivo);
}

int carregarUsuarios(User users[]) {
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    int i = 0;
    while (fscanf(arquivo, "%s %s %s", users[i].username, users[i].password, users[i].email) != EOF) {
        i++;
    }
    fclose(arquivo);
    return i;
}

void salvarItens(Item items[], int numItems) {
    FILE *arquivo;
    arquivo = fopen("itens.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for (int i = 0; i < numItems; i++) {
        fprintf(arquivo, "%s %.2f %d\n", items[i].nome, items[i].preco, items[i].quantidade);
    }
    fclose(arquivo);
}

int carregarItens(Item items[]) {
    FILE *arquivo;
    arquivo = fopen("itens.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    int i = 0;
    while (fscanf(arquivo, "%s %f %d", items[i].nome, &items[i].preco, &items[i].quantidade) != EOF) {
        i++;
    }
    fclose(arquivo);
    return i;
}

void boasVindas() {
    printf("*********************************\n");
    printf("Bem-vindo a Hamburgueria do Bino!\n");
    printf("*********************************\n");
}

void menu() {
    printf("\n--------------------\n");
    printf("\nMenu de Opcoes:\n");
    printf("1. Cadastro de Usuario\n");
    printf("2. Buscar Cliente\n");
    printf("3. Ver Cardapio\n");
    printf("4. Realizar Pedido\n");
    printf("5. Excluir Pedido\n");
    printf("6. Visualizar Carrinho\n");
    printf("7. Editar Pedido\n");
    printf("8. Sair\n");
    printf("\n--------------------\n");
}

void cadastrarUsuario(User users[], int *numUsers) {
    if (*numUsers < MAX_USERS) {
        printf("Digite o nome de usuario: ");
        scanf("%s", users[*numUsers].username);
        printf("Digite a senha: ");
        scanf("%s", users[*numUsers].password);
        printf("Digite o email: ");
        scanf("%s", users[*numUsers].email);
        while (strstr(users[*numUsers].email, "@") == NULL) {
            printf("Email invalido. Digite novamente: ");
            scanf("%s", users[*numUsers].email);
        }
        (*numUsers)++;
        salvarUsuarios(users, *numUsers);
        printf("Cadastro realizado com sucesso!\n");
    } else {
        printf("Limite de usuarios atingido. Nao e possivel cadastrar mais.\n");
    }
}

int buscarCliente(User users[], int numUsers, char *username) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Cliente encontrado:\n");
            printf("Nome de usuario: %s\n", users[i].username);
            printf("Email: %s\n", users[i].email);
            return 1;
        }
    }
    printf("Cliente nao encontrado.\n");
    return 0;
}

void listarCardapio(Item items[], int numItems) {
    printf("Cardapio da Hamburgueria do Bino:\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d. %s - R$%.2f - Quantidade disponivel: %d\n", i+1, items[i].nome, items[i].preco, items[i].quantidade);
    }
}

void adicionarAoCarrinho(Item cardapio[], int numItems, Item carrinho[], int *numCarrinho) {
    int escolha, quantidade;
    printf("Digite o codigo do hamburguer que deseja adicionar ao carrinho: ");
    scanf("%d", &escolha);
    printf("Digite a quantidade desejada: ");
    scanf("%d", &quantidade);
    if (escolha >= 1 && escolha <= numItems && quantidade > 0) {
        if (quantidade <= cardapio[escolha - 1].quantidade) {
            strcpy(carrinho[*numCarrinho].nome, cardapio[escolha - 1].nome);
            carrinho[*numCarrinho].preco = cardapio[escolha - 1].preco;
            carrinho[*numCarrinho].quantidade = quantidade;
            (*numCarrinho)++;
            printf("Item adicionado ao carrinho com sucesso!\n");
        } else {
            printf("Quantidade indisponivel no estoque.\n");
        }
    } else {
        printf("Opcao ou quantidade invalida.\n");
    }
}

void excluirPedido(Item carrinho[], int *numCarrinho) {
    int escolha;
    printf("Digite o numero do item que deseja excluir: ");
    scanf("%d", &escolha);
    if (escolha >= 1 && escolha <= *numCarrinho) {
        for (int i = escolha - 1; i < *numCarrinho -1; i++) {
            strcpy(carrinho[i].nome, carrinho[i + 1].nome);
            carrinho[i].preco = carrinho[i + 1].preco;
            carrinho[i].quantidade = carrinho[i + 1].quantidade;
        }
        (*numCarrinho)--;
        printf("Pedido excluido com sucesso!\n");
    } else {
        printf("Opcao invalida.\n");
    }
}

void visualizarCarrinho(Item carrinho[], int numCarrinho) {
    if (numCarrinho > 0) {
        printf("Carrinho de Compras:\n");
        for (int i = 0; i < numCarrinho; i++) {
            printf("%d. %s - Quantidade: %d - Preco Total: R$%.2f\n", i+1, carrinho[i].nome, carrinho[i].quantidade, carrinho[i].preco * carrinho[i].quantidade);
        }
    } else {
        printf("O carrinho esta vazio.\n");
    }
}

void editarPedido(Item cardapio[], int numCardapio, Item carrinho[], int *numCarrinho) {
    int opcao;
    do {
        printf("\n-------------------------------\n");
        printf("\nMenu de Edicao de Pedido:\n");
        printf("1. Adicionar mais itens ao pedido\n");
        printf("2. Remover itens do pedido\n");
        printf("3. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n-------------------------------\n");
        switch (opcao) {
            case 1:
                listarCardapio(cardapio, numCardapio);
                adicionarAoCarrinho(cardapio, numCardapio, carrinho, numCarrinho);
                break;
            case 2:
                visualizarCarrinho(carrinho, *numCarrinho);
                excluirPedido(carrinho, numCarrinho);
                break;
            case 3:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 3);
}