#include "affichage.h"

void afficherPartie(Sudoku* s){
    int x = 0;
    for (int i=0; i<TAILLE;i++){
        printf("\n");
        for(int j=0;j<TAILLE;j++){
            x = s->grille[i][j];
            if(x==0){printf("   ");}
            else{printf("%d  ",x);}
        }
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
    printf("3. Règles \n");
    printf("\n");
    printf("4. Quitter \n");
    printf("----------------");

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
    printf("----------------\n");

}


void afficherErreur(){

    printf("+--------------+ \n");
    printf("|    Erreur    | \n");
    printf("+--------------+ \n");

}
