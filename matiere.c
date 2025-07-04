#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"

#define TAILLE 100

Matiere tabMatieres[TAILLE];
int nbMatieres = 0;

void ajouterMatiere() {
    if (nbMatieres >= TAILLE) {
        printf("Nombre maximum de matieres atteint.\n");
        return;
    }

    Matiere m;
    printf("Code de la matiere : ");
    scanf("%s", m.code);
    printf("Nom de la matiere : ");
    scanf("%s", m.nom);
    printf("Coefficient : ");
    scanf("%d", &m.coefficient);

    tabMatieres[nbMatieres++] = m;
    printf("Matiere ajoutee avec succes !\n");
}

void afficherMatieres() {
    if (nbMatieres == 0) {
        printf("Aucune matiere enregistree.\n");
        return;
    }

    printf("\nListe des matieres :\n");
    for (int i = 0; i < nbMatieres; i++) {
        printf("%d. Code: %s | Nom: %s | Coefficient: %d\n", i + 1,
               tabMatieres[i].code, tabMatieres[i].nom, tabMatieres[i].coefficient);
    }
}

int rechercherMatiere(char code[]) {
    for (int i = 0; i < nbMatieres; i++) {
        if (strcmp(tabMatieres[i].code, code) == 0)
            return i;
    }
    return -1;
}

void modifierMatiere() {
    char code[20];
    printf("Entrez le code de la matiere a modifier : ");
    scanf("%s", code);

    int index = rechercherMatiere(code);
    if (index == -1) {
        printf("Matiere non trouvee.\n");
        return;
    }

    printf("Nouveau nom : ");
    scanf("%s", tabMatieres[index].nom);
    printf("Nouveau coefficient : ");
    scanf("%d", &tabMatieres[index].coefficient);
    printf("Matiere modifiee avec succes.\n");
}

void supprimerMatiere() {
    char code[20];
    printf("Entrer le code de la matiere a supprimer : ");
    scanf("%s", code);

    int index = rechercherMatiere(code);
    if (index == -1) {
        printf("Matiere non trouvee.\n");
        return;
    }

    for (int i = index; i < nbMatieres - 1; i++) {
        tabMatieres[i] = tabMatieres[i + 1];
    }
    nbMatieres--;
    printf("Matiere supprimee avec succes.\n");
}

void menuMatieres() {
    int choix;
    do {
        printf("\n--- MENU MATIERES ---\n");
        printf("1. Ajouter une matiere\n");
        printf("2. Afficher les matieres\n");
        printf("3. Modifier une matiere\n");
        printf("4. Supprimer une matiere\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterMatiere(); break;
            case 2: afficherMatieres(); break;
            case 3: modifierMatiere(); break;
            case 4: supprimerMatiere(); break;
            case 0: break;
            default: printf("Choix invalide\n");
        }
    } while (choix != 0);
}
