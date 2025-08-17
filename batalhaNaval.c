#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para a função abs() (valor absoluto)

// --- CONSTANTES GLOBAIS ---
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5 // Tamanho das matrizes de habilidade (deve ser ímpar)

// --- VALORES DO TABULEIRO ---
#define AGUA 0
#define NAVIO 3
#define EFEITO_HABILIDADE 5

// --- PROTÓTIPOS DAS FUNÇÕES ---
// Funções da etapa anterior
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
bool posicionarNavio(int tabuleiro[][TAM_TABULEIRO], int linha, int coluna, char orientacao);

// Novas funções para esta etapa
void criarMatrizCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarMatrizCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarMatrizOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]);
void aplicarHabilidade(int tabuleiro[][TAM_TABULEIRO], int habilidade[][TAM_HABILIDADE], int origem_linha, int origem_coluna);
void exibirMatrizHabilidade(int matriz[TAM_HABILIDADE][TAM_HABILIDADE], const char* nomeHabilidade);


int main() {
    // 1. Definir o Tabuleiro e posicionar os navios
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Posiciona os navios da etapa anterior
    posicionarNavio(tabuleiro, 1, 1, 'H');
    posicionarNavio(tabuleiro, 3, 8, 'V');
    posicionarNavio(tabuleiro, 3, 1, 'D');
    posicionarNavio(tabuleiro, 1, 8, 'A');

    // 2. Criar Matrizes de Habilidade
    int habilidadeCone[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeCruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeOctaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Gera os padrões de forma dinâmica usando condicionais
    criarMatrizCone(habilidadeCone);
    criarMatrizCruz(habilidadeCruz);
    criarMatrizOctaedro(habilidadeOctaedro);
    
    // Exibe as matrizes de habilidade geradas para verificação
    exibirMatrizHabilidade(habilidadeCone, "Cone");
    exibirMatrizHabilidade(habilidadeCruz, "Cruz");
    exibirMatrizHabilidade(habilidadeOctaedro, "Octaedro (Losango)");

    // 3. Integrar Habilidades ao Tabuleiro
    printf("\nAplicando habilidades no tabuleiro...\n");
    // Define os pontos de origem para cada habilidade
    aplicarHabilidade(tabuleiro, habilidadeCone, 0, 4);      // Topo do tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCruz, 7, 2);      // Canto inferior esquerdo
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 5, 5);  // Centro do tabuleiro

    // 4. Exibir o Tabuleiro Final
    exibirTabuleiro(tabuleiro);

    return 0;
}

// --- FUNÇÕES DE GERAÇÃO DE HABILIDADES ---

/**
 * @brief Gera uma matriz 5x5 com um padrão de cone.
 * A forma é criada usando a condição: |coluna - centro| <= linha
 */
void criarMatrizCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(j - centro) <= i) {
                matriz[i][j] = 1; // Área afetada
            } else {
                matriz[i][j] = 0; // Área não afetada
            }
        }
    }
}

/**
 * @brief Gera uma matriz 5x5 com um padrão de cruz.
 * A forma é criada usando a condição: linha == centro OU coluna == centro
 */
void criarMatrizCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                matriz[i][j] = 1; // Área afetada
            } else {
                matriz[i][j] = 0; // Área não afetada
            }
        }
    }
}

/**
 * @brief Gera uma matriz 5x5 com um padrão de octaedro/losango.
 * A forma é criada pela "distância de Manhattan": |linha - centro| + |coluna - centro| <= centro
 */
void criarMatrizOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = 1; // Área afetada
            } else {
                matriz[i][j] = 0; // Área não afetada
            }
        }
    }
}

// --- FUNÇÕES DE LÓGICA E EXIBIÇÃO ---

/**
 * @brief Sobrepõe uma matriz de habilidade no tabuleiro principal.
 */
void aplicarHabilidade(int tabuleiro[][TAM_TABULEIRO], int habilidade[][TAM_HABILIDADE], int origem_linha, int origem_coluna) {
    int offset = TAM_HABILIDADE / 2;

    // Percorre a matriz de habilidade 5x5
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Se a posição na matriz de habilidade é uma área de efeito (valor 1)
            if (habilidade[i][j] == 1) {
                // Calcula a coordenada correspondente no tabuleiro principal
                int alvo_linha = origem_linha - offset + i;
                int alvo_coluna = origem_coluna - offset + j;

                // Validação: Garante que a área de efeito não saia dos limites do tabuleiro
                if (alvo_linha >= 0 && alvo_linha < TAM_TABULEIRO &&
                    alvo_coluna >= 0 && alvo_coluna < TAM_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro com o valor da habilidade
                    tabuleiro[alvo_linha][alvo_coluna] = EFEITO_HABILIDADE;
                }
            }
        }
    }
}

/**
 * @brief Exibe uma matriz de habilidade para fins de depuração e visualização.
 */
void exibirMatrizHabilidade(int matriz[TAM_HABILIDADE][TAM_HABILIDADE], const char* nomeHabilidade) {
    printf("--- Matriz Habilidade: %s ---\n", nomeHabilidade);
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------\n");
}


/**
 * @brief Exibe o tabuleiro do jogo com uma representação visual melhorada.
 */
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n=== TABULEIRO FINAL ===\n");
    printf("  ");
    for (int i = 0; i < TAM_TABULEIRO; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            char simbolo = '?';
            switch (tabuleiro[i][j]) {
                case AGUA:              simbolo = '~'; break; // Água
                case NAVIO:             simbolo = 'N'; break; // Navio
                case EFEITO_HABILIDADE: simbolo = '*'; break; // Efeito de habilidade
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
    printf("=======================\n");
    printf("Legenda: ~ Agua | N Navio | * Habilidade\n");
}

// Implementação da função posicionarNavio da etapa anterior (sem alterações)
bool posicionarNavio(int tabuleiro[][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    // Validação de limites
    switch (orientacao) {
        case 'H': if (coluna + TAM_NAVIO > TAM_TABULEIRO) return false; break;
        case 'V': if (linha + TAM_NAVIO > TAM_TABULEIRO) return false; break;
        case 'D': if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna + TAM_NAVIO > TAM_TABULEIRO) return false; break;
        case 'A': if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna - (TAM_NAVIO - 1) < 0) return false; break;
        default: return false;
    }
    // Validação de sobreposição e posicionamento
    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = linha, c = coluna;
        if(orientacao == 'H') c += i; else if(orientacao == 'V') r += i;
        else if(orientacao == 'D') { r += i; c += i; } else if(orientacao == 'A') { r += i; c -= i; }
        if (tabuleiro[r][c] != AGUA) return false;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = linha, c = coluna;
        if(orientacao == 'H') c += i; else if(orientacao == 'V') r += i;
        else if(orientacao == 'D') { r += i; c += i; } else if(orientacao == 'A') { r += i; c -= i; }
        tabuleiro[r][c] = NAVIO;
    }
    return true;
}