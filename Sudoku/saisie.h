#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

//Pour que l'importation successive du module ne duplique pas tout
#ifndef SAISIE_H
#define SAISIE_H

void menu(); //Affiche le menu principal du Sudoku et permet à l'utilisateur de sélectionner une fonctionnalité.

void nouvellePartie(); //Affiche le menu de sélection de difficulté d'une nouvelle partie.

int lireChoix(); // Fonction permettant de sécuriser la saisie utilisateur. Retourne l'entier saisi si la saisie est valide et retourne -1 si la lecture échoue.
#endif