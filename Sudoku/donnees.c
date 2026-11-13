#include "donnees.h"

//hvgdqfvbqdbvhqdbfvqndvjn

//Convention:
//return -1 si probl�me
//return 1 si tout s'est bien pass�


Sudoku* initSudoku(char* grille, char* difficulte){
    Sudoku* s=malloc(sizeof(Sudoku));
    char cheminSol[100];
    char cheminDiff[100];
    snprintf(cheminSol, sizeof(cheminSol ), "grilles/solution/%s", grille);
    snprintf(cheminDiff, sizeof(cheminDiff), "grilles/%s/%s", difficulte, grille);
    FILE* sol = fopen(cheminSol,"r");
    FILE* diff = fopen(cheminDiff,"r");

    //On verifie que ce n'est pas vide
    if(sol ==NULL){
        printf("Erreur: Impossible d'ouvrir le fichier. Il est vide\n");
    }
    if(diff ==NULL){
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
    // On remplie la grille qui s'affiche � l'�cran et la grille caseFixe
    for (int i=0; i<TAILLE;i++){
        for(int j=0;j<TAILLE;j++){
            if (fscanf(diff, "%d",&s->grille[i][j])!= 1){//on les met dans la grille et on verifie si il y a bien quelques chose
                fclose(diff);
                printf("Erreur: Impossible d'ouvrir le fichier. Il n'est pas complet2\n");
                printf("erreur");
            }
            //On verifie que les valeur sont entre 0 et 9, 0 car il y a des cases vides
            if(s->grille[i][j] < 0|| s->grille[i][j]>9){
                    fclose(diff);
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
    if(estCaseVide(s, i, j) && s->solution[i][j]==x){//pas besoin de vérifier les ligne et les colonnes si solution unique.
            s->grille[i][j]=1;
            return 1;
    }
    printf("La case est déja remplie ou la réponse est fausse.");
    return -1;
}


int supprimerChiffre(Sudoku* s,int i, int j){
    if(estCaseFixe(s,i,j)){return -1;}
    else{
        s->grille[i][j]=0;
    return 1;
    }
}


