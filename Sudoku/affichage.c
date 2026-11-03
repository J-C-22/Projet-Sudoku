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

