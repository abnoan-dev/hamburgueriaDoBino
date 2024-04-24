#include "hamburgueria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionarUsuario(UserNode** head, User novoUsuario) {
    UserNode* newNode = (UserNode*)malloc(sizeof(UserNode));
    if (newNode == NULL) {
        printf("Erro: Memória insuficiente para alocar novo usuário.\n");
        return;
    }
    newNode->user = novoUsuario;
    newNode->next = *head;
    *head = newNode;
}

void adicionarItem(ItemNode** head, Item novoItem) {
    ItemNode* newNode = (ItemNode*)malloc(sizeof(ItemNode));
    if (newNode == NULL) {
        printf("Erro: Memória insuficiente para alocar novo item.\n");
        return;
    }
    newNode->item = novoItem;
    newNode->next = *head;
    *head = newNode;
}

void salvarUsuarios(UserNode* head) {
    FILE* arquivo;
    arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }
    UserNode* current = head;
    while (current != NULL) {
        fprintf(arquivo, "%s %s %s\n", current->user.username, current->user.password, current->user.email);
        current = current->next;
    }
    fclose(arquivo);
}

void ordenarUsuariosAlfabeticamente(UserNode** head) {
    UserNode* current = *head;
    UserNode* nextNode;
    User temp;
    while (current != NULL) {
        nextNode = current->next;
        while (nextNode != NULL) {
            if (strcmp(current->user.username, nextNode->user.username) > 0) {
                temp = current->user;
                current->user = nextNode->user;
                nextNode->user = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
    printf("Usuários ordenados em ordem alfabética.\n");
    salvarUsuarios(*head);
}

void carregarUsuarios(UserNode** head) {
    FILE* arquivo;
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }
    char username[MAX_LENGTH], password[MAX_LENGTH], email[MAX_LENGTH];
    while (fscanf(arquivo, "%s %s %s", username, password, email) != EOF) {
        User novoUsuario;
        strcpy(novoUsuario.username, username);
        strcpy(novoUsuario.password, password);
        strcpy(novoUsuario.email, email);
        adicionarUsuario(head, novoUsuario);
    }
    fclose(arquivo);
}

void salvarItens(ItemNode* head) {
    FILE* arquivo;
    arquivo = fopen("itens.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de itens.\n");
        return;
    }
    ItemNode* current = head;
    while (current != NULL) {
        fprintf(arquivo, "%s %.2f %d\n", current->item.nome, current->item.preco, current->item.quantidade);
        current = current->next;
    }
    fclose(arquivo);
}

void escreverCarrinhoEmArquivo(ItemNode* carrinho) {
    FILE* arquivo = fopen("carrinho.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de carrinho.\n");
        return;
    }
    ItemNode* current = carrinho;
    while (current != NULL) {
        fprintf(arquivo, "Nome: %s - Quantidade: %d - Preço: R$%.2f\n", current->item.nome, current->item.quantidade, current->item.preco);
        current = current->next;
    }
    fclose(arquivo);
}

void carregarItens(ItemNode** head) {
    FILE* arquivo;
    arquivo = fopen("itens.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de itens.\n");
        return;
    }
    char nome[MAX_LENGTH];
    float preco;
    int quantidade;
    while (fscanf(arquivo, "%s %f %d", nome, &preco, &quantidade) != EOF) {
        Item novoItem;
        strcpy(novoItem.nome, nome);
        novoItem.preco = preco;
        novoItem.quantidade = quantidade;
        adicionarItem(head, novoItem);
    }
    fclose(arquivo);
}

void boasVindas() {
    printf("*********************************\n");
    printf("Bem-vindo a Hamburgueria do Bino!\n");
    printf("*********************************\n");
}

void menu() {
    printf("\n--------------------\n");
    printf("\nMenu de Opções:\n");
    printf("1. Cadastro de Usuário\n");
    printf("2. Buscar Cliente\n");
    printf("3. Ver Cardápio\n");
    printf("4. Realizar Pedido\n");
    printf("5. Excluir Pedido\n");
    printf("6. Visualizar Carrinho\n");
    printf("7. Editar Pedido\n");
    printf("8. Ordenar usuários em ordem alfabética\n");
    printf("9. Sair\n");
    printf("\n--------------------\n");
}

void cadastrarUsuario(UserNode** head, int* numUsers) {
    if (*numUsers < MAX_USERS) {
        User novoUsuario;
        printf("Digite o nome de usuário: ");
        scanf("%s", novoUsuario.username);
        printf("Digite a senha: ");
        scanf("%s", novoUsuario.password);
        printf("Digite o email: ");
        scanf("%s", novoUsuario.email);
        while (strstr(novoUsuario.email, "@") == NULL) {
            printf("Email inválido. Digite novamente: ");
            scanf("%s", novoUsuario.email);
        }
        adicionarUsuario(head, novoUsuario);
        (*numUsers)++;
        salvarUsuarios(*head);
        printf("Cadastro realizado com sucesso!\n");
    } else {
        printf("Limite de usuários atingido. Não é possível cadastrar mais.\n");
    }
}

int buscarCliente(UserNode* head, char* username) {
    UserNode* current = head;
    while (current != NULL) {
        if (strcmp(current->user.username, username) == 0) {
            printf("Cliente encontrado:\n");
            printf("Nome de usuário: %s\n", current->user.username);
            printf("Email: %s\n", current->user.email);
            return 1;
        }
        current = current->next;
    }
    printf("Cliente não encontrado.\n");
    return 0;
}

void listarCardapio(ItemNode* head) {
    printf("Cardápio da Hamburgueria do Bino:\n");
    ItemNode* current = head;
    int i = 1;
    while (current != NULL) {
        printf("%d. %s - R$%.2f - Quantidade disponível: %d\n", i, current->item.nome, current->item.preco, current->item.quantidade);
        current = current->next;
        i++;
    }
}

void adicionarAoCarrinho(ItemNode* cardapio, ItemNode** carrinho, int* numCarrinho) {
    int escolha, quantidade;
    printf("Digite o código do hambúrguer que deseja adicionar ao carrinho: ");
    scanf("%d", &escolha);
    printf("Digite a quantidade desejada: ");
    scanf("%d", &quantidade);

    ItemNode* current = cardapio;
    int i = 1;
    while (current != NULL && i < escolha) {
        current = current->next;
        i++;
    }

    if (current != NULL && quantidade > 0) {
        if (quantidade <= current->item.quantidade) {
            ItemNode* newNode = (ItemNode*)malloc(sizeof(ItemNode));
            if (newNode == NULL) {
                printf("Erro: Memória insuficiente para alocar novo item no carrinho.\n");
                return;
            }
            strcpy(newNode->item.nome, current->item.nome);
            newNode->item.preco = current->item.preco;
            newNode->item.quantidade = quantidade;
            newNode->next = *carrinho;
            *carrinho = newNode;
            (*numCarrinho)++;
            printf("Item adicionado ao carrinho com sucesso!\n");
        } else {
            printf("Quantidade indisponível no estoque.\n");
        }
    } else {
        printf("Opção ou quantidade inválida.\n");
    }
}

void excluirPedido(ItemNode** carrinho, int* numCarrinho) {
    int escolha;
    printf("Digite o número do item que deseja excluir: ");
    scanf("%d", &escolha);
    if (escolha >= 1 && escolha <= *numCarrinho) {
        ItemNode* temp = *carrinho;
        if (escolha == 1) {
            *carrinho = (*carrinho)->next;
            free(temp);
        } else {
            int i = 1;
            while (i < escolha - 1) {
                temp = temp->next;
                i++;
            }
            ItemNode* nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            free(nodeToDelete);
        }
        (*numCarrinho)--;
        printf("Pedido excluído com sucesso!\n");
    } else {
        printf("Opção inválida.\n");
    }
}

void visualizarCarrinho(ItemNode* carrinho) {
    if (carrinho != NULL) {
        printf("Carrinho de Compras:\n");
        ItemNode* current = carrinho;
        int i = 1;
        while (current != NULL) {
            printf("%d. %s - Quantidade: %d - Preço Total: R$%.2f\n", i, current->item.nome, current->item.quantidade, current->item.preco * current->item.quantidade);
            current = current->next;
            i++;
        }
    } else {
        printf("O carrinho está vazio.\n");
    }
}

void editarPedido(ItemNode* cardapio, ItemNode** carrinho, int* numCarrinho) {
    int opcao;
    do {
        printf("\n-------------------------------\n");
        printf("\nMenu de Edição de Pedido:\n");
        printf("1. Adicionar mais itens ao pedido\n");
        printf("2. Remover itens do pedido\n");
        printf("3. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("\n-------------------------------\n");
        switch (opcao) {
            case 1:
                listarCardapio(cardapio);
                adicionarAoCarrinho(cardapio, carrinho, numCarrinho);
                break;
            case 2:
                visualizarCarrinho(*carrinho);
                excluirPedido(carrinho, numCarrinho);
                break;
            case 3:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 3);
}