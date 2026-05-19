#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// estrutura para representar uma peça do Tetris.
typedef struct {
    char tipo;
    int id;
} Peca;

// estrutura para representar a fila circular de peças futuras.
typedef struct {
    Peca peca[5];
    int primeiro;
    int ultimo;
    int total;
} Fila;

int contador_id = 0; // Variável global para controle do ID das peças

void inicializarFila(Fila* f) {
    f->primeiro = 0;
    f->ultimo = 0;
    f->total = 0;
}

void gerarPeca(Peca* p) {
    char tipos[] = {'I', 'O', 'T', 'L', 'Z'};
    p->tipo = tipos[rand() % 5];
    p->id = contador_id++;
}

// Função para adicionar uma peça à fila circular
void enqueue(Fila* f, Peca p) {
    if (f->total < 5) {
        f->peca[f->ultimo] = p;
        f->ultimo = (f->ultimo + 1) % 5;
        f->total++;
    } else {
        printf("Fila cheia! Não é possível adicionar mais peças.\n");
    }
}

// Função para exibir o conteúdo da fila circular
void mostrarFila(Fila* f) {
    printf("------------------------------\n");
    printf("Fila de Peças Futuras:\n");
    printf("------------------------------\n");
    for (int i = 0; i < f->total; i++) {
        int index = (f->primeiro + i) % 5;
        printf("Peça ID: %d | Tipo: %c\n", f->peca[index].id, f->peca[index].tipo);
        printf("------------------------------\n");
    }
}

// Função para remover uma peça da fila circular
void dequeue(Fila* f) {
    if (f->total > 0) {
        f->primeiro = (f->primeiro + 1) % 5;
        f->total--;
        mostrarFila(f);
    } else {
        printf("Fila vazia! Não há peças para remover.\n");
    }
}


void menu(Fila* fila) {

    int opcao;
    do {
    printf("----------\n");
    printf("Menu:\n");
    printf("----------\n");
    printf("1 - Inserir peça na fila\n");
    printf("2 - Jogar peça\n");
    printf("0 - Sair\n");
    printf("---------------------\n");
    printf("Escolha uma opção: \n");
    printf("----------------------\n");
    scanf("%d", &opcao);
    getchar(); // Limpar o buffer de entrada

    switch (opcao)
    {
    case 1:
    // Lógica para inserir peça na fila
        Peca nova_peca;
        gerarPeca(&nova_peca);
        enqueue(fila, nova_peca);
        mostrarFila(fila);
        break;
    case 2:
        // Lógica para jogar peça
        dequeue(fila);
        break;
    case 0:
        printf("Saindo...\n");
        break;
    default:
        printf("Opção inválida!\n");
        break;
    }

    } while (opcao != 0);

}




int main() {

    srand(time(NULL)); // Inicializa a semente para geração de peças aleatórias
    setlocale(LC_ALL, ".UTF-8"); // Configura a localidade para UTF-8
    // 🧩 Nível Novato: Fila de Peças Futuras
    Fila* fila = (Fila*) calloc(1, sizeof(Fila));
    inicializarFila(fila);
    
    printf("================================\n");
    printf("Bem vindo ao Tretis Stack!\n");
    printf("================================\n");

    menu(fila);

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

