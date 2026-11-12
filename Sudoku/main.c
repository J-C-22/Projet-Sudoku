#include "donnees.h"
#include "saisie.h"
#include "affichage.h"
#include <time.h>

int main(){
    srand(time(NULL));
    menu();
    Sudoku* s = initSudoku("grille1.txt",FACILE);
    afficherPartie(s);
    return 1;
}
