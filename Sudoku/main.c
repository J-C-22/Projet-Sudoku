#include "donnees.h"
#include "saisie.h"
#include "affichage.h"
#include <time.h>

int main(){
    srand(time(NULL));
    menu();
    Sudoku* s = initSudoku("grille1.txt",FACILE);
    afficherPartie(s);

    //test pour sauvegarde
    for(int i=0;i<4;i++){
        for(int j=0;j<9;j++){
            placerChiffre(s, i, j, s->solution[i][j]);
        }
    }
    printf("\n\n");
    afficherPartie(s);
    sauvegarderSudoku(s, "save1.txt");
    Sudoku* s2 = initSave("save1.txt");
    printf("\n\n");
    afficherPartie(s2);
    return 1;
}
