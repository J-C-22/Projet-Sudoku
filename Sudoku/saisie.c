#include "saisie.h"


#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

// Valeurs de retour de menuDifficulte().
#define DIFFICULTE_CHOISIE 0
#define RETOUR_MENU        1

// Valeurs de retour des fonctions de saisie de la partie.
#define SAISIE_EOF        -1   // flux d'entrée fermé
#define SAISIE_RETOUR      0   // l'utilisateur a saisi 0 : on revient en arrière
#define SAISIE_OK          1   // saisie complète validée


int lireChoix(int min, int max)
{
    char saisie[100];
    int choix;
    int i;
    int invalide;

    while (1)
    {
        if (fgets(saisie, sizeof(saisie), stdin) == NULL)
            return -1;

        // Vérification que toute la ligne a bien été lue.
        int longueur = strlen(saisie);

        if (longueur > 0 && saisie[longueur - 1] != '\n'
            && !feof(stdin))
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            printf("Saisie trop longue ou invalide. Entrez un nombre entre %d et %d : ", min, max);
            continue;
        }

        choix = 0;
        i = 0;
        invalide = 0;

        // Ignore les espaces placés avant le nombre.
        while (isspace((unsigned char)saisie[i]))
            i++;

        // Vérifie que la saisie contient au moins un chiffre.
        if (!isdigit((unsigned char)saisie[i]))
            invalide = 1;

        // Conversion des chiffres en entier.
        while (!invalide && isdigit((unsigned char)saisie[i]))
        {
            int chiffre = saisie[i] - '0';

            // Vérification du dépassement de capacité.
            if (choix > (INT_MAX - chiffre) / 10)
            {
                invalide = 1;
                break;
            }

            choix = choix * 10 + chiffre;
            i++;
        }

        // Ignore les espaces placés après le nombre.
        while (isspace((unsigned char)saisie[i]))
            i++;

        // Refuse tout caractère restant après le nombre.
        if (saisie[i] != '\0')
            invalide = 1;

        // Vérifie que le nombre est dans l'intervalle autorisé.
        if (!invalide && (choix < min || choix > max))
            invalide = 1;

        if (!invalide)
            return choix;

        printf("Saisie invalide ! Entrez un nombre entre %d et %d : ", min, max);
    }
}


void menu(void)
{
    int choix;

    while (1)
    {
        afficherMenu();

        // Récupération du choix avec vérification de la saisie.
        printf("\nVotre choix : ");
        choix = lireChoix(1, 4);

        // Flux d'entrée fermé : on quitte pour éviter une boucle infinie.
        if (choix == -1)
            return;

        // Exécution de l'action correspondant au choix.
        switch (choix)
        {
            case 1:
                // RETOUR_MENU : on réaffiche le menu principal.
                // Sinon (difficulté choisie ou flux fermé) : on quitte.
                if (menuDifficulte() != RETOUR_MENU)
                    return;
                break;

            case 2:
                printf("Partie sauvegardee \n\n");
                break;

            case 3:
                printf("Aide \n\n");
                break;

            case 4:
                printf("Au revoir ! \n");
                return;

            default:
                // Ne devrait plus arriver : lireChoix filtre déjà 1 à 4.
                printf("Choix invalide ! \n\n");
                break;
        }
    }
}

// Lance une partie de la difficulté donnée.
// Renvoie 1 si la partie a pu être lancée, 0 si la grille n'a pas pu être chargée.
static int lancerPartie(int difficulte)
{
    Sudoku *s = NULL;

    if (!initSudoku(&s, "grille1.txt", difficulte))
    {
        afficherErreur();
        printf("Impossible de charger la grille.\n\n");
        return 0;
    }

    saisiePartie(s);

    free(s);
    return 1;
}

int menuDifficulte(void)
{
    int choix;
    int difficulte;

    while (1)
    {
        afficherDifficulte();

        printf("Votre choix : ");
        choix = lireChoix(1, 4);

        if (choix == -1)
            return DIFFICULTE_CHOISIE;

        switch (choix)
        {
            case 1:
                difficulte = FACILE;
                break;

            case 2:
                difficulte = MOYEN;
                break;

            case 3:
                difficulte = DIFFICILE;
                break;

            default:
                return RETOUR_MENU;
        }

        // Partie lancée (et terminée) : on quitte. Sinon on réaffiche le menu.
        if (lancerPartie(difficulte))
            return DIFFICULTE_CHOISIE;
    }
}

// Demande le chiffre à placer (1 à 9).
// Renvoie SAISIE_OK, SAISIE_RETOUR (0 saisi) ou SAISIE_EOF.
int saisieChiffre(int *chiffre)
{
    int choix;

    printf("Chiffre (1-9, 0 pour revenir a la colonne) : ");
    choix = lireChoix(0, 9);

    if (choix == -1)
        return SAISIE_EOF;

    if (choix == 0)
        return SAISIE_RETOUR;

    *chiffre = choix;
    return SAISIE_OK;
}

// Demande la colonne (1 à 9), puis le chiffre.
// Renvoie SAISIE_OK, SAISIE_RETOUR (0 saisi) ou SAISIE_EOF.
int saisieColonne(int *colonne, int *chiffre)
{
    int choix;
    int resultat;

    while (1)
    {
        printf("Colonne (1-9, 0 pour revenir a la ligne) : ");
        choix = lireChoix(0, 9);

        if (choix == -1)
            return SAISIE_EOF;

        if (choix == 0)
            return SAISIE_RETOUR;

        *colonne = choix;

        resultat = saisieChiffre(chiffre);

        // OK ou EOF : on remonte l'information.
        // RETOUR : on reste ici et on redemande la colonne.
        if (resultat != SAISIE_RETOUR)
            return resultat;
    }
}

// Demande la ligne (1 à 9), puis la colonne.
// Renvoie SAISIE_OK, SAISIE_RETOUR (0 saisi) ou SAISIE_EOF.
int saisieLigne(int *ligne, int *colonne, int *chiffre)
{
    int choix;
    int resultat;

    while (1)
    {
        printf("Ligne (1-9, 0 pour revenir a la partie) : ");
        choix = lireChoix(0, 9);

        if (choix == -1)
            return SAISIE_EOF;

        if (choix == 0)
            return SAISIE_RETOUR;

        *ligne = choix;

        resultat = saisieColonne(colonne, chiffre);

        // OK ou EOF : on remonte l'information.
        // RETOUR : on reste ici et on redemande la ligne.
        if (resultat != SAISIE_RETOUR)
            return resultat;
    }
}

// Menu de fin de partie (à compléter : proposer de sauvegarder).
void finDePartie(void)
{
    printf("Fin de partie \n\n");
}

// Renvoie 1 si toutes les cases de la grille sont remplies, 0 sinon.
static int grilleComplete(Sudoku *s)
{
    int valeur;
    int i;
    int j;

    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            if (!obtenirValeur(s, i, j, &valeur) || valeur == 0)
                return 0;
        }
    }
    return 1;
}

// Déroulement d'une partie : 0 = fin de partie, 1 = saisir un chiffre.
// Renvoie SAISIE_RETOUR (partie terminée) ou SAISIE_EOF (flux fermé).
int saisiePartie(Sudoku *s)
{
    int choix;
    int ligne = 0;
    int colonne = 0;
    int chiffre = 0;
    int valeur = 0;
    int resultat;

    if (s == NULL)
        return SAISIE_RETOUR;

    while (1)
    {
        printf("\n");
        afficherPartie(s);
        printf("\n\n");

        if (grilleComplete(s))
        {
            printf("Bravo, la grille est terminee !\n");
            finDePartie();
            return SAISIE_RETOUR;
        }

        printf("0 : Fin de partie / 1 : Saisir un chiffre\n");
        printf("Votre choix : ");

        choix = lireChoix(0, 1);

        if (choix == -1)
            return SAISIE_EOF;

        if (choix == 0)
        {
            finDePartie();
            return SAISIE_RETOUR;
        }

        // choix == 1 : saisie ligne -> colonne -> chiffre.
        resultat = saisieLigne(&ligne, &colonne, &chiffre);

        if (resultat == SAISIE_EOF)
            return SAISIE_EOF;

        if (resultat == SAISIE_OK)
        {
            // L'utilisateur saisit de 1 à 9, la grille est indexée de 0 à 8.
            obtenirValeur(s, ligne - 1, colonne - 1, &valeur);

            if (valeur != 0)
                printf("\nCette case est deja remplie.\n");
            else if (placerChiffre(s, ligne - 1, colonne - 1, chiffre))
                printf("\nChiffre place !\n");
            else
                printf("\nCe n'est pas le bon chiffre pour cette case.\n");
        }
    }
}
