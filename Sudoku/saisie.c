#include "saisie.h"
#include <stdio.h>


void menu();
void nouvellePartie();

void menu()
{
    afficherMenu();
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
    afficherDifficulte();
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
