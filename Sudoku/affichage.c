#include "affichage.h"
#include <windows.h>


//fonction gotoxy qui permet de placer le curseur où l'on souhaite dans la console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}




void afficherChiffre(Sudoku* s,int a, int b){
    int x=0;
    x = s->grille[a][b];
    if(x==0){printf(" ");}
    else{printf("%d",x);}
}



void afficherPartie(Sudoku* s){

    int i=0;
    int j=0;
    int x = 0;
    printf("+---+---+---+");
    printf("\n");
    while(j<9 || i<3){
        for(int a=0; a<3; a++){
            for(int b=0;b<3 ;b++){
                printf("|");
                afficherChiffre(s,i,j);
                j=j+1;
                afficherChiffre(s,i,j);
                j=j+1;
                afficherChiffre(s,i,j);
                j=j+1;
            }
            printf("\n");
        }i=i+1;
    }
}

void afficherMenu(){
    printf("----------------");
    printf(" SUDOKU  ");
    printf("----------------");
    printf("\n");
    printf("---------------- \n");
    printf("1. Nouvelle Partie \n");
    printf("2. Continuer \n");
    printf("3. Regles \n");
    printf("\n");
    printf("4. Quitter \n");
    printf("----------------\n\n");

    }



void afficherDifficulte(){

    printf("----------------");
    printf(" SUDOKU  ");
    printf("----------------");
    printf("\n");
    printf("1.Facile \n");
    printf("2.Moyen \n");
    printf("3.Difficile \n");

    printf("\n");
    printf("4.Retour au menu principal \n");
    printf("----------------\n\n");

}


void afficherErreur(){

    printf("+--------------+ \n");
    printf("|    Erreur    | \n");
    printf("+--------------+ \n");

}
