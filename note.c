#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "note.h"
#include "structure.h"

void menuNotes() {
    int choix;
    do {
        printf("\n--- MENU GESTION DES NOTES ---\n");
        printf("1. Ajouter les notes d'un etudiant dans une matiere\n");
        printf("2. Ajouter les notes d'un etudiant dans toutes ses matieres\n");
        printf("3. Ajouter les notes d'une classe dans une matiere\n");
        printf("4. Afficher notes etudiant + matiere\n");
        printf("5. Afficher notes etudiant + toutes matieres\n");
        printf("6. Afficher notes d'une classe dans une matiere\n");
        printf("7. Retour au menu principal\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterNoteParMatiere(); break;
            case 2: ajouterNotesEtudiant(); break;
            case 3: ajouterNotesClasseMatiere(); break;
            case 4: afficherNotesEtudiantMatiere(); break;
            case 5: afficherNotesEtudiantToutes(); break;
            case 6: afficherNotesClasseMatiere(); break;
            case 7: printf("Retour au menu principal.\n"); break;
            default: printf("Choix invalide !\n");
        }

    } while (choix != 7);
}

void ajouterNoteParMatiere() {
    Note n;
    printf("Matricule de l'etudiant : "); scanf("%s", n.matricule);
    printf("Reference de la matiere : "); scanf("%s", n.refMatiere);
    printf("Note CC : "); scanf("%f", &n.noteCC);
    printf("Note DS : "); scanf("%f", &n.noteDS);

    FILE *f = fopen("notes.csv", "a");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier notes.\n");
        return;
    }

    fprintf(f, "%s,%s,%.2f,%.2f\n", n.matricule, n.refMatiere, n.noteCC, n.noteDS);
    fclose(f);
    printf("Notes enregistrees avec succes.\n");
}

void ajouterNotesEtudiant() {
    char matricule[10];
    printf("Matricule de l'etudiant : ");
    scanf("%s", matricule);

    FILE *fMat = fopen("matieres.csv", "r");
    if (fMat == NULL) {
        printf("Erreur : impossible de lire matieres.csv\n");
        return;
    }

    FILE *fNote = fopen("notes.csv", "a");
    if (fNote == NULL) {
        printf("Erreur : impossible d'ouvrir notes.csv en ecriture\n");
        fclose(fMat);
        return;
    }

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), fMat)) {
        Matiere m;
        sscanf(ligne, "%[^,],%[^\n]", m.refMatiere, m.libelle);

        Note n;
        strcpy(n.matricule, matricule);
        strcpy(n.refMatiere, m.refMatiere);

        printf("Matiere : %s (%s)\n", m.libelle, m.refMatiere);
        printf("  Note CC : ");
        scanf("%f", &n.noteCC);
        printf("  Note DS : ");
        scanf("%f", &n.noteDS);

        fprintf(fNote, "%s,%s,%.2f,%.2f\n", n.matricule, n.refMatiere, n.noteCC, n.noteDS);
    }

    fclose(fMat);
    fclose(fNote);
    printf("Notes ajoutees pour toutes les matieres.\n");
}

void ajouterNotesClasseMatiere() {
    char codeClasse[10], refMatiere[10];
    printf("Code de la classe : ");
    scanf("%s", codeClasse);
    printf("Reference de la matiere : ");
    scanf("%s", refMatiere);

    FILE *fEtud = fopen("etudiants.csv", "r");
    if (fEtud == NULL) {
        printf("Erreur : impossible d'ouvrir etudiants.csv\n");
        return;
    }

    FILE *fNote = fopen("notes.csv", "a");
    if (fNote == NULL) {
        printf("Erreur : impossible d'ouvrir notes.csv\n");
        fclose(fEtud);
        return;
    }

    char ligne[200];
    int compteur = 0;

    while (fgets(ligne, sizeof(ligne), fEtud)) {
        Etudiant e;
        sscanf(ligne, "%[^,],%[^,],%[^,],%[^\n]", e.matricule, e.nom, e.prenom, e.codeClasse);

        if (strcmp(e.codeClasse, codeClasse) == 0) {
            Note n;
            strcpy(n.matricule, e.matricule);
            strcpy(n.refMatiere, refMatiere);

            printf("Etudiant : %s %s (%s)\n", e.nom, e.prenom, e.matricule);
            printf("  Note CC : ");
            scanf("%f", &n.noteCC);
            printf("  Note DS : ");
            scanf("%f", &n.noteDS);

            fprintf(fNote, "%s,%s,%.2f,%.2f\n", n.matricule, n.refMatiere, n.noteCC, n.noteDS);
            compteur++;
        }
    }

    fclose(fEtud);
    fclose(fNote);

    if (compteur > 0)
        printf("Notes ajoutees pour %d etudiant(s) de la classe %s.\n", compteur, codeClasse);
    else
        printf("Aucun etudiant trouve dans la classe %s.\n", codeClasse);
}

void afficherNotesEtudiantMatiere() {
    char matricule[10], refMatiere[10];
    printf("Matricule de l'etudiant : ");
    scanf("%s", matricule);
    printf("Reference de la matiere : ");
    scanf("%s", refMatiere);

    FILE *f = fopen("notes.csv", "r");
    if (f == NULL) {
        printf("Erreur d'ouverture de notes.csv\n");
        return;
    }

    char ligne[100];
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        Note n;
        sscanf(ligne, "%[^,],%[^,],%f,%f", n.matricule, n.refMatiere, &n.noteCC, &n.noteDS);
        if (strcmp(n.matricule, matricule) == 0 && strcmp(n.refMatiere, refMatiere) == 0) {
            printf("Note trouvee : CC = %.2f | DS = %.2f\n", n.noteCC, n.noteDS);
            trouve = 1;
            break;
        }
    }

    fclose(f);

    if (!trouve)
        printf("Aucune note trouvee pour cet etudiant dans cette matiere.\n");
}

void afficherNotesEtudiantToutes() {
    char matricule[10];
    printf("Matricule de l'etudiant : ");
    scanf("%s", matricule);

    FILE *f = fopen("notes.csv", "r");
    if (f == NULL) {
        printf("Erreur d'ouverture de notes.csv\n");
        return;
    }

    char ligne[100];
    int trouve = 0;

    printf("\n--- Notes de l'etudiant %s ---\n", matricule);
    while (fgets(ligne, sizeof(ligne), f)) {
        Note n;
        sscanf(ligne, "%[^,],%[^,],%f,%f", n.matricule, n.refMatiere, &n.noteCC, &n.noteDS);
        if (strcmp(n.matricule, matricule) == 0) {
            printf("Matiere : %s | CC = %.2f | DS = %.2f\n", n.refMatiere, n.noteCC, n.noteDS);
            trouve = 1;
        }
    }

    fclose(f);

    if (!trouve)
        printf("Aucune note trouvee pour cet etudiant.\n");
}

void afficherNotesClasseMatiere() {
    char codeClasse[10], refMatiere[10];
    printf("Code de la classe : ");
    scanf("%s", codeClasse);
    printf("Reference de la matiere : ");
    scanf("%s", refMatiere);

    FILE *fEtud = fopen("etudiants.csv", "r");
    FILE *fNote = fopen("notes.csv", "r");

    if (fEtud == NULL || fNote == NULL) {
        printf("Erreur d'ouverture des fichiers.\n");
        if (fEtud) fclose(fEtud);
        if (fNote) fclose(fNote);
        return;
    }

    char ligneEtud[200];
    int trouve = 0;

    printf("\n--- Notes de la classe %s pour la matiere %s ---\n", codeClasse, refMatiere);

    while (fgets(ligneEtud, sizeof(ligneEtud), fEtud)) {
        Etudiant e;
        sscanf(ligneEtud, "%[^,],%[^,],%[^,],%[^\n]", e.matricule, e.nom, e.prenom, e.codeClasse);

        if (strcmp(e.codeClasse, codeClasse) == 0) {
            rewind(fNote);

            char ligneNote[100];
            while (fgets(ligneNote, sizeof(ligneNote), fNote)) {
                Note n;
                sscanf(ligneNote, "%[^,],%[^,],%f,%f", n.matricule, n.refMatiere, &n.noteCC, &n.noteDS);
                if (strcmp(n.matricule, e.matricule) == 0 && strcmp(n.refMatiere, refMatiere) == 0) {
                    printf("Etudiant %s %s (%s) | CC = %.2f | DS = %.2f\n",
                           e.nom, e.prenom, e.matricule, n.noteCC, n.noteDS);
                    trouve = 1;
                }
            }
        }
    }

    fclose(fEtud);
    fclose(fNote);

    if (!trouve)
        printf("Aucune note trouvee pour cette matiere dans cette classe.\n");
}
