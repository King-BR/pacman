/*
 *  Projeto de Linguagem de Progamação 1
 *  Jogo foge foge
 *  Feito por Pedro e Fernando
 *  Versão: 3.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>

int pi;
int pj;
int mi;
int mj;
int key;
int points = 0;
int walking = 0;
int player[50][100] = {};
int pontos[50][100] = {};
char mapa[50][100] = {'@'};

void keepwalking(int tecla);
void tela_de_carregamento();
void pause(float delay1);
void loadmap();
void game();
void menu();
void map();
void W();
void A();
void S();
void D();

int main(){

    //mapa = (int*)malloc(20*20*sizeof(int));

    loadmap();

    // olha eu dnv aqui
    tela_de_carregamento();

    int i,j;
    pi = 1;
    pj = 1;
    player[pi][pj] = 1;
    pontos[pi][pj] = 1;

    //hackzinho pra ver conteudo da matriz mapa
    /*
    for(i=0;i<20;i++){
        printf(" linha %d\t %s\n",i, mapa[i]);
    }
    */

    game();

    return 0;
}

void loadmap(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("mapadetest.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    /*
    for(i=0;i<=1;i++){
        fflush(stdin);
        fgets(aux, 21, mpt);
        printf("%s",aux);
        for(j=0;j<=20;j++){
            mapa[i][j] = aux[j];
        }
         strcpy(mapa[i], aux);
    }
    */

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }

}

void pause(float delay1) {
    if (delay1 < 0.001) return;

    float inst1 = 0, inst2 = 0;
    inst1 = (float)clock() / (float)CLOCKS_PER_SEC;
    while (inst2 - inst1 < delay1) inst2 = (float)clock() / (float)CLOCKS_PER_SEC;
    return;
}

void map() {
    int i, j;
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 40; j++) {
            switch (player[i][j]) {
                case 1: {
                    printf(">");
                    break;
                }
                case 2: {
                    printf("<");
                    break;
                }
                case 3: {
                    printf("v");
                    break;
                }
                case 4: {
                    printf("^");
                    break;
                }
                case 0: {
                    switch (mapa[i][j]) {
                        case ' ': {
                            if (pontos[i][j] == 0) {
                                printf("*");
                            } else {
                                printf(" ");
                            }
                            break;
                        }
                        case '@': {
                            printf(" ");
                            break;
                        }
                        default: {
                            printf("%c", mapa[i][j]);
                            break;
                        }
                    }
                }
            }

            fflush(stdin);
        }
        printf("\n");
    }
    return;
}

void game() {
    for (;;) {
        map();

        if (kbhit()) {
            key = getch();

            switch (key) {
                case 'a':{
                    A();
                    break;
                }
                case 's': {
                    S();
                    break;
                }
                case 'd': {
                    D();
                    break;
                }
                case 'w': {
                    W();
                    break;
                }
                default: {
                    switch (walking) {
                        case 1: {
                            A();
                            break;
                        }
                        case 2: {
                            S();
                            break;
                        }
                        case 3: {
                            D();
                            break;
                        }
                        case 4: {
                            W();
                            break;
                        }
                    }
                }
            }
        } else {
            keepwalking(key);
        }

        pause(1);
        system("cls");
    }
}

void keepwalking(int tecla) {
    switch (tecla) {
        case 'a': {
            A();
            break;
        }
        case 's': {
            S();
            break;
        }
        case 'd': {
            D();
            break;
        }
        case 'w': {
            W();
            break;
        }
        default: {
            switch (walking) {
                case 1: {
                    A();
                    break;
                }
                case 2: {
                    S();
                    break;
                }
                case 3: {
                    D();
                    break;
                }
                case 4: {
                    W();
                    break;
                }
            }
        }
    }
    return;
}

void A() {
    if (mapa[pi][pj - 1] == '|' || mapa[pi][pj - 1] == '=') {
        switch (walking) {
            case 2: {
                S();
                break;
            }
            case 3: {
                D();
                break;
            }
            case 4: {
                W();
                break;
            }
        }
        return;
    }

    walking = 1;
    player[pi][pj] = 0;
    pj--;
    player[pi][pj] = 1;
    pontos[pi][pj] = 1;
    return;
}

void S() {
    if (mapa[pi + 1][pj] == '|' || mapa[pi + 1][pj] == '=') {
        switch (walking) {
            case 1: {
                A();
                break;
            }
            case 3: {
                D();
                break;
            }
            case 4: {
                W();
                break;
            }
        }
        return;
    }

    walking = 2;
    player[pi][pj] = 0;
    pi++;
    player[pi][pj] = 4;
    pontos[pi][pj] = 1;
    return;
}

void D() {
    if (mapa[pi][pj + 1] == '|' || mapa[pi][pj + 1] == '=') {
        switch (walking) {
            case 1: {
                A();
                break;
            }
            case 2: {
                S();
                break;
            }
            case 4: {
                W();
                break;
            }
        }
        return;
    }

    walking = 3;
    player[pi][pj] = 0;
    pj++;
    player[pi][pj] = 2;
    pontos[pi][pj] = 1;
    return;
}


void W() {
    if (mapa[pi - 1][pj] == '|' || mapa[pi - 1][pj] == '=') {
        switch (walking) {
            case 1: {
                A();
                break;
            }
            case 2: {
                S();
                break;
            }
            case 3: {
                D();
                break;
            }
        }
        return;
    }

    walking = 4;
    player[pi][pj] = 0;
    pi--;
    player[pi][pj] = 3;
    pontos[pi][pj] = 1;
    return;
}

void tela_de_carregamento() {
    int i;
    printf("Loading program...\n");
    for (i = 0; i < 25; i++) {
        pause(0.05);
        printf("=");
    }
    printf("\n\nFinishing installation");
    pause(0.3);
    printf(".");
    pause(0.3);
    printf(".");
    pause(0.3);
    printf(".\n\n");
    pause(0.3);
    printf("Jogo feito por Pedro e Fernando\n\n");
    pause(2);
    system("cls");
}