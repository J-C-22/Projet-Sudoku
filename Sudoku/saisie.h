#ifndef SAISIE_H
#define SAISIE_H

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "affichage.h"
#include "donnees.h"

void menu(void); // Affiche le menu principal du Sudoku et permet à l'utilisateur de sélectionner une fonctionnalité.

int menuDifficulte(void); // Affiche le menu de sélection de difficulté, puis lance la partie. Retourne 1 pour revenir au menu principal, 0 sinon.

int lireChoix(int min, int max); // Sécurise la saisie utilisateur. Retourne l'entier saisi s'il est valide (entre min et max), -1 si la lecture échoue.

int saisiePartie(Sudoku *s); // Gère le déroulement de la partie : 0 = fin de partie, 1 = appelle saisieLigne.

int saisieLigne(int *ligne, int *colonne, int *chiffre); // Demande la ligne (1-9), puis appelle saisieColonne. Retourne à saisiePartie si 0.

int saisieColonne(int *colonne, int *chiffre); // Demande la colonne (1-9), puis appelle saisieChiffre. Retourne à saisieLigne si 0.

int saisieChiffre(int *chiffre); // Demande le chiffre (1-9). Retourne à saisieColonne si 0.

void finDePartie(void); // Gère la fin de la partie (et proposera de sauvegarder).

#endif
