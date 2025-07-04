#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"
#include "structure.h"

void menuEtudiants() {
    int choix;
    do {
        printf("\n--- MENU ETUDIANTS ---\n");
        printf("1. Ajouter\n");
        printf("2. Afficher tous\n");
        printf("3. Rechercher\n");
        printf("4. Modifier\n");
        printf("5. Supprimer\n");
        printf("6. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterEtudiant(); break;
            case 2: afficherEtudiants(); break;
            case 3: rechercherEtudiant(); break;
            case 4: modifierEtudiant(); break;
            case 5: supprimerEtudiant(); break;
            case 6: printf("Retour au menu principal.\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 6);
}

void ajouterEtudiant() {
    Etudiant e;
    printf("Matricule : "); scanf("%s", e.matricule);
    printf("Nom : "); scanf("%s", e.nom);
    printf("Prenom : "); scanf("%s", e.prenom);
    printf("Email : "); scanf("%s", e.email);
    printf("Date de naissance (JJ/MM/AAAA) : "); scanf("%s", e.date_naissance);
    printf("Code classe : "); scanf("%s", e.codeClasse);

    FILE *f = fopen("etudiants.csv", "a");
    if (!f) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(f, "%s,%s,%s,%s,%s,%s\n", e.matricule, e.nom, e.prenom, e.email, e.date_naissance, e.codeClasse);
    fclose(f);
    printf("Etudiant ajoute avec succes.\n");
}

void afficherEtudiants() {
    FILE *f = fopen("etudiants.csv", "r");
    if (!f) {
        printf("Aucun etudiant trouve.\n");
        return;
    }

    char ligne[300];
    printf("\n--- Liste des etudiants ---\n");
    while (fgets(ligne, sizeof(ligne), f)) {
        Etudiant e;
        sscanf(ligne, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", e.matricule, e.nom, e.prenom, e.email, e.date_naissance, e.codeClasse);
        printf("Matricule: %s | Nom: %s | Prenom: %s | Email: %s | Naissance: %s | Classe: %s\n",
               e.matricule, e.nom, e.prenom, e.email, e.date_naissance, e.codeClasse);
    }

    fclose(f);
}

void rechercherEtudiant() {
    char mat[10];
    printf("Entrer le matricule a rechercher : ");
    scanf("%s", mat);

    FILE *f = fopen("etudiants.csv", "r");
    if (!f) {
        printf("Erreur d'ouverture.\n");
        return;
    }

    char ligne[300];
    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        Etudiant e;
        sscanf(ligne, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", e.matricule, e.nom, e.prenom, e.email, e.date_naissance, e.codeClasse);
        if (strcmp(e.matricule, mat) == 0) {
            printf("Etudiant trouve : %s %s (%s) - Email: %s - Naissance: %s - Classe : %s\n",
                   e.nom, e.prenom, e.matricule, e.email, e.date_naissance, e.codeClasse);
            trouve = 1;
            break;
        }
    }

    fclose(f);
    if (!trouve)
        printf("Etudiant non trouve.\n");
}

void modifierEtudiant() {
    char mat[10];
    printf("Entrer le matricule de l'etudiant a modifier : ");
    scanf("%s", mat);

    FILE *f = fopen("etudiants.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!f || !temp) {
        printf("Erreur lors de l'ouverture.\n");
        return;
    }

    char ligne[300];
    int modifie = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        Etudiant e;
        sscanf(ligne, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", e.matricule, e.nom, e.prenom, e.email, e.date_naissance, e.codeClasse);
        if (strcmp(e.matricule, mat) == 0) {
            printf("Nouveau nom : "); scanf("%s", e.nom);
            printf("Nouveau prenom : "); scanf("%s", e.prenom);
            printf("Nouveau email : "); scanf("%s", e.email);
            printf("Nouvelle date naissance : "); scanf("%s", e.date_naissance);
            printf("Nouveau code classe : "); scanf("%s", e.codeClasse);
            modifie = 1;
        }
        fprintf(temp, "%s,%s,%s,%s,%s,%s\n", e.matricule, e.nom, e.prenom, e.email, e.date_naissance, e.codeClasse);
    }

    fclose(f);
    fclose(temp);
    remove("etudiants.csv");
    rename("temp.csv", "etudiants.csv");

    if (modifie)
        printf("Etudiant modifie avec succes.\n");
    else
        printf("Etudiant introuvable.\n");
}

void supprimerEtudiant() {
    char mat[10];
    printf("Entrer le matricule de l'etudiant a supprimer : ");
    scanf("%s", mat);

    FILE *f = fopen("etudiants.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!f || !temp) {
        printf("Erreur.\n");
        return;
    }

    char ligne[300];
    int supprime = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        Etudiant e;
        sscanf(ligne, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", e.matricule, e.nom, e.prenom, e.email, e.date_naissance, e.codeClasse);
        if (strcmp(e.matricule, mat) != 0) {
            fprintf(temp, "%s,%s,%s,%s,%s,%s\n", e.matricule, e.nom, e.prenom, e.email, e.date_naissance, e.codeClasse);
        } else {
            supprime = 1;
        }
    }

    fclose(f);
    fclose(temp);
    remove("etudiants.csv");
    rename("temp.csv", "etudiants.csv");

    if (supprime)
        printf("Etudiant supprime avec succes.\n");
    else
        printf("Etudiant non trouve.\n");
}
