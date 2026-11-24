
#ifndef DONNEES_H
#define DONNEES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/**
 @file donnees.h
 @brief Gestion des données et des opérations du Sudoku.

 Ce module permet d'initialiser une partie, de consulter et modifier
 la grille, de gérer le chronomètre et de sauvegarder une partie.
*/

/** @def TAILLE
 @brief Taille d'un côté de la grille de Sudoku.
*/
#define TAILLE 9

/** @def FACILE
 @brief Nombre de cases à vider pour une grille de difficulté facile.
*/
#define FACILE 35

/** @def MOYEN
 @brief Nombre de cases à vider pour une grille de difficulté moyenne.
*/
#define MOYEN 45

/** @def DIFFICILE
 @brief Nombre de cases à vider pour une grille de difficulté difficile.
*/
#define DIFFICILE 53

/**
 @brief Structure contenant les données d'une partie de Sudoku.
*/
typedef struct sudoku {
    int grille[TAILLE][TAILLE];/**< Grille en cours de résolution.*/
    int solution[TAILLE][TAILLE];/**<Solution complète de la grille.*/
    long tempsEcoule;/**< Temps accumulé en secondes.*/
    time_t debutChrono;/**< Instant du dernier démarrage du chronomètre.*/
    bool chronoActif;/**< Indique si le chronomètre est actuellement actif.*/
} Sudoku;

/**
 @brief Récupère le temps écoulé depuis le début de la partie.

 Si le chronomètre est actif, le temps écoulé depuis son dernier
 démarrage est ajouté au temps déjà accumulé, sans arrêter le chronomètre.

 @param s: Pointeur vers la partie de Sudoku.
 @param temps: Adresse de la variable qui recevra le temps écoulé, en secondes.
 @return 1 si la récupération a réussi, 0 en cas d'erreur.
*/
int obtenirTempsEcoule(Sudoku *s, long *temps);

/**
 @brief Initialise une nouvelle partie de Sudoku.

 Charge la solution depuis un fichier, construit la grille de jeu
 en retirant un certain nombre de cases, puis démarre le chronomètre.

 @param s: Adresse du pointeur qui recevra la partie créée.
 @param grille: Nom du fichier contenant la solution.
 @param difficulte: Nombre de cases à vider dans la grille.
 @return 1 si l'initialisation a réussi, 0 en cas d'erreur.
*/
int initSudoku(Sudoku** s, char* grille, int difficulte);

/**
 @brief Récupère la valeur d'une case de la grille.

 @param s: Pointeur vers la partie de Sudoku.
 @param i: Indice de la ligne.
 @param j: Indice de la colonne.
 @param valeur Adresse de la variable qui recevra la valeur de la case.
 @return 1 si la récupération a réussi, 0 en cas d'erreur.
*/
int obtenirValeur(Sudoku* s, int i, int j, int *valeur);

/**
 @brief Place un chiffre dans une case vide de la grille.

 Le chiffre est placé uniquement s'il correspond à la valeur attendue
 dans la solution.

 @param s: Pointeur vers la partie de Sudoku.
 @param i: Indice de la ligne.
 @param j: Indice de la colonne.
 @param x: Chiffre à placer.
 @return 1 si le chiffre a été placé, 0 en cas d'erreur.
*/
int placerChiffre(Sudoku* s, int i, int j, int x);

/**
 @brief Sauvegarde une partie de Sudoku dans un fichier.

 La sauvegarde contient les données nécessaires pour reprendre
 la partie ultérieurement, notamment le temps écoulé.

 @param s: Pointeur vers la partie à sauvegarder.
 @param nomFichier: Nom du fichier de sauvegarde.
 @return 1 si la sauvegarde a réussi, 0 en cas d'erreur.
*/
int sauvegarderSudoku(Sudoku* s, char* nomFichier);

/**
 @brief Initialise une partie à partir d'un fichier de sauvegarde.

 Charge la grille, sa solution et le temps déjà écoulé, puis
 redémarre le chronomètre.

 @param s: Adresse du pointeur qui recevra la partie restaurée.
 @param nomFichier: Nom du fichier de sauvegarde.
 @return 1 si le chargement a réussi, 0 en cas d'erreur.
*/
int initSave(Sudoku** s, char* nomFichier);

#endif
