#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 4

int main() {

    int tabuleiro[TAM][TAM];

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Inserindo os navios
    int navioHorizontal[3] = {3, 3, 3}; 
    int navioVertical[3] = {3, 3, 3};
    int navioDiagonal1[3] = {3, 3, 3};
    int navioDiagonal2[3] = {3, 3, 3};

    // Coordenadas iniciais dos navios (alterável)
    int linhaInicialHorizontal = 1;
    int colunaInicialHorizontal = 7;

    int linhaInicialVertical = 5;
    int colunaInicialVertical = 2;

    int linhaInicialDiagonal1 = 0;
    int colunaInicialDiagonal1 = 0;

    int linhaInicialDiagonal2 = 9;
    int colunaInicialDiagonal2 = 6;

        // Posiciona o navio horizontal (3 casas)
    for (int i = 0; i < 3; i++) {
        // Verifica se está dentro dos limites
        if (colunaInicialHorizontal + i < TAM) {
            tabuleiro[linhaInicialHorizontal][colunaInicialHorizontal + i] = navioHorizontal[i];
        }
    }

    // Posiciona o navio vertical (3 casas)
    for (int i = 0; i < 3; i++) {
        // Verifica se está dentro dos limites
        if (linhaInicialVertical + i < TAM) {
            // Verifica se não está sobrepondo o outro navio
            if (tabuleiro[linhaInicialVertical + i][colunaInicialVertical] == 0) {
                tabuleiro[linhaInicialVertical + i][colunaInicialVertical] = navioVertical[i];
            }
        }
    }
    // Navio diagonal 1(descendo)
    for (int i = 0; i < 3; i++) {
        if (linhaInicialDiagonal1 + i < TAM && colunaInicialDiagonal1 + i < TAM) {
            if (tabuleiro[linhaInicialDiagonal1 + i][colunaInicialDiagonal1 + i] == 0) {
                tabuleiro[linhaInicialDiagonal1 + i][colunaInicialDiagonal1 + i] = navioDiagonal1[i];
            }
        }
    }

    // Navio diagonal 2 (subindo)
    for (int i = 0; i < 3; i++) {
        if (linhaInicialDiagonal2 - i >= 0 && colunaInicialDiagonal2 + i < TAM) {
            if (tabuleiro[linhaInicialDiagonal2 - i][colunaInicialDiagonal2 + i] == 0) {
                tabuleiro[linhaInicialDiagonal2 - i][colunaInicialDiagonal2 + i] = navioDiagonal2[i];
            }
        }
    }

        // Matrizes de habilidade

    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // CONE - formato pirâmide apontando para baixo
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2) - i && j <= (TAM_HAB / 2) + i && i <= TAM_HAB / 2)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // CRUZ
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // OCTAEDRO (losango)
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }


    // Sobrepor habilidades no tabuleiro

    // Local dos centros das habilidades
    int origemConeLinha = 3, origemConeColuna = 3;
    int origemCruzLinha = 6, origemCruzColuna = 6;
    int origemOctaedroLinha = 4, origemOctaedroColuna = 8;

    // Função para aplicar uma matriz de habilidade ao tabuleiro
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {

            // Cone
            int linhaTab = origemConeLinha - TAM_HAB / 2 + i;
            int colunaTab = origemConeColuna - TAM_HAB / 2 + j;

            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM)
                if (cone[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == 0)
                    tabuleiro[linhaTab][colunaTab] = 5;

            // Cruz
            linhaTab = origemCruzLinha - TAM_HAB / 2 + i;
            colunaTab = origemCruzColuna - TAM_HAB / 2 + j;

            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM)
                if (cruz[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == 0)
                    tabuleiro[linhaTab][colunaTab] = 5;

            // Octaedro
            linhaTab = origemOctaedroLinha - TAM_HAB / 2 + i;
            colunaTab = origemOctaedroColuna - TAM_HAB / 2 + j;

            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM)
                if (octaedro[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == 0)
                    tabuleiro[linhaTab][colunaTab] = 5;
        }
    }

    //Exibir tabuleiro
    printf("\n===== TABULEIRO DE BATALHA NAVAL =====\n\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
