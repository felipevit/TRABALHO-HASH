//FELIPE FILLA VITORINO
//GRR:20230947

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 100 // Tamanho da tabela

typedef struct Contato {
    char nome[50];
    char telefone[15];
    struct Contato *prox;
} Contato;

typedef struct {
    Contato *inicio;
} HashTable;

HashTable tabela[TAM];

// Função hash usando a soma dos caracteres do nome
int hash(char *nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += nome[i];
    }
    return soma % TAM;
}

// Adicionar contato
void adicionarContato(char *nome, char *telefone) {
    int idx = hash(nome);
    Contato *novo = malloc(sizeof(Contato));
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    novo->prox = tabela[idx].inicio;
    tabela[idx].inicio = novo;
    printf("Contato adicionado com sucesso.\n");
}

// Buscar contato por nome
void buscarContato(char *nome) {
    int idx = hash(nome);
    Contato *atual = tabela[idx].inicio;
    clock_t inicio = clock();

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            clock_t fim = clock();
            double tempoBusca = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", atual->nome, atual->telefone, tempoBusca);
            return;
        }
        atual = atual->prox;
    }
    printf("Contato nao encontrado.\n");
}

// Remover contato
void removerContato(char *nome) {
    int idx = hash(nome);
    Contato *atual = tabela[idx].inicio;
    Contato *anterior = NULL;
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                tabela[idx].inicio = atual->prox;
            }
            free(atual);
            printf("Contato removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Contato nao encontrado.\n");
}

// Mostrar todos os contatos
void mostrarTodos() {
    for (int i = 0; i < TAM; i++) {
        Contato *atual = tabela[i].inicio;
        while (atual) {
            printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->prox;
        }
    }
}

// Interface do usuário
void menu() {
    int opcao;
    char nome[50], telefone[15];

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("\nDigite uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Telefone: ");
                fgets(telefone, 15, stdin);
                telefone[strcspn(telefone, "\n")] = '\0';
                adicionarContato(nome, telefone);
                break;
            case 2:
                printf("Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarContato(nome);
                break;
            case 3:
                printf("Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerContato(nome);
                break;
            case 4:
                mostrarTodos();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    for (int i = 0; i < TAM; i++) {
        tabela[i].inicio = NULL;
    }
    menu();
    return 0;
}
