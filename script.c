#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar informações sobre destinos
typedef struct {
    char nome[20];
    char horarioSaida[10];
    char horarioChegada[10];
    float valorNormal;
    float valorEstudante;
} Destino;

// Estrutura para armazenar informações sobre transações
typedef struct {
    char destino[20];
    float valor;
} Transacao;

Transacao transacoes[100]; // Array para armazenar as transações
int numTransacoes = 0; // Número atual de transações

// Função para registrar uma venda de passagem
void registrarVenda(char destino[], float valor) {
    if (numTransacoes < 100) {
        strcpy(transacoes[numTransacoes].destino, destino);
        transacoes[numTransacoes].valor = valor;
        numTransacoes++;
        printf("Venda registrada com sucesso!\n");
    } else {
        printf("Não foi possível registrar a venda. Limite de transações atingido.\n");
    }
}

// Função para exibir o relatório de caixa
void relatorioCaixa() {
    float totalVendas = 0;

    printf("\n=== Relatório de Caixa ===\n");
    printf("Destino\t\tValor\n");
    for (int i = 0; i < numTransacoes; i++) {
        printf("%s\t\tR$%.2f\n", transacoes[i].destino, transacoes[i].valor);
        totalVendas += transacoes[i].valor;
    }
    printf("Total de Vendas: R$%.2f\n", totalVendas);
}

// Função para comprar passagem
void comprarPassagem() {
    Destino destinos[3] = {
        {"Jundiaí", "08:00", "10:30", 50.0, 40.0},
        {"Santos", "09:30", "12:00", 70.0, 55.0},
        {"Ribeirão Preto", "10:00", "14:00", 90.0, 70.0}
    };

    int opcaoDestino;

    printf("\nEscolha o destino:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s (Saída: %s | Chegada: %s | Valor: R$%.2f | Estudante: R$%.2f)\n", 
                i + 1, destinos[i].nome, destinos[i].horarioSaida, destinos[i].horarioChegada, 
                destinos[i].valorNormal, destinos[i].valorEstudante);
    }
    printf("Opção: ");
    scanf("%d", &opcaoDestino);

    if (opcaoDestino < 1 || opcaoDestino > 3) {
        printf("Opção inválida.\n");
        return;
    }

    int tipoCliente;
    printf("Você é um estudante? (1 - Sim / 0 - Não): ");
    scanf("%d", &tipoCliente);

    if (tipoCliente != 0 && tipoCliente != 1) {
        printf("Opção inválida.\n");
        return;
    }

    float valorPassagem = tipoCliente ? destinos[opcaoDestino - 1].valorEstudante : destinos[opcaoDestino - 1].valorNormal;
    registrarVenda(destinos[opcaoDestino - 1].nome, valorPassagem);
}

int main() {
    int opcaoMenu;

    printf("=== Sistema de Vendas de Passagens ===\n");

    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Comprar passagem\n");
        printf("2. Controle de caixa\n");
        printf("3. Sair do sistema\n");
        printf("Opção: ");
        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {
            case 1:
                comprarPassagem();
                break;
            case 2:
                relatorioCaixa();
                break;
            case 3:
                printf("Saindo do sistema. Até logo!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcaoMenu != 3);

    return 0;
}
