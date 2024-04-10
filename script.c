#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para armazenar informações sobre destinos
typedef struct {
    char nome[20];
    char horarioSaida[10];
    char horarioChegada[10];
    float valorNormal;
    float valorEstudante;
    int numPoltronas;
    int poltronasLivres;
    int poltronasOcupadas;
    bool poltronas[50]; // Assumindo um máximo de 50 poltronas por veículo
} Destino;

// Inicializa os destinos com todas as poltronas disponíveis
Destino destinos[3] = {
    {"Jundiaí", "08:00", "10:30", 50.0, 40.0, 38, 38, 0, {true}}, // Todas as poltronas disponíveis inicialmente
    {"Santos", "09:30", "12:00", 70.0, 55.0, 38, 38, 0, {true}},
    {"Ribeirão Preto", "10:00", "14:00", 90.0, 70.0, 38, 38, 0, {true}}
};

// Função para exibir poltronas disponíveis
void exibirPoltronas(int destinoIndex) {
    printf("\nPoltronas disponíveis para %s (%d poltronas livres | %d poltronas ocupadas):\n", 
           destinos[destinoIndex].nome, destinos[destinoIndex].poltronasLivres, destinos[destinoIndex].poltronasOcupadas);
    for (int i = 0; i < destinos[destinoIndex].numPoltronas; i++) {
        if (destinos[destinoIndex].poltronas[i]) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

// Função para selecionar a poltrona
int selecionarPoltrona(int destinoIndex) {
    int poltronaSelecionada;

    exibirPoltronas(destinoIndex);

    printf("Selecione o número da poltrona desejada: ");
    scanf("%d", &poltronaSelecionada);

    if (poltronaSelecionada < 1 || poltronaSelecionada > destinos[destinoIndex].numPoltronas || !destinos[destinoIndex].poltronas[poltronaSelecionada - 1]) {
        printf("Poltrona inválida ou já ocupada.\n");
        return -1; // Retorna -1 se a poltrona for inválida
    }

    destinos[destinoIndex].poltronas[poltronaSelecionada - 1] = false; // Marca a poltrona como ocupada
    destinos[destinoIndex].poltronasLivres--; // Decrementa o número de poltronas livres
    destinos[destinoIndex].poltronasOcupadas++; // Incrementa o número de poltronas ocupadas
    return poltronaSelecionada;
}

// Função para comprar passagem
void comprarPassagem() {
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

    int poltronaSelecionada = selecionarPoltrona(opcaoDestino - 1);

    if (poltronaSelecionada != -1) {
        float valorPassagem = tipoCliente ? destinos[opcaoDestino - 1].valorEstudante : destinos[opcaoDestino - 1].valorNormal;
        printf("Passagem comprada com sucesso para %s. Poltrona: %d. Valor: R$%.2f\n", destinos[opcaoDestino - 1].nome, poltronaSelecionada, valorPassagem);
    }
}

// Função para exibir relatório de caixa
void relatorioCaixa() {
    float totalVendas = 0.0;

    for (int i = 0; i < 3; i++) {
        float vendasDestino = (destinos[i].valorNormal * (destinos[i].numPoltronas - destinos[i].poltronasLivres)) + (destinos[i].valorEstudante * (destinos[i].numPoltronas - destinos[i].poltronasLivres));
        totalVendas += vendasDestino;
        printf("Total de vendas para %s: R$%.2f\n", destinos[i].nome, vendasDestino);
    }

    printf("\nTotal de vendas realizadas: R$%.2f\n", totalVendas);
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
