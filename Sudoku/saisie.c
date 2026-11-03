#include "saisie.h"
#include <stdio.h>


void menu();
void nouvellePartie();

void menu()
{
    printf("MENU PRINCIPAL \n\n");
    printf("1  Nouvelle partie \n");
    printf("2  Charger une partie sauvegarder \n");
    printf("3  Aide \n");
    printf("4  Quitter \n\n");
    int choix;
    scanf("%d", &choix);
    switch (choix)
        {
            case 1:
                nouvellePartie();
                break;

            case 2:
                printf("Partie sauvegarder \n\n");
                break;

            case 3:
                printf("Aide \n\n");
                break;

            case 4:
                printf("Quitter \n\n");
                break;

            default:
                 printf("Choix invalide \n\n");
                 menu();
        };
}

void nouvellePartie()
{
    printf("NOUVELLE PARTIE \n\n");
    printf("1  Facile \n");
    printf("2  Intermediaire \n");
    printf("3  Expert \n");
    printf("4  Retour au menu \n\n");
    int choix;
    scanf("%d", &choix);
                switch (choix)
                    {
                        case 1:
                            printf("Facile \n\n");
                            break;

                        case 2:
                            printf("Intermediaire \n\n");
                            break;

                        case 3:
                            printf("Expert \n\n");
                            break;

                        case 4:
                            menu();
                            break;

                        default:
                            printf("Choix invalide \n\n");
                            nouvellePartie();
                    }
}
