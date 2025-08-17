#include <stdio.h>
#include <stdbool.h> // Para usar o tipo de dado 'bool' (true/false)

// Define constantes para facilitar a manutenção do código
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("=== TABULEIRO BATALHA NAVAL ===\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Pula para a próxima linha ao final de cada linha da matriz
    }
    printf("=============================\n");
}

int main() {
    // 1. Representa o Tabuleiro: Cria a matriz 10x10
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com 0 (água)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Posiciona os Navios
    // Coordenadas iniciais (linha e coluna) para cada navio.
    // Você pode alterar esses valores para testar a validação.
    
    // Navio 1 (Horizontal)
    int navio_h_linha = 2;
    int navio_h_coluna = 3;

    // Navio 2 (Vertical)
    int navio_v_linha = 5;
    int navio_v_coluna = 7;

    // --- VALIDAÇÃO ---

    // a) Validar se os navios estão dentro dos limites do tabuleiro
    bool h_dentro_dos_limites = (navio_h_coluna + TAM_NAVIO) <= TAM_TABULEIRO;
    bool v_dentro_dos_limites = (navio_v_linha + TAM_NAVIO) <= TAM_TABULEIRO;

    if (!h_dentro_dos_limites) {
        printf("Erro: O navio horizontal esta fora do tabuleiro!\n");
        return 1; // Encerra o programa com um código de erro
    }
    if (!v_dentro_dos_limites) {
        printf("Erro: O navio vertical esta fora do tabuleiro!\n");
        return 1; // Encerra o programa com um código de erro
    }

    // b) Validar se os navios não se sobrepõem (verificação simplificada)
    // Primeiro, posicionamos o navio horizontal.
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[navio_h_linha][navio_h_coluna + i] = 3;
    }

    // Agora, antes de posicionar o vertical, verificamos se alguma de suas futuras posições já está ocupada.
    bool sobreposicao = false;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[navio_v_linha + i][navio_v_coluna] != 0) {
            sobreposicao = true;
            break; // Se encontrar uma sobreposição, não precisa continuar verificando
        }
    }

    if (sobreposicao) {
        printf("Erro: Os navios estao se sobrepondo!\n");
        return 1; // Encerra o programa com um código de erro
    }

    // --- POSICIONAMENTO FINAL ---

    // Se passou por todas as validações, posiciona o navio vertical
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[navio_v_linha + i][navio_v_coluna] = 3;
    }

    // 3. Exiba o Tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0; // Sucesso
}