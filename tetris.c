#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha

#define MAX 5

// estrutura para representar uma peça do Tetris.
typedef struct {
    char tipo;
    int id;
} Peca;

// estrutura para representar a fila circular de peças futuras.
typedef struct {
    Peca peca[MAX];
    int primeiro;
    int ultimo;
    int total;
} Fila;

typedef struct {
    Peca peca[MAX];
    int topo;
    int total;
} Pilha;

int contador_id = 0; // Variável global para controle do ID das peças
char tipos[5] = {'I', 'O', 'T', 'L', 'Z'}; // Tipos de peças do Tetris

void inicializarFila(Fila* f) {
    f->primeiro = 0;
    f->ultimo = 0;
    f->total = 0;
}

void inicializarPilha(Pilha* p) {
    p->topo = -1;
    p->total = 0;
}

// Função para adicionar uma peça à fila circular
void enqueue(Fila* f) {


    while (f->total != MAX)
    {
        //gera peças aleatórias.
        Peca p;
        p.tipo = tipos[rand() % 5]; // Gera um tipo de peça aleatório
        p.id = contador_id++; // Atribui um ID único à peça
        f->peca[f->ultimo] = p; // Adiciona a peça à posição do último
        f->ultimo = (f->ultimo + 1) % MAX; // Atualiza o índice do último
        f->total++; // Incrementa o total de peças na fila
    }
    

}

// Função para exibir o conteúdo da fila circular
void mostrarFila(Fila* f) {
    printf("------------------------------\n");
    printf("Fila de Peças Futuras:\n");
    printf("------------------------------\n");
    for (int i = 0; i < f->total; i++) {
        int index = (f->primeiro + i) % MAX;
        printf("Peça ID: %d | Tipo: %c\n", f->peca[index].id, f->peca[index].tipo);
        printf("------------------------------\n");
    }
}

// Função para remover uma peça da fila circular
void dequeue(Fila* f) {
    if (f->total > 0) {
        f->primeiro = (f->primeiro + 1) % MAX;
        f->total--;
        mostrarFila(f);
    } else {
        printf("Fila vazia! Não há peças para remover.\n");
    }
}

// Função para reservar uma peça na pilha
void push(Pilha* p, Fila* f) {
    if (p->total < MAX) {
        p->topo++;
        p->peca[p->topo] = f->peca[f->primeiro];
        p->total++;
        dequeue(f); // Remove a peça da fila após reservá-la na pilha
    } else {
        printf("Pilha cheia! Não é possível reservar mais peças.\n");
    }
}

// Função para exibir o conteúdo da pilha
void mostrarPilha(Pilha* p) {
    if (p->total == 0) {
        return;
    }
    printf("----------------------------------------------\n");
    printf("Pilha de Peças Reservadas:\n");
    printf("----------------------------------------------\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("Peça ID: %d | Tipo: %c\n", p->peca[i].id, p->peca[i].tipo);
        printf("----------------------------------------------\n");
    }
}

// Função para usar uma peça reservada da pilha
void pop(Pilha* p) {
    if (p->total > 0) {
        Peca pe = p->peca[p->topo];
        p->topo--;
        p->total--;
        printf("----------------------------------------------\n");
        printf("Usando peça reservada: ID %d | Tipo: %c\n", pe.id, pe.tipo);
        printf("----------------------------------------------\n");
        mostrarPilha(p);
    } else {
        printf("Pilha vazia! Não há peças reservadas para usar.\n");
    }
}

void menu(Fila* fila, Pilha* pilha) {


    int opcao;
    do {
    // Lógica para inserir peça na fila
    enqueue(fila);

    mostrarFila(fila);

    mostrarPilha(pilha);

    printf("----------\n");
    printf("Menu:\n");
    printf("----------\n");
    printf("1 - Jogar peça\n");
    printf("2 - Reservar peça\n");
    printf("3 - Usar peça reservada\n");
    printf("0 - Sair\n");
    printf("---------------------\n");
    printf("Escolha uma opção: \n");
    printf("----------------------\n");
    scanf("%d", &opcao);
    getchar(); // Limpar o buffer de entrada

    switch (opcao)
    {
    case 1:
         // Lógica para jogar peça
        dequeue(fila);
        break;
    case 2:
        // Lógica para reservar peça
        push(pilha, fila);
        mostrarPilha(pilha);
        break;
    case 3:
        // Lógica para usar peça reservada
        pop(pilha);
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
    
    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    Fila fila;
    inicializarFila(&fila);
    Pilha pilha;
    inicializarPilha(&pilha);
    
    printf("================================\n");
    printf("Bem vindo ao Tretis Stack!\n");
    printf("================================\n");

    menu(&fila, &pilha);


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

