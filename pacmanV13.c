/*
 *  Universidade IFMA
 *  Projeto de Linguagem de Progamação 1
 *  Jogo foge foge
 *  Feito por Pedro e Fernando
 *  Versão: 13
 */



// bibliotecas usadas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>



// variaveis globais
int mi,mj; // tamanho do mapa
char mapa[50][100] = {'@'}; // matriz do mapa

int walking = 0; // movimento do pacman
char key; // tecla apertada no teclado
int pi,pj; // posição do pacman na matriz
int player[50][100] = {0}; // matriz do pacman

int vitoria; // auxiliar que detecta se o pacman ja comeu todos os pontos do mapa
int points = 0; // pontos atuais
int pontos[50][100] = {0}; // matriz dos pontos
int tempopilula = -1; // tempo de duração da pilula

int F1 = 0,F2 = 0,F3 = 0,F4 = 0; // status do fantasma (0 = morto | 1 = vivo)
int F1i,F1j; // posição do fantasma 1
int F2i,F2j; // posição do fantasma 2
int F3i,F3j; // posição do fantasma 3
int F4i,F4j; // posição do fantasma 4
int tempofanta; // tempo do fantasma spawnar
int walkingF1 = 0; // movimento do fantasma 1
int walkingF2 = 0; // movimento do fantasma 2
int walkingF3 = 0; // movimento do fantasma 3
int walkingF4 = 0; // movimento do fantasma 4
int fanta1[50][100] = {0}; // matriz do fantasma 1
int fanta2[50][100] = {0}; // matriz do fantasma 2
int fanta3[50][100] = {0}; // matriz do fantasma 3
int fanta4[50][100] = {0}; // matriz do fantasma 4



// funções
void jogo(); // função principal do jogo
void jogarnvm(); // pergunta se o jogador que jogar novamente
void game(); // função do jogo em si
void reset(); // reseta as variaveis globais caso o jogador queira jogar novamente
void matarfanta(); // função q faz o pacman matar os fantasmas
int perdeu(); // detecta se o pacman foi morto

void tela_de_carregamento(); // animação da tela de carregamento
void ready(); // animação do ready
void pause(float delay1); // função de pause por tempo em segundos
void caveira_fechada(); // caveira com a boca fechada
void caveira_aberta(); // caveira com a boca aberta
void animacao_caveira(); // animação da caveira
void ganhou(); // printa a imagem do trofeu

void movimentofanta1(); // movimento do fantasma 1
void movimentofanta2(); // movimento do fantasma 2
void movimentofanta3(); // movimento do fantasma 3
void movimentofanta4(); // movimento do fantasma 4

void menu(); // menu de escolha da dificuldade
void loadmaptest(); // load do mapa de teste
void map(); // printa o mapa na tela junto com o pacman, fantasmas e pontos

void dificil(); // escolha aleatorio do mapa dificil
void loadmap1dificil(); // load do mapa dificil 1
void loadmap2dificil(); // load do mapa dificil 2
void loadmap3dificil(); // load do mapa dificil 3

void medio(); // escolha aleatorio do mapa medio
void loadmap1medio(); // load do mapa medio 1
void loadmap2medio(); // load do mapa medio 2
void loadmap3medio(); // load do mapa medio 3

void facil(); // escolha aleatorio do mapa facil
void loadmap1facil(); // load do mapa facil 1
void loadmap2facil(); // load do mapa facil 2
void loadmap3facil(); // load do mapa facil 3

void keepwalking(int tecla); // movimento automatico do pacman
void W(); // movimento para cima do pacman
void A(); // movimento para esquerda do pacman
void S(); // movimento para baixo do pacman
void D(); // movimento para direita do pacman



int main() {
    // define a seed da função rand() para a hora do relogio fazendo com que os numeros sejam sempre aleatorios
    srand(time(NULL));

    // essa função faz uma animação de tela de carregamento 
    tela_de_carregamento();

    // defini a posição inicial do pacman
    pi = 1;
    pj = 1;
    player[pi][pj] = 1;
    pontos[pi][pj] = 1;

    // função principal do jogo
    jogo();

    return 0;
}

void jogo() {
    // chama a função menu para o jogador escolher a dificuldade do jogo
    menu();
    
    // mapa de teste 
    // loadmaptest();

    // função do jogo em si
    game();

    // pergunta se quer jogar novamente
    jogarnvm();

    return;
}

void jogarnvm() {
    char nvm;

    printf("\nDeseja jogar novamente? (S/N)\n");
    fflush(stdin);
    scanf("%c", &nvm);

    switch (nvm) {
        case 'S': {
            system("cls");
            reset();
            jogo();
            break;
        }
        case 's': {
            system("cls");
            reset();
            jogo();
            break;
        }
        case 'N': {
            printf("\n\nTchau!\n");
            break;
        }
        case 'n': {
            printf("\n\nTchau!\n");
            break;
        }
        default: {
            printf("\n\nVoce digitou algo errado!Tente novamente\n");
            system("pause");
            system("cls");
            jogarnvm();
            break;
        }
    }
    return;
}

// printa o mapa
void map() {
    int i, j;

    vitoria = 1;

    for (i = 0; i < mi; i++) {
        for (j = 0; j < mj; j++) {
            
            // detecta o lugar de nascimento dos fantasmas
            if (mapa[i][j] == '#') {
                mapa[i][j] = '@';
                F1i = F2i = F3i = F4i = i;
                F1j = F2j = F3j = F4j = j;
            }

            // detecta a posição do pacman
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
                default: {
                    // verifica se é pra spawnar os fantasmas
                    switch (tempofanta) {
                        case 10: {
                            fanta1[F1i][F1j] = 1;
                            F1 = 1;
                            break;
                        }
                        case 20: {
                            fanta2[F2i][F2j] = 1;
                            F2 = 1;
                            break;
                        }
                        case 30: {
                            fanta3[F3i][F3j] = 1;
                            F3 = 1;
                            break;
                        }
                        case 40: {
                            fanta4[F4i][F4j] = 1;
                            F4 = 1;
                            break;
                        }
                    }

                    // printa o fantasma 4
                    if (fanta4[i][j] == 1 && F4 == 1) {
                        printf("4");
                        break;
                    }

                    // printa o fantasma 3
                    if (fanta3[i][j] == 1 && F3 == 1) {
                        printf("3");
                        break;
                    }

                    // printa o fantasma 2
                    if (fanta2[i][j] == 1 && F2 == 1) {
                        printf("2");
                        break;
                    }

                    // printa o fantasma 1
                    if (fanta1[i][j] == 1 && F1 == 1) {
                        printf("1");
                        break;
                    }

                    // printa o mapa
                    switch (mapa[i][j]) {
                        case '0':
                            if (pontos[i][j] == 1) {
                                printf(" ");
                                break;
                            }
                            pontos[i][j] = 2;
                            printf("0");
                            break;
                        case ' ': {
                            if (pontos[i][j] == 0) {
                                vitoria = 0;
                                printf("*");
                            } else{
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
        // pula pra proxima linha do mapa
        printf("\n");
    }
    // printa a quantidade de pontos na tela
    printf("\npontos: %d", points);
    return;
}

// menu de escolha da dificuldade
void menu() {
    int modo;
    printf("Escolha o modo de jogo:");
    printf("\n1) Facil\n2) Medio\n3) Dificil\n");
    scanf("%d", &modo);

    // nesse switch ele da load no mapa de acordo com a dificuldade escolhida
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

// essa função da load em um mapa facil aleatorio 
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

// essa função da load em um mapa medio aleatorio 
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

// essa função da load em um mapa dificil aleatorio 
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

// funções de load dos mapas
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
        } else{

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
        } else{

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
        } else{

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
        } else{

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
        } else{

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
        } else{

        }
    }
}

void loadmap1dificil(){
    int i = 0,j = 0;
    char aux[42];
    FILE *mpt;
    mpt = fopen("1dificil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }

    mi = 21;
    mj = 42;

    while(i<21){
        fgets(aux, 42, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        } else{

        }
    }
}

void loadmap2dificil(){
    int i = 0,j = 0;
    char aux[42];
    FILE *mpt;
    mpt = fopen("2dificil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }
    
    mi = 21;
    mj = 42;

    while(i<21){
        fgets(aux, 42, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        } else{

        }
    }
}

void loadmap3dificil(){
    int i = 0,j = 0;
    char aux[42];
    FILE *mpt;
    mpt = fopen("3dificil.txt","r");
    if(mpt == NULL){
        printf("Mapa n Carregado");
        return;
    }
    
    mi = 21;
    mj = 42;

    while(i<21){
        fgets(aux, 42, mpt);
        if(strlen(aux)>=20){
            strcpy(mapa[i],aux);
            i++;
        } else{

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
        } else{

        }
    }

}

// função de pause por tempo
void pause(float delay1) {
    if (delay1 < 0.001) return;

    float inst1 = 0, inst2 = 0;
    inst1 = (float)clock() / (float)CLOCKS_PER_SEC;
    while (inst2 - inst1 < delay1) inst2 = (float)clock() / (float)CLOCKS_PER_SEC;
    return;
}

// função do jogo
void game() {
    int aux = 0;
    // printa o mapa na tela
    map();

    printf("\n\nDica: So precisa apertar uma vez para que o\n      pacman se mova para direcao desejada\n");
    pause(1.2);

    // animação de ready
    ready();

    for (;;) {
        // tempo pra spawnar os fantasmas
        tempofanta++;

        // aqui é o timer da pilula
        if(tempopilula > 0) {
            tempopilula--;
        } else if (tempopilula == 0) {
            system("color 0F");
            tempopilula = -1;
        }

        // printa o mapa na tela
        map();

        // detecta se tem pilula ou não
        if(tempopilula > 0) {
            matarfanta();
        } else {
            // aqui ele detecta se o fantasma matou o pacman
            aux = perdeu();
            if (aux == 1) return;
        }

        // aqui ele detecta se alguma tecla foi apertada
        if (kbhit()) {

            // aqui ele pega a tecla apertada
            key = getch();

            // switch da tecla
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
                    // se a tecla apertada for diferente de wasd ele continua com o movimento
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
            // se nao tiver apertado nenhuma tecla ele continua a se movimentar
            keepwalking(key);
        }

        // movimentos dos fantasmas
        movimentofanta1();
        movimentofanta2();
        movimentofanta3();
        movimentofanta4();


        if (vitoria == 1) {
            system("color 0F");
            ganhou();
            return;
        }
       
        pause(0.4);
        system("cls");
    }
}

// aqui é pra fazer o pacman continuar a se movimentar sem precisar ficar apertando wasd varias vezes
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

// movimentação do pacman
void A() {
    // se a direção que o pacman tiver indo tiver uma parede
    if (mapa[pi][pj - 1] == '|' || mapa[pi][pj - 1] == '=') {
        // ele tenta fazer o movimento anterior
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
        // se nao for possivel se movimentar ele para
        return;
    }

    walking = 1;
    player[pi][pj] = 0;
    pj--;
    player[pi][pj] = 1;

    if (pontos[pi][pj] == 0) {
        pontos[pi][pj] = 1;
        points++;
    }else if(pontos[pi][pj] == 2) {
        tempopilula = 20;
        system("color 1F");
        pontos[pi][pj] = 1;
        points++;
    }
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

    if (pontos[pi][pj] == 0) {
        pontos[pi][pj] = 1;
        points++;
    }else if(pontos[pi][pj] == 2) {
        tempopilula = 20;
        system("color 1F");
        pontos[pi][pj] = 1;
        points++;
    }
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

    if (pontos[pi][pj] == 0) {
        pontos[pi][pj] = 1;
        points++;
    }else if(pontos[pi][pj] == 2) {
        tempopilula = 20;
        system("color 1F");
        pontos[pi][pj] = 1;
        points++;
    }
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

    if (pontos[pi][pj] == 0) {
        pontos[pi][pj] = 1;
        points++;
    }else if(pontos[pi][pj] == 2) {
        tempopilula = 20;
        system("color 1F");
        pontos[pi][pj] = 1;
        points++;
    }
    return;
}

// animação da tela de carregamento ${}
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

// animação do ready
void ready() {
    printf("\nReady?\n");
    pause(1);
    printf("\nGO!!");
    pause(0.5);
    system("cls");
    return;
}

// movimento dos fantasmas
void movimentofanta1() {
    if (F1 == 0) return;

    // debug do movimento do fantasma 1
    // printf("\nfanta1: %d",walkingF1);

    switch (walkingF1) {
        case 0: {
            if (mapa[F1i][F1j - 1] == ' ' || mapa[F1i][F1j - 1] == '@') {
                walkingF1 = 1;
            } else if (mapa[F1i + 1][F1j] == ' ' || mapa[F1i + 1][F1j] == '@') {
                walkingF1 = 2;
            } else if (mapa[F1i][F1j + 1] == ' ' || mapa[F1i][F1j + 1] == '@') {
                walkingF1 = 3;
            } else if (mapa[F1i - 1][F1j] == ' ' || mapa[F1i - 1] [F1j] == '@') {
                walkingF1 = 4;
            }
            break;
        }
        case 1: {
            if (mapa[F1i - 1][F1j] == ' ' || mapa[F1i + 1][F1j] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F1i - 1][F1j] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 4;

                        fanta1[F1i][F1j] = 0;
                        F1i--;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F1i + 1][F1j] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 2;

                        fanta1[F1i][F1j] = 0;
                        F1i++;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F1i][F1j - 1] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 1;

                        fanta1[F1i][F1j] = 0;
                        F1j--;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F1i][F1j + 1] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 3;

                        fanta1[F1i][F1j] = 0;
                        F1j++;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta1();
                        break;
                    }
                }
                break;

            } else {
                walkingF1 = 1;

                fanta1[F1i][F1j] = 0;
                F1j--;
                fanta1[F1i][F1j] = 1;
            }

            break;
        }
        case 2: {
            if (mapa[F1i][F1j - 1] == ' ' || mapa[F1i][F1j + 1] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F1i - 1][F1j] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 4;

                        fanta1[F1i][F1j] = 0;
                        F1i--;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F1i + 1][F1j] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 2;

                        fanta1[F1i][F1j] = 0;
                        F1i++;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F1i][F1j - 1] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 1;

                        fanta1[F1i][F1j] = 0;
                        F1j--;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F1i][F1j + 1] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 3;

                        fanta1[F1i][F1j] = 0;
                        F1j++;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta1();
                        break;
                    }
                }
                break;

            } else {
                walkingF1 = 2;

                fanta1[F1i][F1j] = 0;
                F1i++;
                fanta1[F1i][F1j] = 1;
            }

            break;
        }
        case 3: {
            if (mapa[F1i - 1][F1j] == ' ' || mapa[F1i + 1][F1j] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F1i - 1][F1j] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 4;

                        fanta1[F1i][F1j] = 0;
                        F1i--;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F1i + 1][F1j] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 2;

                        fanta1[F1i][F1j] = 0;
                        F1i++;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F1i][F1j - 1] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 1;

                        fanta1[F1i][F1j] = 0;
                        F1j--;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F1i][F1j + 1] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 3;

                        fanta1[F1i][F1j] = 0;
                        F1j++;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta1();
                        break;
                    }
                }
                break;

            } else {
                walkingF1 = 3;

                fanta1[F1i][F1j] = 0;
                F1j++;
                fanta1[F1i][F1j] = 1;
            }
            
            break;
        }
        case 4: {
            if (mapa[F1i][F1j - 1] == ' ' || mapa[F1i][F1j + 1] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F1i - 1][F1j] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 4;

                        fanta1[F1i][F1j] = 0;
                        F1i--;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F1i + 1][F1j] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 2;

                        fanta1[F1i][F1j] = 0;
                        F1i++;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F1i][F1j - 1] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 1;

                        fanta1[F1i][F1j] = 0;
                        F1j--;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F1i][F1j + 1] != ' ') {
                            movimentofanta1();
                            break;
                        }

                        walkingF1 = 3;

                        fanta1[F1i][F1j] = 0;
                        F1j++;
                        fanta1[F1i][F1j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta1();
                        break;
                    }
                }
                break;

            } else {
                walkingF1 = 4;

                fanta1[F1i][F1j] = 0;
                F1i--;
                fanta1[F1i][F1j] = 1;
            }
            
            break;
        }
    }
}

void movimentofanta2() {
    if (F2 == 0) return;

    // debug do movimento do fantasma 2
    // printf("\nfanta2: %d",walkingF2);

    switch (walkingF2) {
        case 0: {
            if (mapa[F2i][F2j - 1] == ' ' || mapa[F2i][F2j - 1] == '@') {
                walkingF2 = 1;
            } else if (mapa[F2i + 1][F2j] == ' ' || mapa[F2i + 1][F2j] == '@') {
                walkingF2 = 2;
            } else if (mapa[F2i][F2j + 1] == ' ' || mapa[F2i][F2j + 1] == '@') {
                walkingF2 = 3;
            } else if (mapa[F2i - 1][F2j] == ' ' || mapa[F2i - 1] [F2j] == '@') {
                walkingF2 = 4;
            }
            break;
        }
        case 1: {
            if (mapa[F2i - 1][F2j] == ' ' || mapa[F2i + 1][F2j] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F2i - 1][F2j] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 4;

                        fanta2[F2i][F2j] = 0;
                        F2i--;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F2i + 1][F2j] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 2;

                        fanta2[F2i][F2j] = 0;
                        F2i++;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F2i][F2j - 1] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 1;

                        fanta2[F2i][F2j] = 0;
                        F2j--;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F2i][F2j + 1] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 3;

                        fanta2[F2i][F2j] = 0;
                        F2j++;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta2();
                        break;
                    }
                }
                break;

            } else {
                walkingF2 = 1;

                fanta2[F2i][F2j] = 0;
                F2j--;
                fanta2[F2i][F2j] = 1;
            }
            
            break;
        }
        case 2: {
            if (mapa[F2i][F2j - 1] == ' ' || mapa[F2i][F2j + 1] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F2i - 1][F2j] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 4;

                        fanta2[F2i][F2j] = 0;
                        F2i--;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F2i + 1][F2j] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 2;

                        fanta2[F2i][F2j] = 0;
                        F2i++;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F2i][F2j - 1] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 1;

                        fanta2[F2i][F2j] = 0;
                        F2j--;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F2i][F2j + 1] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 3;

                        fanta2[F2i][F2j] = 0;
                        F2j++;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta2();
                        break;
                    }
                }
                break;

            } else {
                walkingF2 = 2;

                fanta2[F2i][F2j] = 0;
                F2i++;
                fanta2[F2i][F2j] = 1;
            }
            
            break;
        }
        case 3: {
            if (mapa[F2i - 1][F2j] == ' ' || mapa[F2i + 1][F2j] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F2i - 1][F2j] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 4;

                        fanta2[F2i][F2j] = 0;
                        F2i--;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F2i + 1][F2j] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 2;

                        fanta2[F2i][F2j] = 0;
                        F2i++;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F2i][F2j - 1] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 1;

                        fanta2[F2i][F2j] = 0;
                        F2j--;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F2i][F2j + 1] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 3;

                        fanta2[F2i][F2j] = 0;
                        F2j++;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta2();
                        break;
                    }
                }
                break;

            } else {
                walkingF2 = 3;

                fanta2[F2i][F2j] = 0;
                F2j++;
                fanta2[F2i][F2j] = 1;
            }
            
            break;
        }
        case 4: {
            if (mapa[F2i][F2j - 1] == ' ' || mapa[F2i][F2j + 1] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F2i - 1][F2j] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 4;

                        fanta2[F2i][F2j] = 0;
                        F2i--;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F2i + 1][F2j] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 2;

                        fanta2[F2i][F2j] = 0;
                        F2i++;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F2i][F2j - 1] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 1;

                        fanta2[F2i][F2j] = 0;
                        F2j--;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F2i][F2j + 1] != ' ') {
                            movimentofanta2();
                            break;
                        }

                        walkingF2 = 3;

                        fanta2[F2i][F2j] = 0;
                        F2j++;
                        fanta2[F2i][F2j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta2();
                        break;
                    }
                }
                break;

            } else {
                walkingF2 = 4;

                fanta2[F2i][F2j] = 0;
                F2i--;
                fanta2[F2i][F2j] = 1;
            }
            break;
        }
    }
}

void movimentofanta3() {
    if (F3 == 0) return;

    // debug do movimento do fantasma 3
    // printf("\nfanta3: %d",walkingF3);

    switch (walkingF3) {
        case 0: {
            if (mapa[F3i][F3j - 1] == ' ' || mapa[F3i][F3j - 1] == '@') {
                walkingF3 = 1;
            } else if (mapa[F3i + 1][F3j] == ' ' || mapa[F3i + 1][F3j] == '@') {
                walkingF3 = 2;
            } else if (mapa[F3i][F3j + 1] == ' ' || mapa[F3i][F3j + 1] == '@') {
                walkingF3 = 3;
            } else if (mapa[F3i - 1][F3j] == ' ' || mapa[F3i - 1] [F3j] == '@') {
                walkingF3 = 4;
            }
            break;
        }
        case 1: {
            if (mapa[F3i - 1][F3j] == ' ' || mapa[F3i + 1][F3j] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F3i - 1][F3j] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 4;

                        fanta3[F3i][F3j] = 0;
                        F3i--;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F3i + 1][F3j] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 2;

                        fanta3[F3i][F3j] = 0;
                        F3i++;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F3i][F3j - 1] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 1;

                        fanta3[F3i][F3j] = 0;
                        F3j--;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F3i][F3j + 1] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 3;

                        fanta3[F3i][F3j] = 0;
                        F3j++;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta3();
                        break;
                    }
                }
                break;
            
            } else {
                walkingF3 = 1;

                fanta3[F3i][F3j] = 0;
                F3j--;
                fanta3[F3i][F3j] = 1;
            }

            break;
        }
        case 2: {
            if (mapa[F3i][F3j - 1] == ' ' || mapa[F3i][F3j + 1] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F3i - 1][F3j] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 4;

                        fanta3[F3i][F3j] = 0;
                        F3i--;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F3i + 1][F3j] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 2;

                        fanta3[F3i][F3j] = 0;
                        F3i++;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F3i][F3j - 1] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 1;

                        fanta3[F3i][F3j] = 0;
                        F3j--;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F3i][F3j + 1] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 3;

                        fanta3[F3i][F3j] = 0;
                        F3j++;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta3();
                        break;
                    }
                }
                break;

            } else {
                walkingF3 = 2;

                fanta3[F3i][F3j] = 0;
                F3i++;
                fanta3[F3i][F3j] = 1;
            }
            
            break;
        }
        case 3: {
            if (mapa[F3i - 1][F3j] == ' ' || mapa[F3i + 1][F3j] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F3i - 1][F3j] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 4;

                        fanta3[F3i][F3j] = 0;
                        F3i--;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F3i + 1][F3j] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 2;

                        fanta3[F3i][F3j] = 0;
                        F3i++;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F3i][F3j - 1] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 1;

                        fanta3[F3i][F3j] = 0;
                        F3j--;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F3i][F3j + 1] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 3;

                        fanta3[F3i][F3j] = 0;
                        F3j++;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta3();
                        break;
                    }
                }

                break;
            } else {
                walkingF3 = 3;

                fanta3[F3i][F3j] = 0;
                F3j++;
                fanta3[F3i][F3j] = 1;
            }
            
            break;
        }
        case 4: {
            if (mapa[F3i][F3j - 1] == ' ' || mapa[F3i][F3j + 1] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F3i - 1][F3j] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 4;

                        fanta3[F3i][F3j] = 0;
                        F3i--;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F3i + 1][F3j] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 2;

                        fanta3[F3i][F3j] = 0;
                        F3i++;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F3i][F3j - 1] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 1;

                        fanta3[F3i][F3j] = 0;
                        F3j--;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F3i][F3j + 1] != ' ') {
                            movimentofanta3();
                            break;
                        }

                        walkingF3 = 3;

                        fanta3[F3i][F3j] = 0;
                        F3j++;
                        fanta3[F3i][F3j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta3();
                        break;
                    }
                }
                break;

            } else {
                walkingF3 = 4;

                fanta3[F3i][F3j] = 0;
                F3i--;
                fanta3[F3i][F3j] = 1;
            }
            
            break;
        }
    }
}

void movimentofanta4() {
    if (F4 == 0) return;

    // debug do movimento do fantasma 4
    // printf("\nfanta4: %d",walkingF4);

    switch (walkingF4) {
        case 0: {
            if (mapa[F4i][F4j - 1] == ' ' || mapa[F4i][F4j - 1] == '@') {
                walkingF4 = 1;
            } else if (mapa[F4i + 1][F4j] == ' ' || mapa[F4i + 1][F4j] == '@') {
                walkingF4 = 2;
            } else if (mapa[F4i][F4j + 1] == ' ' || mapa[F4i][F4j + 1] == '@') {
                walkingF4 = 3;
            } else if (mapa[F4i - 1][F4j] == ' ' || mapa[F4i - 1] [F4j] == '@') {
                walkingF4 = 4;
            }
            break;
        }
        case 1: {
            if (mapa[F4i - 1][F4j] == ' ' || mapa[F4i + 1][F4j] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F4i - 1][F4j] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 4;

                        fanta4[F4i][F4j] = 0;
                        F4i--;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F4i + 1][F4j] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 2;

                        fanta4[F4i][F4j] = 0;
                        F4i++;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F4i][F4j - 1] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 1;
                        
                        fanta4[F4i][F4j] = 0;
                        F4j--;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F4i][F4j + 1] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 3;

                        fanta4[F4i][F4j] = 0;
                        F4j++;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta4();
                        break;
                    }
                }
                break;

            } else {
                walkingF4 = 1;

                fanta4[F4i][F4j] = 0;
                F4j--;
                fanta4[F4i][F4j] = 1;
            }
            
            break;
        }
        case 2: {
            if (mapa[F4i][F4j - 1] == ' ' || mapa[F4i][F4j + 1] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F4i - 1][F4j] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 4;

                        fanta4[F4i][F4j] = 0;
                        F4i--;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F4i + 1][F4j] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 2;

                        fanta4[F4i][F4j] = 0;
                        F4i++;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F4i][F4j - 1] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 1;
                        
                        fanta4[F4i][F4j] = 0;
                        F4j--;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F4i][F4j + 1] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 3;

                        fanta4[F4i][F4j] = 0;
                        F4j++;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta4();
                        break;
                    }
                }
                break;

            } else {
                walkingF4 = 2;

                fanta4[F4i][F4j] = 0;
                F4i++;
                fanta4[F4i][F4j] = 1;
            }
            
            break;
        }
        case 3: {
            if (mapa[F4i - 1][F4j] == ' ' || mapa[F4i + 1][F4j] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F4i - 1][F4j] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 4;

                        fanta4[F4i][F4j] = 0;
                        F4i--;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F4i + 1][F4j] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 2;

                        fanta4[F4i][F4j] = 0;
                        F4i++;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F4i][F4j - 1] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 1;
                        
                        fanta4[F4i][F4j] = 0;
                        F4j--;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F4i][F4j + 1] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 3;

                        fanta4[F4i][F4j] = 0;
                        F4j++;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta4();
                        break;
                    }
                }
                break;

            } else {
                walkingF4 = 3;

                fanta4[F4i][F4j] = 0;
                F4j++;
                fanta4[F4i][F4j] = 1;
            }
            
            break;
        }
        case 4: {
            if (mapa[F4i][F4j - 1] == ' ' || mapa[F4i][F4j + 1] == ' ') {
                switch ((rand() % 4)) {
                    case 0: {
                        if(mapa[F4i - 1][F4j] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 4;

                        fanta4[F4i][F4j] = 0;
                        F4i--;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 1: {
                        if(mapa[F4i + 1][F4j] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 2;

                        fanta4[F4i][F4j] = 0;
                        F4i++;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 2: {
                        if(mapa[F4i][F4j - 1] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 1;
                        
                        fanta4[F4i][F4j] = 0;
                        F4j--;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    case 3: {
                        if(mapa[F4i][F4j + 1] != ' ') {
                            movimentofanta4();
                            break;
                        }

                        walkingF4 = 3;

                        fanta4[F4i][F4j] = 0;
                        F4j++;
                        fanta4[F4i][F4j] = 1;
                        break;
                    }
                    default: {
                        movimentofanta4();
                        break;
                    }
                }
                break;

            } else {
                walkingF4 = 4;

                fanta4[F4i][F4j] = 0;
                F4i--;
                fanta4[F4i][F4j] = 1;
            }
            
            break;
        }
    }
}

void caveira_fechada() {
    printf("        Voce perdeu!       \n");
    printf("                           \n");
    printf("       ---0000000---       \n");
    printf("    -00000000000000000-    \n");
    printf("   |0000000000000000000|   \n");
    printf("   |0000000000000000000|   \n");
    printf("  0|0000000000000000000|0  \n");
    printf("  00|00000000000000000|00  \n");
    printf("  00|0     00000     0|00  \n");
    printf("   0|       000       |0   \n");
    printf("   0|      00_00      |0   \n");
    printf("    |0000000___0000000|    \n");
    printf("   000___000-_-000___000   \n");
    printf("      |___0000000___|      \n");
    printf("     00__TTTTTTTTT__00     \n");
    printf("     000-TTTTTTTTT-000     \n");
    printf("      000TTTTTTTTT000      \n");
    printf("        00000000000        \n\n");
}

void caveira_aberta() {
    printf("        Voce perdeu!       \n");
    printf("                           \n");
    printf("       ---0000000---       \n");
    printf("    -00000000000000000-    \n");
    printf("   |0000000000000000000|   \n");
    printf("   |0000000000000000000|   \n");
    printf("  0|0000000000000000000|0  \n");
    printf("  00|00000000000000000|00  \n");
    printf("  00|0     00000     0|00  \n");
    printf("   0|       000       |0   \n");
    printf("   0|      00_00      |0   \n");
    printf("    |0000000___0000000|    \n");
    printf("   000___000-_-000___000   \n");
    printf("      |___0000000___|      \n");
    printf("     00__TTTTTTTTT__00     \n");
    printf("     000-         -000     \n");
    printf("      000TTTTTTTTT000      \n");
    printf("        00000000000        \n\n");
}

void animacao_caveira() {
    caveira_fechada();
    pause(0.5);
    system("cls");
    caveira_aberta();
    pause(0.5);
    system("cls");
    caveira_fechada();
    pause(0.5);
    system("cls");
    caveira_aberta();
    pause(0.5);
    system("cls");
    caveira_fechada();
}

int perdeu() {
    if(fanta1[pi][pj] == 1 || fanta2[pi][pj] == 1 || fanta3[pi][pj] == 1 || fanta4[pi][pj] == 1) {
        printf("\n\n");
        system("color 0F");
        system("pause");
        system("cls");
        animacao_caveira();
        return 1;
    } else if(fanta1[pi][pj - 1] == 1 || fanta2[pi][pj - 1] == 1 || fanta3[pi][pj - 1] == 1 || fanta4[pi][pj - 1] == 1) {
        printf("\n\n");
        system("color 0F");
        system("pause");
        system("cls");
        animacao_caveira();
        return 1;
    } else if(fanta1[pi][pj + 1] == 1 || fanta2[pi][pj + 1] == 1 || fanta3[pi][pj + 1] == 1 || fanta4[pi][pj + 1] == 1) {
        printf("\n\n");
        system("color 0F");
        system("pause");
        system("cls");
        animacao_caveira();
        return 1;
    } else if(fanta1[pi - 1][pj] == 1 || fanta2[pi - 1][pj] == 1 || fanta3[pi - 1][pj] == 1 || fanta4[pi - 1][pj] == 1) {
        printf("\n\n");
        system("color 0F");
        system("pause");
        system("cls");
        animacao_caveira();
        return 1;
    } else if(fanta1[pi + 1][pj] == 1 || fanta2[pi + 1][pj] == 1 || fanta3[pi + 1][pj] == 1 || fanta4[pi + 1][pj] == 1) {
        printf("\n\n");
        system("color 0F");
        system("pause");
        system("cls");
        animacao_caveira();
        return 1;
    }
}

void ganhou() {
    printf("\n\n");
    system("pause");
    system("cls");
    printf("      Voce Ganhou!!!    \n");
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
    return;
}

void reset() {
    int i,j;

    for (i = 0; i < 50; i++) {
        for (j = 0; j < 100; j++) {
            mapa[i][j] = '@';
            pontos[i][j] = 0;
            player[i][j] = 0;
            fanta1[i][j] = 0;
            fanta2[i][j] = 0;
            fanta3[i][j] = 0;
            fanta4[i][j] = 0;
        }
    }

    mi = mj = 0;
    points = 0;
    tempopilula = -1;
    pi = pj = 1;
    player[pi][pj] = 1;
    walking = 1;
    walkingF1 = 0;
    walkingF2 = 0;
    walkingF3 = 0;
    walkingF4 = 0;
    tempofanta = 0;
    F1 = F2 = F3 = F4 = 0;

    return;
}

void matarfanta() {
    if(fanta1[pi][pj] == 1 || fanta1[pi - 1][pj] == 1 || fanta1[pi + 1][pj] == 1 || fanta1[pi][pj - 1] == 1 || fanta1[pi][pj + 1] == 1) {
        F1 = 0;
        fanta1[F1i][F1j] = 0;
    }

    if(fanta2[pi][pj] == 1 || fanta2[pi - 1][pj] == 1 || fanta2[pi + 1][pj] == 1 || fanta2[pi][pj - 1] == 1 || fanta2[pi][pj + 1] == 1) {
        F2 = 0;
        fanta2[F2i][F2j] = 0;
    }

    if(fanta3[pi][pj] == 1 || fanta3[pi - 1][pj] == 1 || fanta3[pi + 1][pj] == 1 || fanta3[pi][pj - 1] == 1 || fanta3[pi][pj + 1] == 1) {
        F3 = 0;
        fanta3[F3i][F3j] = 0;
    }

    if(fanta4[pi][pj] == 1 || fanta4[pi - 1][pj] == 1 || fanta4[pi + 1][pj] == 1 || fanta4[pi][pj - 1] == 1 || fanta4[pi][pj + 1] == 1) {
        F4 = 0;
        fanta4[F4i][F4j] = 0;
    }

    return;
}