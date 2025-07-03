#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classe.h"
#include "structure.h"

void menuClasses() {
    int choix;
    do {
        printf("\n--- MENU CLASSES ---\n");
        printf("1. Ajouter une classe\n");
        printf("2. Afficher toutes les classes\n");
        printf("3. Rechercher une classe\n");
        printf("4. Modifier une classe\n");
        printf("5. Supprimer une classe\n");
        printf("6. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterClasse(); break;
            case 2: afficherClasses(); break;
            case 3: rechercherClasse(); break;
            case 4: modifierClasse(); break;
            case 5: supprimerClasse(); break;
            case 6: printf("Retour au menu principal.\n"); break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 6);
}

// Ajouter une classe
void ajouterClasse() {
    Classe c;
    printf("Code de la classe : "); scanf("%s", c.codeClasse);
    printf("Nom de la classe : "); scanf("%s", c.nom);
    printf("Niveau (Licence/Master) : "); scanf("%s", c.niveau);

    FILE *f = fopen("classes.csv", "a");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(f, "%s,%s,%s\n", c.codeClasse, c.nom, c.niveau);
    fclose(f);
    printf("Classe ajoutee avec succes.\n");
}

// Afficher toutes les classes
void afficherClasses() {
    FILE *f = fopen("classes.csv", "r");
    if (f == NULL) {
        printf("Aucune classe trouvee.\n");
        return;
    }

    char ligne[150];
    printf("\n--- Liste des classes ---\n");
    while (fgets(ligne, sizeof(ligne), f)) {
        Classe c;
        sscanf(ligne, "%[^,],%[^,],%[^\n]", c.codeClasse, c.nom, c.niveau);
        printf("Code : %s | Nom : %s | Niveau : %s\n", c.codeClasse, c.nom, c.niveau);
    }

    fclose(f);
}

// Rechercher une classe
void rechercherClasse() {
    char code[10];
    printf("Entrer le code de la classe a rechercher : ");
    scanf("%s", code);

    FILE *f = fopen("classes.csv", "r");
    if (f == NULL) {
        printf("Erreur d'ouverture.\n");
        return;
    }

    char ligne[150];
    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        Classe c;
        sscanf(ligne, "%[^,],%[^,],%[^\n]", c.codeClasse, c.nom, c.niveau);
        if (strcmp(c.codeClasse, code) == 0) {
            printf("Classe trouvee : %s - %s - Niveau : %s\n", c.codeClasse, c.nom, c.niveau);
            trouve = 1;
            break;
        }
    }

    fclose(f);
    if (!trouve) printf("Classe non trouvee.\n");
}

// Modifier une classe
void modifierClasse() {
    char code[10];
    printf("Code de la classe a modifier : ");
    scanf("%s", code);

    FILE *f = fopen("classes.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (f == NULL || temp == NULL) {
        printf("Erreur d'ouverture.\n");
        return;
    }

    char ligne[150];
    int modifie = 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        Classe c;
        sscanf(ligne, "%[^,],%[^,],%[^\n]", c.codeClasse, c.nom, c.niveau);
        if (strcmp(c.codeClasse, code) == 0) {
            printf("Nouveau nom : "); scanf("%s", c.nom);
            printf("Nouveau niveau : "); scanf("%s", c.niveau);
            modifie = 1;
        }
        fprintf(temp, "%s,%s,%s\n", c.codeClasse, c.nom, c.niveau);
    }

    fclose(f); fclose(temp);
    remove("classes.csv");
    rename("temp.csv", "classes.csv");

    if (modifie)
        printf("Classe modifiee avec succes.\n");
    else
        printf("Classe non trouvee.\n");
}

// Supprimer une classe
void supprimerClasse() {
    char code[10];
    printf("Code de la classe a supprimer : ");
    scanf("%s", code);

    FILE *f = fopen("classes.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (f == NULL || temp == NULL) {
        printf("Erreur d'ouverture.\n");
        return;
    }

    char ligne[150];
    int supprime = 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        Classe c;
        sscanf(ligne, "%[^,],%[^,],%[^\n]", c.codeClasse, c.nom, c.niveau);
        if (strcmp(c.codeClasse, code) != 0) {
            fprintf(temp, "%s,%s,%s\n", c.codeClasse, c.nom, c.niveau);
        } else {
            supprime = 1;
        }
    }

    fclose(f); fclose(temp);
    remove("classes.csv");
    rename("temp.csv", "classes.csv");

    if (supprime)
        printf("Classe supprimee avec succes.\n");
    else
        printf("Classe non trouvee.\n");
}
