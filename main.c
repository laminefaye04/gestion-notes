#include <stdio.h>
#include <stdlib.h>
#include "etudiant.h"
#include "matiere.h"
#include "note.h"
#include "classe.h"

int main() {
    int choix;

    do {
        printf("\n=========================\n");
        printf("   GESTION DES NOTES C   \n");
        printf("=========================\n");
        printf("1. Gestion des etudiants\n");
        printf("2. Gestion des classes\n");
        printf("3. Gestion des matieres\n");
        printf("4. Gestion des notes\n");
        printf("5. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: menuEtudiants(); break;
            case 2: menuClasses(); break;
            case 3: menuMatieres(); break;
            case 4: menuNotes(); break;
            case 5: printf("A bientot !\n"); break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 5);

    return 0;
}
