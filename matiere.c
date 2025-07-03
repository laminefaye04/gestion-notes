#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"

#define TAILLE 100

Matiere tabMatieres[TAILLE];
int nbMatieres = 0;

void ajouterMatiere() {
    if (nbMatieres >= TAILLE) {
        printf("Nombre maximum de matières atteint.\n");
        return;
    }

    Matiere m;
    printf("Code de la matière : ");
    scanf("%s", m.code);
    printf("Nom de la matière : ");
    scanf("%s", m.nom);
    printf("Coefficient : ");
    scanf("%d", &m.coefficient);

    tabMatieres[nbMatieres++] = m;
    printf("Matière ajoutée avec succès !\n");
}

void afficherMatieres() {
    if (nbMatieres == 0) {
        printf("Aucune matière enregistrée.\n");
        return;
    }

    printf("\nListe des matières :\n");
    for (int i = 0; i < nbMatieres; i++) {
        printf("%d. Code: %s | Nom: %s | Coefficient: %d\n", i+1,
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
    printf("Entrer le code de la matière à modifier : ");
    scanf("%s", code);

    int index = rechercherMatiere(code);
    if (index == -1) {
        printf("Matière non trouvée.\n");
        return;
    }

    printf("Nouveau nom : ");
    scanf("%s", tabMatieres[index].nom);
    printf("Nouveau coefficient : ");
    scanf("%d", &tabMatieres[index].coefficient);
    printf("Matière modifiée avec succès.\n");
}

void supprimerMatiere() {
    char code[20];
    printf("Entrer le code de la matière à supprimer : ");
    scanf("%s", code);

    int index = rechercherMatiere(code);
    if (index == -1) {
        printf("Matière non trouvée.\n");
        return;
    }

    for (int i = index; i < nbMatieres - 1; i++) {
        tabMatieres[i] = tabMatieres[i + 1];
    }
    nbMatieres--;
    printf("Matière supprimée avec succès.\n");
}

void menuMatieres() {
    int choix;
    do {
        printf("\n--- MENU MATIÈRES ---\n");
        printf("1. Ajouter une matière\n");
        printf("2. Afficher les matières\n");
        printf("3. Modifier une matière\n");
        printf("4. Supprimer une matière\n");
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
