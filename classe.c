#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classe.h"
#include "structure.h"

#define FICHIER_CLASSES "classes.csv"
#define FICHIER_TEMP "temp.csv"

void menuClasses() {
    int choix;
    do {
        printf("\n=== MENU CLASSES ===\n");
        printf("1. Ajouter une classe\n");
        printf("2. Afficher toutes les classes\n");
        printf("3. Rechercher une classe\n");
        printf("4. Modifier une classe\n");
        printf("5. Supprimer une classe\n");
        printf("6. Retour\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            printf("Entree invalide.\n");
            while(getchar() != '\n');
            continue;
        }

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

void ajouterClasse() {
    Classe c;

    printf("\n--- Ajout d'une classe ---\n");
    printf("Code de la classe : ");
    scanf("%s", c.codeClasse);

    printf("Nom de la classe : ");
    scanf("%s", c.nom);

    printf("Niveau (Licence/Master) : ");
    scanf("%s", c.niveau);

    FILE *f = fopen(FICHIER_CLASSES, "a");
    if (!f) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fprintf(f, "%s,%s,%s\n", c.codeClasse, c.nom, c.niveau);
    fclose(f);
    printf("Classe ajoutee avec succes.\n");
}

void afficherClasses() {
    FILE *f = fopen(FICHIER_CLASSES, "r");
    if (!f) {
        printf("Aucune classe trouvee.\n");
        return;
    }

    char ligne[150];
    printf("\n=== Liste des classes ===\n");
    while (fgets(ligne, sizeof(ligne), f)) {
        Classe c;
        sscanf(ligne, "%[^,],%[^,],%[^\n]", c.codeClasse, c.nom, c.niveau);
        printf("Code : %-10s | Nom : %-15s | Niveau : %s\n", c.codeClasse, c.nom, c.niveau);
    }

    fclose(f);
}

void rechercherClasse() {
    char code[10];
    printf("Code de la classe a rechercher : ");
    scanf("%s", code);

    FILE *f = fopen(FICHIER_CLASSES, "r");
    if (!f) {
        perror("Erreur d'ouverture");
        return;
    }

    char ligne[150];
    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        Classe c;
        sscanf(ligne, "%[^,],%[^,],%[^\n]", c.codeClasse, c.nom, c.niveau);
        if (strcmp(c.codeClasse, code) == 0) {
            printf("Classe trouvée : %s - %s - Niveau : %s\n", c.codeClasse, c.nom, c.niveau);
            trouve = 1;
            break;
        }
    }

    fclose(f);
    if (!trouve)
        printf("Classe non trouvee.\n");
}

void modifierClasse() {
    char code[10];
    printf("Code de la classe a modifier : ");
    scanf("%s", code);

    FILE *f = fopen(FICHIER_CLASSES, "r");
    FILE *temp = fopen(FICHIER_TEMP, "w");
    if (!f || !temp) {
        perror("Erreur d'ouverture des fichiers");
        return;
    }

    char ligne[150];
    int modifie = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        Classe c;
        sscanf(ligne, "%[^,],%[^,],%[^\n]", c.codeClasse, c.nom, c.niveau);
        if (strcmp(c.codeClasse, code) == 0) {
            printf("Nouveau nom : ");
            scanf("%s", c.nom);
            printf("Nouveau niveau : ");
            scanf("%s", c.niveau);
            modifie = 1;
        }
        fprintf(temp, "%s,%s,%s\n", c.codeClasse, c.nom, c.niveau);
    }

    fclose(f);
    fclose(temp);

    remove(FICHIER_CLASSES);
    rename(FICHIER_TEMP, FICHIER_CLASSES);

    if (modifie)
        printf("Classe modifiée avec succès.\n");
    else
        printf("Classe non trouvée.\n");
}

void supprimerClasse() {
    char code[10];
    printf("Code de la classe à supprimer : ");
    scanf("%s", code);

    FILE *f = fopen(FICHIER_CLASSES, "r");
    FILE *temp = fopen(FICHIER_TEMP, "w");
    if (!f || !temp) {
        perror("Erreur d'ouverture des fichiers");
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

    fclose(f);
    fclose(temp);

    remove(FICHIER_CLASSES);
    rename(FICHIER_TEMP, FICHIER_CLASSES);

    if (supprime)
        printf("Classe supprimee avec succes.\n");
    else
        printf("Classe non trouvee.\n");
}
