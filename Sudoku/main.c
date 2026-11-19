#include "donnees.h"
#include "saisie.h"
#include "affichage.h"
#include <windows.h>

int main() {
    srand(time(NULL));
    menu();
    // Initialisation d'une nouvelle partie.
    Sudoku* s = NULL;
    if (!initSudoku(&s, "grille1.txt", FACILE)) {
        printf("Erreur lors de l'initialisation du Sudoku.\n");
        return 0;
    }
    afficherPartie(s);
    // Test pour sauvegarde.
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            placerChiffre(s, i, j, s->solution[i][j]);
        }
    }
    // Deux mauvaises réponses
    placerChiffre(s, 0, 0, 1);
    placerChiffre(s, 0, 0, 1);
    printf("Nombre d'erreurs : %d\n", s->erreurs);
    // Simulation d'une partie.
    long temps;
    int heures;
    int minutes;
    int secondes;
    printf("\n\n");
    afficherPartie(s);
    Sleep(4000); // Attendre 4 secondes.
    if (!obtenirTempsEcoule(s, &temps)) {
        printf("Erreur lors de la récupération du temps.\n");
        free(s);
        return 0;
    }
    heures = temps / 3600;
    minutes = (temps % 3600) / 60;
    secondes = temps % 60;
    printf("Temps : %02d:%02d:%02d\n", heures, minutes, secondes);
    printf("Nombre d'erreurs : %d\n", s->erreurs);
    // Sauvegarde de la partie.
    if (!sauvegarderSudoku(s, "save1.txt")) {
        printf("Erreur lors de la sauvegarde.\n");
        free(s);
        return 0;
    }
    // Chargement de la sauvegarde.
    Sudoku* s2 = NULL;
    if (!initSave(&s2, "save1.txt")) {
        printf("Erreur lors du chargement de la sauvegarde.\n");
        free(s);
        return 0;
    }
    printf("\n\n");
    afficherPartie(s2);
    Sleep(6000);
    if (!obtenirTempsEcoule(s, &temps)) {
        printf("Erreur lors de la récupération du temps.\n");
        free(s);
        free(s2);
        return 0;
    }
    heures = temps / 3600;
    minutes = (temps % 3600) / 60;
    secondes = temps % 60;
    printf("Temps : %02d:%02d:%02d\n", heures, minutes, secondes);
    printf("Nombre d'erreurs : %d\n", s->erreurs);
    // Libération de la mémoire.
    free(s);
    free(s2);
    return 1;
}
