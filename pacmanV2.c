/*
 *  Projeto de Linguagem de Progamação 1
 *  Jogo foge foge
 *  Feito por Pedro e Fernando
 *  Versão: 2.0
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
int key;
int key2;
int player[20][40] = {};
int pontos[50][50] = {};
char mapa[50][50] = {'@'};


void keepwalking(int tecla, int walking);
void pause(float delay1);
void loadmap();
void game();
void map();
void W();
void A();
void S();
void D();

int main(){

    //mapa = (int*)malloc(20*20*sizeof(int));

    loadmap();

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

            /*
            if (player[i][j] == 1) {
                printf(">");
            }
            else if (player[i][j] == 2) {
                printf("<");
            }
            else if (player[i][j] == 3) {
                printf("v");
            }
            else if (player[i][j] == 4) {
                printf("^");
            }
            else {
                if (mapa[i][j] == ' ' && pontos[i][j] == 0) {
                    printf("*");
                } else if (mapa[i][j] == '@') {
                    printf(" ");
                } else {
                    printf("%c", mapa[i][j]);
                }
            }
            */

            fflush(stdin);
        }
        printf("\n");
    }
    return;
}

void game() {
    int walking = 0;
    for (;;) {
        map();
        keepwalking(key,walking);
        if (kbhit())
        {
            key = getch();

            switch (key) {
                case 'a':{
                    walking = 1;
                    A();
                    break;
                }
                case 's': {
                    walking = 2;
                    S();
                    break;
                }
                case 'd': {
                    walking = 3;
                    D();
                    break;
                }
                case 'w': {
                    walking = 4;
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

            /*
            if (key == 'a') {
                A();
            }
            else if (key == 's') {
                S();
            }
            else if (key == 'w') {
                W();
            }
            else if (key == 'd') {
                D();
            }
            else {}
            */
        }
        pause(1);
        system("cls");
    }
}

void keepwalking(int tecla, int walking) {
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
    if (mapa[pi][pj - 1] == '|' || mapa[pi][pj - 1] == '=')
        return;

    player[pi][pj] = 0;
    pj--;
    player[pi][pj] = 1;
    pontos[pi][pj] = 1;
    return;
}

void S() {
    if (mapa[pi + 1][pj] == '|' || mapa[pi + 1][pj] == '=')
        return;

    player[pi][pj] = 0;
    pi++;
    player[pi][pj] = 4;
    pontos[pi][pj] = 1;
    return;
}

void W() {
    if (mapa[pi - 1][pj] == '|' || mapa[pi - 1][pj] == '=')
        return;

    player[pi][pj] = 0;
    pi--;
    player[pi][pj] = 3;
    pontos[pi][pj] = 1;
    return;
}

void D() {
    if (mapa[pi][pj + 1] == '|' || mapa[pi][pj + 1] == '=')
        return;

    player[pi][pj] = 0;
    pj++;
    player[pi][pj] = 2;
    pontos[pi][pj] = 1;
    return;
}