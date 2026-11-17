#include "saisie.h"


#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

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
        printf("Votre choix : ");
        choix = lireChoix(1, 4);

        // Flux d'entrée fermé : on quitte pour éviter une boucle infinie.
        if (choix == -1)
            return;

        // Exécution de l'action correspondant au choix.
        switch (choix)
        {
            case 1:
                nouvellePartie();
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

void nouvellePartie(void)
{
    int choix;

    while (1)
    {

        afficherDifficulte();
        // Récupération du choix de difficulté.
        printf("Votre choix : ");
        choix = lireChoix(1, 4);

        // Flux d'entrée fermé : retour au menu (qui quittera aussi).
        if (choix == -1)
            return;

        // Exécution de l'action correspondant au choix.
        switch (choix)
        {
            case 1:
                printf("Facile \n\n");
                return;

            case 2:
                printf("Intermediaire \n\n");
                return;

            case 3:
                printf("Expert \n\n");
                return;

            case 4:
                return;

            default:
                // Ne devrait plus arriver : lireChoix filtre déjà 1 à 4.
                printf("Choix invalide ! \n\n");
                break;
        }
    }
}

