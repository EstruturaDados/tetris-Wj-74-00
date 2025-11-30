#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5   // Tamanho máximo da fila

// -------------------------------
// Struct que representa uma peça
// -------------------------------
typedef struct {
    char nome;   // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;      // ID único da peça
} Peca;

// -------------------------------
// Fila de peças
// -------------------------------
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

// -------------------------------
// Gera automaticamente uma nova peça
// -------------------------------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];
    nova.id = id;

    return nova;
}

// -------------------------------
// Inicializa a fila
// -------------------------------
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;
}

// -------------------------------
// Verifica se a fila está cheia
// -------------------------------
int filaCheia(Fila *f) {
    return f->quantidade == TAMANHO_FILA;
}

// -------------------------------
// Verifica se a fila está vazia
// -------------------------------
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// -------------------------------
// Insere uma nova peça no final da fila (enqueue)
// -------------------------------
void enqueue(Fila *f, Peca nova) {
    if (filaCheia(f)) {
        printf(" A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    f->tras = (f->tras + 1) % TAMANHO_FILA;
    f->pecas[f->tras] = nova;
    f->quantidade++;

    printf("Peça [%c %d] inserida com sucesso!\n", nova.nome, nova.id);
}

// -------------------------------
// Remove a peça da frente da fila (dequeue)
// -------------------------------
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf(" A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->quantidade--;

    printf("Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// -------------------------------
// Exibe as peças da fila
// -------------------------------
void exibirFila(Fila *f) {
    printf("\n=== Fila de peças ===\n");

    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }

    int i = f->frente;
    for (int c = 0; c < f->quantidade; c++) {
        Peca p = f->pecas[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// -------------------------------
// Programa principal
// -------------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    int idAtual = 0;

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    int opcao;

    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;

            case 2:
                enqueue(&fila, gerarPeca(idAtual++));
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}