#include "saisie.h"


int lireChoix()
{
    char saisie[100];
    int choix = 0;

    while (1)
    {
        if (fgets(saisie, sizeof(saisie), stdin) == NULL)
            return -1;

        // Vérification de chaque caractère de la saisie.
        int i = 0;

        while (saisie[i] != '\0' && saisie[i] != '\n')
        {
            // Vérifie que le caractère est un chiffre.
            if (!isdigit((unsigned char)saisie[i]))
            {
                choix = -1;
                break;
            }

            // Vérifie que le nombre ne provoque pas de dépassement de capacité
            if (choix > (INT_MAX - (saisie[i] - '0')) / 10)
            {
                choix = -1;
                break;
            }

            // Conversion du caractère en entier et construction du nombre.
            choix = choix * 10 + (saisie[i] - '0');
            i++;
        }

        // Si la ligne est trop longue, on vide le reste du tampon.
        if (saisie[i] == '\0' && i == 99)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            choix = -1;
        }

        // Vérifie que la saisie contient au moins un chiffre.
        if (i == 0 || saisie[i] == '\n' || saisie[i] == '\0')
        {
            if (choix >= 0)
                return choix;
        }

        // Affiche un message d'erreur et prépare une nouvelle tentative.
        printf("Saisie invalide ! Entrez uniquement un chiffre : ");
        choix = 0;
    }
}


void menu()
{
    int choix;

    while (1)
    {
        printf("MENU PRINCIPAL \n\n");
        printf("1  Nouvelle partie \n");
        printf("2  Charger une partie sauvegardee \n");
        printf("3  Aide \n");
        printf("4  Quitter \n\n");

        // Récupération du choix avec vérification de la saisie.
        printf("Votre choix : ");
        choix = lireChoix();

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
                // Toute option non prévue entraîne un retour au menu.
                printf("Choix invalide ! \n\n");
                break;
        }
    }
}

void nouvellePartie()
{
    int choix;

    while (1)
    {
        printf("NOUVELLE PARTIE \n\n");
        printf("1  Facile \n");
        printf("2  Intermediaire \n");
        printf("3  Expert \n");
        printf("4  Retour au menu \n\n");

        // Récupération du choix de difficulté.
        printf("Votre choix : ");
        choix = lireChoix();

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
                // En cas d'erreur, le menu de difficulté est réaffiché.
                printf("Choix invalide ! \n\n");
                break;
        }
    }
}

void main()
{
menu();
}