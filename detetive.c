#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------
// Estrutura da peça
// ---------------------------------------------
typedef struct {
    char nome;   // Tipo da peça (I, O, T, L)
    int id;      // Identificador único
} Peca;

// ---------------------------------------------
// Configurações de capacidade
// ---------------------------------------------
#define TAM_FILA 5       // Capacidade fixa da fila circular
#define TAM_PILHA 3      // Capacidade da pilha de reserva

// ---------------------------------------------
// Variáveis globais
// ---------------------------------------------
int proximoID = 0;       // ID único para cada nova peça gerada

// ---------------------------------------------
// Função que gera uma nova peça automaticamente
// ---------------------------------------------
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];  // Escolhe um tipo aleatório
    nova.id = proximoID++;          // Define ID único
    return nova;
}

// ---------------------------------------------
// Impressão formatada da fila
// ---------------------------------------------
void printFila(Peca fila[], int frente, int tamanho) {
    printf("Fila de pecas: ");
    for (int i = 0; i < tamanho; i++) {
        int idx = (frente + i) % TAM_FILA;  // Índice circular
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
    }
    printf("\n");
}

// ---------------------------------------------
// Impressão da pilha (Topo → Base)
// ---------------------------------------------
void printPilha(Peca pilha[], int topo) {
    printf("Pilha de reserva (Topo -> Base): ");
    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

// ---------------------------------------------
// Mostrar estado atual (fila + pilha)
// ---------------------------------------------
void mostrarEstado(Peca fila[], int frente, int tamanho, Peca pilha[], int topo) {
    printFila(fila, frente, tamanho);
    printPilha(pilha, topo);
    printf("-------------------------------------------------\n");
}

// ---------------------------------------------
// Mostrar regras completas do "Tetris Stack"
// ---------------------------------------------
void mostrarRegras() {
    printf("\n========== REGRAS DO JOGO ==========\n");
    printf("Este programa simula um sistema de gerenciamento de pecas\n");
    printf("inspirado no Tetris. A fila representa as proximas pecas que\n");
    printf("o jogador recebera, enquanto a pilha armazena pecas reservadas.\n\n");

    printf("COMO FUNCIONA:\n");
    printf("- A fila possui sempre 5 pecas.\n");
    printf("- A pilha pode guardar ate 3 pecas.\n");
    printf("- Jogar peca: remove a peca da frente da fila.\n");
    printf("- Reservar peca: move a peca da frente da fila para o topo da pilha.\n");
    printf("- Usar peca reservada: remove a peca do topo da pilha.\n");
    printf("- Trocar peca atual: troca a peca da frente da fila com o topo da pilha.\n");
    printf("- Troca multipla: troca as 3 primeiras pecas da fila com as 3 da pilha.\n");
    printf("- Toda vez que remover ou reservar uma peca, uma nova e gerada.\n\n");
}

// ---------------------------------------------
// Função principal
// ---------------------------------------------
int main() {
    srand(123); // Semente fixa para gerar sempre a mesma sequência

    // -----------------------------------------
    // Estruturas da fila e pilha
    // -----------------------------------------
    Peca fila[TAM_FILA];
    Peca pilha[TAM_PILHA];

    int frente = 0;                 // Início da fila circular
    int tamanhoFila = TAM_FILA;    // Fila sempre cheia
    int topo = -1;                 // Pilha vazia

    // -----------------------------------------
    // Inicializar fila com 5 pecas
    // -----------------------------------------
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
    }

    // -----------------------------------------
    // Mensagem de boas-vindas
    // -----------------------------------------
    printf("======================================\n");
    printf("   BEM-VINDO AO TETRIS STACK DELUXE!\n");
    printf("======================================\n\n");

    int opcao;

    // -----------------------------------------
    // Loop principal do menu
    // -----------------------------------------
    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Reservar peça (enviar para pilha)\n");
        printf("3 - Usar peça reservada (remover topo da pilha)\n");
        printf("4 - Trocar peça da frente com topo da pilha\n");
        printf("5 - Trocar as 3 primeiras da fila com as 3 da pilha\n");
        printf("6 - Mostrar regras\n");
        printf("7 - Mostrar estado atual\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        printf("\n");

        // -------------------------------
        // OPCÃO 1 – Jogar peça
        // -------------------------------
        if (opcao == 1) {
            printf("Acao: Jogando peca...\n");

            frente = (frente + 1) % TAM_FILA;    // Avança a fila
            fila[(frente + TAM_FILA - 1) % TAM_FILA] = gerarPeca(); // Enche o final

            mostrarEstado(fila, frente, tamanhoFila, pilha, topo);
        }

        // -------------------------------
        // OPCÃO 2 – Reservar peça
        // -------------------------------
        else if (opcao == 2) {
            if (topo == TAM_PILHA - 1) {
                printf("A pilha esta cheia! Impossivel reservar.\n");
            } else {
                printf("Acao: Reservando peca...\n");

                pilha[++topo] = fila[frente]; // Envia para o topo da pilha

                frente = (frente + 1) % TAM_FILA; // Remove da fila
                fila[(frente + TAM_FILA - 1) % TAM_FILA] = gerarPeca(); // Reposição automática

                mostrarEstado(fila, frente, tamanhoFila, pilha, topo);
            }
        }

        // -------------------------------
        // OPCÃO 3 – Usar peça reservada
        // -------------------------------
        else if (opcao == 3) {
            if (topo == -1) {
                printf("A pilha esta vazia!\n");
            } else {
                printf("Acao: Usando peca reservada...\n");
                topo--; // Remove a peça do topo

                mostrarEstado(fila, frente, tamanhoFila, pilha, topo);
            }
        }

        // -------------------------------
        // OPCÃO 4 – Troca simples
        // -------------------------------
        else if (opcao == 4) {
            if (topo == -1) {
                printf("Nao ha pecas na pilha para trocar!\n");
            } else {
                printf("Acao: Trocando peca atual com o topo da pilha...\n");

                Peca tmp = fila[frente];
                fila[frente] = pilha[topo];
                pilha[topo] = tmp;

                mostrarEstado(fila, frente, tamanhoFila, pilha, topo);
            }
        }

        // -------------------------------
        // OPCÃO 5 – Troca múltipla
        // -------------------------------
        else if (opcao == 5) {
            if (topo < 2) {
                printf("A pilha precisa ter ao menos 3 pecas!\n");
            } else {
                printf("Acao: Trocando em bloco (3 pecas)...\n");

                for (int i = 0; i < 3; i++) {
                    int idx = (frente + i) % TAM_FILA;
                    Peca tmp = fila[idx];
                    fila[idx] = pilha[topo - i];
                    pilha[topo - i] = tmp;
                }

                mostrarEstado(fila, frente, tamanhoFila, pilha, topo);
            }
        }

        // -------------------------------
        // OPCÃO 6 – Regras
        // -------------------------------
        else if (opcao == 6) {
            mostrarRegras();
        }

        // -------------------------------
        // OPCÃO 7 – Mostrar estado
        // -------------------------------
        else if (opcao == 7) {
            mostrarEstado(fila, frente, tamanhoFila, pilha, topo);
        }

        // -------------------------------
        // Encerrar
        // -------------------------------
        else if (opcao == 0) {
            printf("Saindo... Obrigado por jogar o Tetris Stack!\n");
        }

        else {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
