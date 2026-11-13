#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//fgdfbsbsfb
//Pour que l'importation successive du module ne duplique pas tout
#ifndef DONNEES_H
#define DONNEES_H

#define TAILLE 9
#define FACILE 35
#define MOYEN 45
#define DIFFICILE 53

//Convention:
//return -1 si problème
//return 1 si tout s'est bien passé
//Que pour les fonction qui fonctionne q'avec effet de bord: B à coté de la fonction

typedef struct sudoku {
int grille[TAILLE][TAILLE];
int caseFixe[TAILLE][TAILLE];
int solution[TAILLE][TAILLE];
}Sudoku;
void genererGrille(int n, int grille[9][9]); //B

Sudoku* initSudoku(char* grille, int difficulte);//B

int obtenirValeur(Sudoku* s,int i, int j);

bool estCaseVide(Sudoku* s,int i, int j);

bool estCaseFixe(Sudoku* s,int i, int j);

int placerChiffre(Sudoku* s,int i, int j, int x);//B

int supprimerChiffre(Sudoku* s,int i, int j);//B

int sauvegarderSudoku(Sudoku *s, char *nomFichier);//B

#endif
