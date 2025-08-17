#include <stdio.h>
#include <stdbool.h> // Para usar o tipo de dado 'bool' (true/false)

// Constantes globais
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Protótipo da função (declaração para que a main() saiba que ela existe)
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
bool posicionarNavio(int tabuleiro[][TAM_TABULEIRO], int linha, int coluna, char orientacao);


int main() {
    // 1. Criar um Tabuleiro 10x10 e inicializar com 0 (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    printf("Iniciando o jogo Batalha Naval...\n");
    printf("Posicionando 4 navios de tamanho %d...\n\n", TAM_NAVIO);

    // 2. Posicionar Quatro Navios (coordenadas definidas no código)
    //    'H' -> Horizontal
    //    'V' -> Vertical
    //    'D' -> Diagonal (principal, da esquerda para direita)
    //    'A' -> Anti-diagonal (secundária, da direita para esquerda)

    // Tenta posicionar cada navio. Se qualquer um falhar (por sair do limite ou sobrepor), o programa encerra.
    if (!posicionarNavio(tabuleiro, 1, 1, 'H')) return 1; // Navio Horizontal
    if (!posicionarNavio(tabuleiro, 3, 8, 'V')) return 1; // Navio Vertical
    if (!posicionarNavio(tabuleiro, 3, 1, 'D')) return 1; // Navio Diagonal
    if (!posicionarNavio(tabuleiro, 1, 8, 'A')) return 1; // Navio Anti-Diagonal

    // 3. Exibir o Tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0; // Sucesso
}


/**
 * @brief Posiciona um navio no tabuleiro após validar limites e sobreposição.
 * @param tabuleiro A matriz do jogo.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param orientacao O tipo de orientação: 'H', 'V', 'D', ou 'A'.
 * @return true se o navio foi posicionado com sucesso, false caso contrário.
 */
bool posicionarNavio(int tabuleiro[][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    // --- VALIDAÇÃO DE LIMITES ---
    switch (orientacao) {
        case 'H': // Horizontal
            if (coluna + TAM_NAVIO > TAM_TABULEIRO) {
                printf("Erro: Navio horizontal na posicao (%d,%d) esta fora do tabuleiro!\n", linha, coluna);
                return false;
            }
            break;
        case 'V': // Vertical
            if (linha + TAM_NAVIO > TAM_TABULEIRO) {
                printf("Erro: Navio vertical na posicao (%d,%d) esta fora do tabuleiro!\n", linha, coluna);
                return false;
            }
            break;
        case 'D': // Diagonal (principal)
            if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna + TAM_NAVIO > TAM_TABULEIRO) {
                printf("Erro: Navio diagonal na posicao (%d,%d) esta fora do tabuleiro!\n", linha, coluna);
                return false;
            }
            break;
        case 'A': // Anti-diagonal
            if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna - (TAM_NAVIO - 1) < 0) {
                printf("Erro: Navio anti-diagonal na posicao (%d,%d) esta fora do tabuleiro!\n", linha, coluna);
                return false;
            }
            break;
        default:
            printf("Erro: Orientacao '%c' invalida!\n", orientacao);
            return false;
    }

    // --- VALIDAÇÃO DE SOBREPOSIÇÃO ---
    // Verifica se alguma das posições que o navio irá ocupar já está preenchida
    for (int i = 0; i < TAM_NAVIO; i++) {
        switch (orientacao) {
            case 'H':
                if (tabuleiro[linha][coluna + i] != 0) return false;
                break;
            case 'V':
                if (tabuleiro[linha + i][coluna] != 0) return false;
                break;
            case 'D':
                if (tabuleiro[linha + i][coluna + i] != 0) return false;
                break;
            case 'A':
                if (tabuleiro[linha + i][coluna - i] != 0) return false;
                break;
        }
    }
    
    // Se passou em todas as validações, posiciona o navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        switch (orientacao) {
            case 'H':
                tabuleiro[linha][coluna + i] = 3;
                break;
            case 'V':
                tabuleiro[linha + i][coluna] = 3;
                break;
            case 'D':
                tabuleiro[linha + i][coluna + i] = 3;
                break;
            case 'A':
                tabuleiro[linha + i][coluna - i] = 3;
                break;
        }
    }
    
    printf("Navio com orientacao '%c' posicionado com sucesso em (%d,%d).\n", orientacao, linha, coluna);
    return true;
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 * @param tabuleiro A matriz do jogo a ser exibida.
 */
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n");
    // Imprime cabeçalho das colunas para melhor visualização
    printf("  ");
    for(int i = 0; i < TAM_TABULEIRO; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d ", i); // Imprime cabeçalho da linha
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("=============================\n");
}