#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//Pour que l'importation successive du module ne duplique pas tout
#ifndef DONNEES_H
#define DONNEES_H

#define TAILLE 9
#define FACILE 35
#define MOYEN 45
#define DIFFICILE 53

//Convention:
//return 0 si problème
//return 1 si tout s'est bien passé
//Que pour les fonction qui fonctionne q'avec effet de bord: B à coté de la fonction

typedef struct sudoku {
    int grille[TAILLE][TAILLE];
    int solution[TAILLE][TAILLE];
    long tempsEcoule;       // Temps accumulé en secondes
    time_t debutChrono;     // Instant du dernier démarrage
    bool chronoActif;       // Indique si le chrono tourne
}Sudoku;

int genererGrille(int n, int grille[TAILLE][TAILLE]); //B

int demarrerChronometre(Sudoku *s);//B

int arreterChronometre(Sudoku *s);//B

int obtenirTempsEcoule(Sudoku *s, long *temps);//B

int initSudoku(Sudoku** s, char* grille, int difficulte);//B

int estCaseVide(Sudoku* s, int i, int j);//B

int obtenirValeur(Sudoku* s, int i, int j, int *valeur);//B

int placerChiffre(Sudoku* s, int i, int j, int x);//B

int sauvegarderSudoku(Sudoku* s, char* nomFichier);//B

int initSave(Sudoku** s, char* nomFichier); //B

#endif
