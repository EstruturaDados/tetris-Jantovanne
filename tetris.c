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

typedef struct {
    Peca peca[MAX];
    int topo;
} desfazerPeca;

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

void inicializarDesfazer(desfazerPeca* d) {
    d->topo = -1;
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
void dequeue(Fila* f, desfazerPeca* d) {
    if (f->total > 0) {
        Peca pe = f->peca[f->primeiro];
        // Armazena a peça removida na pilha de desfazer
        d->peca[++d->topo] = pe;
        f->primeiro = (f->primeiro + 1) % MAX;
        f->total--;
        mostrarFila(f);
    } else {
        printf("Fila vazia! Não há peças para remover.\n");
    }
}

// Função para reservar uma peça na pilha
void push(Pilha* p, Fila* f, desfazerPeca* d) {
    if (p->total < MAX) {
        p->topo++;
        p->peca[p->topo] = f->peca[f->primeiro];
        p->total++;
        f->primeiro = (f->primeiro + 1) % MAX; // Remove a peça da fila após reservá-la na pilha
        f->total--;
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

// Função para trocar a peça da frente da fila com o topo da pilha
void trocarPeca(Fila* f, Pilha* p) {
    if (f->total > 0 && p->total > 0) {
        Peca temp = f->peca[f->primeiro];
        f->peca[f->primeiro] = p->peca[p->topo];
        p->peca[p->topo] = temp;
        printf("Peça da frente da fila trocada com o topo da pilha!\n");
    } else {
        printf("Não é possível trocar peças! Verifique se a fila e a pilha têm peças suficientes.\n");
    }
}

// Função para desfazer a última jogada (voltar peça para a fila)
void desfazerJogada(Fila* f, desfazerPeca* d) {
    if (d->topo >= 0) {
        Peca temp = d->peca[d->topo];
        // Desloca as peças na fila para abrir espaço para a peça desfeita
        for (int i = MAX - 1 ; i >= 0 ; i--) {
            f->peca[(f->primeiro + i) % MAX] = f->peca[(f->primeiro + i - 1) % MAX];
        }
        f->peca[f->primeiro] = temp;
        d->topo--;
        printf("Última jogada desfeita! Peça retornada para a fila.\n");
    } else {
        printf("Não há jogadas para desfazer!\n");
    }
}

// Função para inverter a fila de peças futuras
void inverterFila(Fila* f) {
    if (f->total > 0) {
        desfazerPeca temp;
        temp.topo = -1; // Inicializa o topo da pilha temporária
        for (int i = 0; i < f->total; i++) {
            int index = (f->primeiro + i) % MAX;
            temp.peca[i] = f->peca[index];
            temp.topo++;
        }
        for (int i = 0; i < f->total; i++) {
            int index = (f->primeiro + i) % MAX;
            f->peca[index] = temp.peca[temp.topo];
            temp.topo--;
        }
        printf("Fila de peças futuras invertida!\n");
    } else {
        printf("Fila vazia! Não há peças para inverter.\n");
    }
}

void menu(Fila* fila, Pilha* pilha, desfazerPeca* desfazer) {


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
    printf("4 - Trocar peça da frente com topo da pilha\n");
    printf("5 - desfazer a última jogada (voltar peça para a fila)\n");
    printf("6 - inverter a fila de peças futuras\n");
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
        dequeue(fila, desfazer);
        break;
    case 2:
        // Lógica para reservar peça
        push(pilha, fila, desfazer);
        mostrarPilha(pilha);
        break;
    case 3:
        // Lógica para usar peça reservada
        pop(pilha);
        break;
    case 4:
        // Lógica para trocar peça da frente com topo da pilha
        trocarPeca(fila, pilha);
        break;
    case 5:
        // Lógica para desfazer a última jogada (voltar peça para a fila)
        desfazerJogada(fila, desfazer);
        break;
    case 6:
        // Lógica para inverter a fila de peças futuras
        inverterFila(fila);
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
    
    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    Fila fila;
    inicializarFila(&fila);
    Pilha pilha;
    inicializarPilha(&pilha);
    desfazerPeca desfazer;
    inicializarDesfazer(&desfazer);
    
    printf("================================\n");
    printf("Bem vindo ao Tretis Stack!\n");
    printf("================================\n");

    menu(&fila, &pilha, &desfazer);

    return 0;
}

