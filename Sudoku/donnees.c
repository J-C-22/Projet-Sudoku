#include "donnees.h"

//Pratique de programmation que j'essaie de respecter:
//--> Ne pas renvoyer le résultat mais le demander en argument pour le modifier par effet de bord
//--> Renvoyer des valeur bouléenne qui indique si l'exécution c'est bien passée

//Convention:
//return 0si probleme (en c 0=false)
//return 1 si tout s'est bien passé(en c 1=true, de maniere générale seul 0=false; le rest est évalué à true)

#include <stdlib.h>

#include <stdlib.h>

#include <stdlib.h>

void genererGrille(int n, int grille[9][9]){
    int ligne, colonne;
    int tab[81] = {0};
    int position;
    for (int i = 0; i < n; i++){
            position = rand() % 81;
            while(tab[position] ==1){
                  position = rand() % 81;
                  }
            tab[position] = 1;
            ligne = position / 9;
            colonne = position % 9;
            grille[ligne][colonne] = 0;
            }
            }


int demarrerChronometre(Sudoku *s) {
    if (s == NULL) {return -1;}
    // Evite de redemarrer un chronometre deja actif.
    if (s->chronoActif) {return 1;}
    s->debutChrono = time(NULL);
    if (s->debutChrono == (time_t)-1) {return -1;}
    s->chronoActif = true;
    return 1;
}


int arreterChronometre(Sudoku *s) {
    if (s == NULL) {return -1;}
    if (!s->chronoActif) {return 1;}
    time_t maintenant = time(NULL);
    if (maintenant == (time_t)-1) {return -1;}
    s->tempsEcoule += (long)difftime(maintenant, s->debutChrono);
    s->chronoActif = false;
    return 1;
}


long obtenirTempsEcoule(Sudoku *s) {
    if (s == NULL) {return -1;}
    if (!s->chronoActif) {return s->tempsEcoule;}
    time_t maintenant = time(NULL);
    if (maintenant == (time_t)-1) {return -1;}
    return (s->tempsEcoule + (long)difftime(maintenant, s->debutChrono));
}


Sudoku* initSudoku(char* grille, int difficulte){
    Sudoku* s=malloc(sizeof(Sudoku));
    char cheminSol[100];
    snprintf(cheminSol, sizeof(cheminSol ), "grilles/solution/%s", grille);
    FILE* sol = fopen(cheminSol,"r");

    //On verifie que ce n'est pas vide
    if(sol ==NULL){
        printf("Erreur: Impossible d'ouvrir le fichier. Il est vide\n");
    }
    // On remplie la grille solution
    for (int i=0; i<TAILLE;i++){
        for(int j=0;j<TAILLE;j++){
            if (fscanf(sol, "%d",&s->solution[i][j])!= 1){//on les met dans la solution de s et on verifie si il y a bien quelques chose
                fclose(sol);
                printf("Erreur: Impossible d'ouvrir le fichier. Il n'est pas complet1\n");

            }
            //On verifie les valeurs(entre 1 et 9)
            if(s->solution[i][j] < 1|| s->solution[i][j]>9){
                    fclose(sol);
            printf("erreur");
            }
        }
    }
    //On copie la solution dans grille
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            s->grille[i][j] = s->solution[i][j];
        }
    }
    // On remplie la grille qui s'affiche à l'écran et la grille caseFixe
    genererGrille(difficulte, s->grille);
            //On verifie que les valeur sont entre 0 et 9, 0 car il y a des cases vides
    for (int i=0; i<TAILLE;i++){
        for(int j=0;j<TAILLE;j++){
            if(s->grille[i][j] < 0|| s->grille[i][j]>9){
                    printf("erreur");
            }
            if(s->grille[i][j]!=0){s->caseFixe[i][j]=1;}
            else{s->caseFixe[i][j]=0;}
        }
    }
    s->tempsEcoule = 0;
    s->chronoActif = false;
    if (demarrerChronometre(s) == -1) {
            free(s);
            return NULL;
    }
    return s;
}


int obtenirValeur(Sudoku* s,int i, int j){
    return s->grille[i][j];
}


bool estCaseVide(Sudoku* s,int i, int j){
    if (obtenirValeur(s, i, j)==0){return true;}
    else{return false;}
}


//Convention: 1 = case fixe, 0 = case � compl�ter
bool estCaseFixe(Sudoku* s,int i, int j){
    if (s->caseFixe[i][j]==0){return false;}
    else{return true;}
}


int placerChiffre(Sudoku* s,int i, int j, int x){
    if(estCaseVide(s, i, j)&& s->solution[i][j]==x){
            s->grille[i][j]=x;
            return 1;
    }
    return -1;
}


int supprimerChiffre(Sudoku* s,int i, int j){
    if(estCaseFixe(s,i,j)){return -1;}
    else{
        s->grille[i][j]=0;
    return 1;
    }
}
int sauvegarderSudoku(Sudoku *s, char *nomFichier) {
    char chemin[256];
    sprintf(chemin, "grilles/saves/%s", nomFichier);
    FILE *fichier = fopen(chemin, "w");
    if (fichier == NULL){
        return -1;
    }
    // Sauvegarde de la grille actuelle
    fprintf(fichier, "MATRICE GRILLE\n");
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++){
            fprintf(fichier, "%d ", s->grille[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fprintf(fichier, "\nMATRICE CASEFIXE\n");

    // Sauvegarde des cases fixes
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            fprintf(fichier, "%d ", s->caseFixe[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fprintf(fichier, "\nMATRICE SOLUTION\n");
    // Sauvegarde de la solution
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            fprintf(fichier, "%d ", s->solution[i][j]);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarde du temps écoulé
    fprintf(fichier, "\nTEMPS %ld\n", obtenirTempsEcoule(s));
    if (fclose(fichier) != 0) {
        return -1;
    }
    return 1;
}

Sudoku* initSave(char* nomFichier){
    Sudoku* s = malloc(sizeof(Sudoku));
    if(s == NULL){
        printf("Erreur allocation memoire\n");
        return NULL;
    }
    char chemin[256];
    char mot1[32], mot2[32];
    snprintf(chemin, sizeof(chemin), "grilles/saves/%s", nomFichier);
    FILE* save = fopen(chemin, "r");
    if(save == NULL){
            printf("Erreur: Impossible d'ouvrir la sauvegarde\n");
            free(s);
            return NULL;
            }

    // On recupere la matrice grille
    if(fscanf(save, "%31s %31s", mot1, mot2) != 2 || strcmp(mot1, "MATRICE") != 0 || strcmp(mot2, "GRILLE") != 0){
            printf("Erreur: Format de sauvegarde incorrect\n");
            fclose(save);
            free(s);
            return NULL;
            }
    for(int i = 0; i < TAILLE; i++){
            for(int j = 0; j < TAILLE; j++){
                    if(fscanf(save, "%d", &s->grille[i][j]) != 1 || s->grille[i][j] < 0 || s->grille[i][j] > 9){
                           printf("Erreur: Grille incomplete ou invalide\n");
                           fclose(save);
                           free(s);
                           return NULL;
                           }
                           }
                           }

    // On recupere la matrice caseFixe
    if(fscanf(save, "%31s %31s", mot1, mot2) != 2 || strcmp(mot1, "MATRICE") != 0 || strcmp(mot2, "CASEFIXE") != 0){
            printf("Erreur: Format caseFixe incorrect\n");
            fclose(save);
            free(s);
            return NULL;
            }
    for(int i = 0; i < TAILLE; i++){
            for(int j = 0; j < TAILLE; j++){
                if(fscanf(save, "%d", &s->caseFixe[i][j]) != 1 || (s->caseFixe[i][j] != 0 && s->caseFixe[i][j] != 1)){
                    printf("Erreur: Matrice caseFixe invalide\n");
                    fclose(save);
                    free(s);
                    return NULL;
                    }
                    }
                    }

    // On recupere la matrice solution
    if(fscanf(save, "%31s %31s", mot1, mot2) != 2 || strcmp(mot1, "MATRICE") != 0 || strcmp(mot2, "SOLUTION") != 0){
        printf("Erreur: Format solution incorrect\n");
        fclose(save);
        free(s);
        return NULL;
    }

    for(int i = 0; i < TAILLE; i++){
        for(int j = 0; j < TAILLE; j++){

            if(fscanf(save, "%d", &s->solution[i][j]) != 1 ||
               s->solution[i][j] < 1 || s->solution[i][j] > 9){

                printf("Erreur: Solution incomplete ou invalide\n");
                fclose(save);
                free(s);
                return NULL;
            }
        }

    }
    // Recuperation du temps sauvegarde
        if (fscanf(save, "%31s %ld", mot1, &s->tempsEcoule) != 2 || strcmp(mot1, "TEMPS") != 0 || s->tempsEcoule < 0) {
                printf("Erreur: Temps sauvegarde invalide\n");
                fclose(save);
                free(s);
                return NULL;
        }
    fclose(save);
    // Le chronometre reprend a partir du temps sauvegarde
    s->chronoActif = false;

    if (demarrerChronometre(s) == -1) {
            free(s);
            return NULL;
    }

    return s;
}

