#include "donnees.h"
#include "saisie.h"
#include "affichage.h"
#include <windows.h>

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

    //Silulation d'une partie
    long temps;
    int heures;
    int minutes;
    int secondes;
    printf("\n\n");
    afficherPartie(s);
    Sleep(4000); // Attendre (en millisecondes)
    temps = obtenirTempsEcoule(s);
    heures = temps / 3600;
    minutes = (temps % 3600) / 60;
    secondes = temps % 60;
    printf("Temps : %02d:%02d:%02d\n", heures, minutes, secondes);
    sauvegarderSudoku(s, "save1.txt");
    Sudoku* s2 = initSave("save1.txt");
    printf("\n\n");
    afficherPartie(s2);
    Sleep(6000);
    temps = obtenirTempsEcoule(s);
    heures = temps / 3600;
    minutes = (temps % 3600) / 60;
    secondes = temps % 60;
    printf("Temps : %02d:%02d:%02d\n", heures, minutes, secondes);
    return 1;
}
