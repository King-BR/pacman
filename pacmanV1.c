/*
 *  Projeto de Linguagem de Progamação 1
 *  Jogo foge foge
 *  Feito por Pedro e Fernando
 *  Versão: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>

void pause(float delay1);
void constroe_mapa();
void imprime_mapa();

#define X 40
#define Y 20

int posXP,posYP;
int posXF1,posYF1;
int mapa[Y][X] = {0};
int player[Y][X] = {0};
int fantasmas[Y][X] = {0};

int main() {
    constroe_mapa();
    imprime_mapa();
    return 0;
}

void imprime_mapa() {
    int i,j;

    for (i = 0; i < Y; i++) {
        for (j = 0; j < X; j++) {
            switch (mapa[i][j]) {
                case 0: {
                    printf(" ");
                    break;
                }
                case 1: {
                    printf("#");
                    break;
                }
                case 2: {
                    printf(".");
                    break;
                }
            }
        }
        printf("\n");
    }
}

void constroe_mapa() {
    int i,j;
    for (i = 0; i < Y; i++) {
        for (j = 0; j < X; j++) {
            if (i == 0 || i == (Y - 1) || j == 0 || j == (X - 1)) {
                mapa[i][j] = 1;
            } else {
                mapa[i][j] = 2;
            }
        }
    }
}

void pause(float delay1) {
    if (delay1 < 0.001)
        return;

    float inst1 = 0, inst2 = 0;
    inst1 = (float)clock() / (float)CLOCKS_PER_SEC;

    while (inst2 - inst1 < delay1)
        inst2 = (float)clock() / (float)CLOCKS_PER_SEC;

    return;
}