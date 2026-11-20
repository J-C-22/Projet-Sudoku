#include "donnees.h"

//Pratique de programmation que j'essaie de respecter:
//--> Ne pas renvoyer le résultat mais le demander en argument pour le modifier par effet de bord
//--> Renvoyer des valeur de type int qui indique si l'exécution c'est bien passée
//Convention:
//return 0si probleme (en c 0=false)
//return 1 si tout s'est bien passé(en c 1=true, de maniere générale seul 0=false; le rest est évalué à true)

static int genererGrille(int n, int grille[TAILLE][TAILLE]){
    if (grille == NULL || n < 0 || n > TAILLE * TAILLE){return 0;}
    int positions[TAILLE * TAILLE];
    // Initialisation du tableau des positions.
    for (int i = 0; i < TAILLE * TAILLE; i++) {positions[i] = i;}
    // Sélection aléatoire de n positions différentes.
    for (int i = 0; i < n; i++) {
        int j = i + rand() % (TAILLE * TAILLE - i);
        // Échange des positions.
        int temp = positions[i];
        positions[i] = positions[j];
        positions[j] = temp;
        // Conversion de la position en coordonnées.
        int ligne = positions[i] / TAILLE;
        int colonne = positions[i] % TAILLE;
        grille[ligne][colonne] = 0;
    }
    return 1;
}

static int demarrerChronometre(Sudoku *s) {
    if (s == NULL) {return 0;}
    // Évite de redémarrer un chronomètre déjà actif.
    if (s->chronoActif) {return 1;}
    time_t maintenant = time(NULL);
    if (maintenant == (time_t)-1) {return 0;}
    s->debutChrono = maintenant;
    s->chronoActif = true;
    return 1;
}


static int arreterChronometre(Sudoku *s) {
    if (s == NULL) {return 0;}
    // Si le chronomètre est déjà arrêté, rien à faire.
    if (!s->chronoActif) {return 1;}
    time_t maintenant = time(NULL);
    // Vérifie que la récupération de l'heure a fonctionné.
    if (maintenant == (time_t)-1) {return 0;}
    // Ajoute le temps écoulé au temps déjà accumulé.
    s->tempsEcoule += (long)difftime(maintenant, s->debutChrono);
    // Désactive le chronomètre.
    s->chronoActif = false;
    return 1;
}

int obtenirTempsEcoule(Sudoku *s, long *temps){
    if (s == NULL || temps == NULL){return 0;}
    // Si le chronomètre est arrêté, on récupère le temps accumulé.
    if (!s->chronoActif) {
        *temps = s->tempsEcoule;
        return 1;
    }
    time_t maintenant = time(NULL);
    if (maintenant == (time_t)-1) {return 0;}
    // Temps accumulé + durée depuis le dernier démarrage.
    *temps = s->tempsEcoule + (long)difftime(maintenant, s->debutChrono);
    return 1;
}


int initSudoku(Sudoku**  s, char* grille, int difficulte)
{
    // Vérification des arguments
    if (s == NULL || grille == NULL || grille[0] == '\0'){return 0;}
    *s = NULL;
    // Allocation mémoire
    *s = malloc(sizeof(Sudoku));
    if (*s == NULL){return 0;}
    // Construction du chemin du fichier
    char cheminSol[100];
    int longueur = snprintf(cheminSol, sizeof(cheminSol), "grilles/solution/%s", grille);
    //Sécurité
    if (longueur < 0 || longueur >= sizeof(cheminSol)){
        free(*s);
        *s = NULL;
        return 0;
    }
    // Ouverture du fichier contenant la solution
    FILE* sol = fopen(cheminSol, "r");
    //Sécurité
    if (sol == NULL){
        free(*s);
        *s = NULL;
        return 0;
    }
    // Lecture et vérification de la solution
    for (int i = 0; i < TAILLE; i++){
        for (int j = 0; j < TAILLE; j++){
            if (fscanf(sol, "%d", &(*s)->solution[i][j]) != 1){
                fclose(sol);
                free(*s);
                *s = NULL;
                return 0;
            }
            if ((*s)->solution[i][j] < 1 ||(*s)->solution[i][j] > 9){
                fclose(sol);
                free(*s);
                *s = NULL;
                return 0;
            }
        }
    }

    // Vérification de la fermeture du fichier
    if (fclose(sol) != 0){
        free(*s);
        *s = NULL;
        return 0;
        }
    // Copie de la solution dans la grille de jeu
    for (int i = 0; i < TAILLE; i++){
        for (int j = 0; j < TAILLE; j++){
            (*s)->grille[i][j] = (*s)->solution[i][j];
        }
    }
    // Génération des cases vides
    if (!genererGrille(difficulte, (*s)->grille)){
        free(*s);
        *s = NULL;
        return 0;
    }
    // Initialisation du chrono
    (*s)->tempsEcoule = 0;
    (*s)->chronoActif = false;

    if (demarrerChronometre(*s) != 1){
        free(*s);
        *s = NULL;
        return 0;
    }
    // Initialisation du compteur d'erreurs
    (*s)->erreurs = 0;
    return 1;
}

static int estCaseVide(Sudoku* s, int i, int j){
    if (s == NULL || i < 0 || i >= TAILLE || j < 0 || j >= TAILLE){return 0;}
    return (s->grille[i][j] == 0);
}

int placerChiffre(Sudoku* s, int i, int j, int x) {
    if (s == NULL || i < 0 || i >= TAILLE || j < 0 || j >= TAILLE){
        s->erreurs++;
        return 0;
    }
    if (x < 1 || x > 9){
        s->erreurs++;
        return 0;
    }
    if (!estCaseVide(s, i, j)){
        s->erreurs++;
        return 0;
    }
    // Vérification de la réponse
    if (s->solution[i][j] != x){
        s->erreurs++;
        return 0;
    }
    s->grille[i][j] = x;
    return 1;
}


int obtenirValeur(Sudoku* s, int i, int j, int *valeur){
    if (s == NULL || valeur == NULL || i < 0 || i >= TAILLE || j < 0 || j >= TAILLE) {return 0;}
    *valeur = s->grille[i][j];
    return 1;
}

int sauvegarderSudoku(Sudoku* s, char* nomFichier)
{
    // Vérification des arguments
    if (s == NULL || nomFichier == NULL || nomFichier[0] == '\0'){return 0;}
    // Récupération du temps écoulé
    long temps;

    if (!obtenirTempsEcoule(s, &temps)){return 0;}
    // Construction du chemin
    char chemin[256];
    int longueur = snprintf(chemin, sizeof(chemin),"grilles/saves/%s", nomFichier);
    if (longueur < 0 || longueur >= sizeof(chemin)){return 0;}
    // Ouverture du fichier
    FILE* fichier = fopen(chemin, "w");
    if (fichier == NULL){return 0;}
    int succes = 1;//explication à la fin
    // Sauvegarde de la grille actuelle
    if (fprintf(fichier, "MATRICE GRILLE\n") < 0){succes = 0;}
    for (int i = 0; i < TAILLE && succes; i++){
        for (int j = 0; j < TAILLE; j++){
            if (fprintf(fichier, "%d ", s->grille[i][j]) < 0){
                succes = 0;
                break;
            }
        }
        if (succes && fprintf(fichier, "\n") < 0){succes = 0;}
    }
    // Sauvegarde de la solution
    if (succes && fprintf(fichier, "\nMATRICE SOLUTION\n") < 0){succes = 0;}
    for (int i = 0; i < TAILLE && succes; i++){
        for (int j = 0; j < TAILLE; j++){
            if (fprintf(fichier, "%d ", s->solution[i][j]) < 0){
                succes = 0;
                break;
            }
        }
        if (succes && fprintf(fichier, "\n") < 0){succes = 0;}
    }
    // Sauvegarde du temps écoulé
    if (succes && fprintf(fichier, "\nTEMPS %ld\n", temps) < 0){succes = 0;}
    // Sauvegarde du nombre d'erreurs
    if (succes && fprintf(fichier, "ERREURS %d\n", s->erreurs) < 0){
        succes = 0;
    }
    // Fermeture du fichier
    if (fclose(fichier) != 0){succes = 0;}
    return succes;
}

//fprintf peut avoir terminé son travail sans que les données soient enregistrées sur le disque.
// Elles peuvent être temporairement stockées en mémoire. fclose permet de vider ce tampon et de finaliser l'écriture.
//C'est pourquoi j'utilise une variable succes au lieu de fclose directement comme dans les autres fonction.
int initSave(Sudoku** s, char* nomFichier)
{
    // Vérification des arguments
    if (s == NULL || nomFichier == NULL || nomFichier[0] == '\0'){return 0;}
    *s = NULL;
    // Allocation mémoire
    *s = malloc(sizeof(Sudoku));
    if (*s == NULL){return 0;}
    // Construction du chemin
    char chemin[256];
    char mot1[32], mot2[32];
    int longueur = snprintf(chemin, sizeof(chemin),"grilles/saves/%s", nomFichier);
    //Sécurité
    if (longueur < 0 || longueur >= sizeof(chemin)){
        free(*s);
        *s = NULL;
        return 0;
    }
    // Ouverture du fichier
    FILE* save = fopen(chemin, "r");
    //Sécurité
    if (save == NULL)
    {
        free(*s);
        *s = NULL;
        return 0;
    }
    // Lecture de la grille
    if (fscanf(save, "%31s %31s", mot1, mot2) != 2 || strcmp(mot1, "MATRICE") != 0 || strcmp(mot2, "GRILLE") != 0){
        fclose(save);
        free(*s);
        *s = NULL;
        return 0;
    }
    for (int i = 0; i < TAILLE; i++){
        for (int j = 0; j < TAILLE; j++){
            if (fscanf(save, "%d", &(*s)->grille[i][j]) != 1 || (*s)->grille[i][j] < 0 || (*s)->grille[i][j] > 9){
                fclose(save);
                free(*s);
                *s = NULL;
                return 0;
            }
        }
    }
    // Lecture de la solution
    if (fscanf(save, "%31s %31s", mot1, mot2) != 2 || strcmp(mot1, "MATRICE") != 0 || strcmp(mot2, "SOLUTION") != 0){
        fclose(save);
        free(*s);
        *s = NULL;
        return 0;
    }
    for (int i = 0; i < TAILLE; i++){
        for (int j = 0; j < TAILLE; j++){
            if (fscanf(save, "%d", &(*s)->solution[i][j]) != 1 || (*s)->solution[i][j] < 1 || (*s)->solution[i][j] > 9){
                fclose(save);
                free(*s);
                *s = NULL;
                return 0;
            }
        }
    }
    // Récupération du temps sauvegardé
    if (fscanf(save, "%31s %ld", mot1, &(*s)->tempsEcoule) != 2 || strcmp(mot1, "TEMPS") != 0 || (*s)->tempsEcoule < 0){
        fclose(save);
        free(*s);
        *s = NULL;
        return 0;
    }
    // Récupération du nombre d'erreurs sauvegardé
    if (fscanf(save, "%31s %d", mot1, &(*s)->erreurs) != 2 || strcmp(mot1, "ERREURS") != 0 || (*s)->erreurs < 0){
        fclose(save);
        free(*s);
        *s = NULL;
        return 0;
    }
    // Fermeture du fichier
    if (fclose(save) != 0){
        free(*s);
        *s = NULL;
        return 0;
    }
    // Reprise du chronomètre
    (*s)->chronoActif = false;
    if (demarrerChronometre(*s) != 1){
        free(*s);
        *s = NULL;
        return 0;
    }
    return 1;
}


