/*
 *  Projeto de Linguagem de Progamação 1
 *  Jogo foge foge
 *  Feito por Pedro e Fernando
 *  Versão: 5.0
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
void loadmap1dificil();
void loadmap2dificil();
void loadmap3dificil();
void loadmap1medio();
void loadmap2medio();
void loadmap3medio();
void loadmap1facil();
void loadmap2facil();
void loadmap3facil();
void loadmaptest();
void dificil();
void medio();
void facil();
void ready();
void game();
void menu();
void map();
void W();
void A();
void S();
void D();

int main() {
    srand(time(NULL));

    //loadmaptest();

    // olha eu aqui dnv
    tela_de_carregamento();

    menu();

    pi = 1;
    pj = 1;
    player[pi][pj] = 1;
    pontos[pi][pj] = 1;

    //hackzinho pra ver conteudo da matriz mapa
    /*
    int i,j;
    for(i = 0;i < mi; i++) {
        printf(" linha %d\t %s\n",i, mapa[i]);
    }
    */

    game();

    return 0;
}

void menu() {
    int modo;
    printf("Escolha o modo de jogo:");
    printf("\n1) Facil\n2) Medio\n3) Dificil\n");
    scanf("%d", &modo);

    switch (modo) {
        case 1: {
            system("cls");
            facil();
            break;
        }
        case 2: {
            system("cls");
            medio();
            break;
        }
        case 3: {
            system("cls");
            dificil();
            break;
        }
        default: {
            printf("\n\nVoce digitou algo errado!\n");
            system("pause");
            system("cls");
            menu();
            break;
        }
    }
    return;
}

void facil() {
    int i;

    i = (rand() % 3);

    switch (i) {
        case 0: {
            loadmap1facil();
            break;
        }
        case 1: {
            loadmap2facil();
            break;
        }
        case 2: {
            loadmap3facil();
            break;
        }
    }
    return;
}

void medio() {
    int i;
    
    i = (rand() % 3);

    switch (i) {
        case 0: {
            loadmap1medio();
            break;
        }
        case 1: {
            loadmap2medio();
            break;
        }
        case 2: {
            loadmap3medio();
            break;
        }
    }
    return;
}

void dificil() {
    int i;
    
    i = (rand() % 3);

    switch (i) {
        case 0: {
            loadmap1dificil();
            break;
        }
        case 1: {
            loadmap2dificil();
            break;
        }
        case 2: {
            loadmap3dificil();
            break;
        }
    }
    return;
}

void loadmap1facil(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("1facil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    mi = 11;
    mj = 21;

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux) >= 20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmap2facil(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("2facil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    mi = 11;
    mj = 21;

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmap3facil(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("3facil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    mi = 11;
    mj = 21;

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmap1medio(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("1medio.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    mi = 16;
    mj = 31;


    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmap2medio(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("2medio.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    mi = 16;
    mj = 31;

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmap3medio(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("3medio.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    mi = 16;
    mj = 31;

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmap1dificil(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("1dificil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    mi = 21;
    mj = 41;

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmap2dificil(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("2dificil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }
    
    mi = 21;
    mj = 41;

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmap3dificil(){
    int i = 0,j = 0;
    char aux[41];
    FILE *mpt;
    mpt = fopen("3dificil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }
    
    mi = 21;
    mj = 41;

    while(i<21){
        fgets(aux, 41, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        }else{

        }
    }
}

void loadmaptest(){
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

    mi = 21;
    mj = 41;

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
    for (i = 0; i < mi; i++) {
        for (j = 0; j < mj; j++) {
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
    map();
    ready();

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

        pause(0.5);
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

void ready() {
    printf("\nReady?\n");
    pause(1);
    printf("\nGO!!");
    pause(0.5);
    system("cls");
    return;
}