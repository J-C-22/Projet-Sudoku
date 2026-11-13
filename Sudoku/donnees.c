#include "donnees.h"

//hvgdqfvbqdbvhqdbfvqndvjn

//Convention:
//return -1 si probl�me
//return 1 si tout s'est bien pass�

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
    return s;
}


int obtenirValeur(Sudoku* s,int i, int j){
    return s->grille[i][j];
}


bool estCaseVide(Sudoku* s,int i, int j){
    if (obtenirValeur(s, i, j)==0){return false;}
    else{return true;}
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
    if (fclose(fichier) != 0) {
        return -1;
    }
    return 1;
}

