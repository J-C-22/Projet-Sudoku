#include "donnees.h"
#include "saisie.h"
#include "affichage.h"

int main(){
    menu();
    Sudoku* s = initSudoku("grille1.txt","moyen");
    afficherPartie(s);
    return 1;
}
