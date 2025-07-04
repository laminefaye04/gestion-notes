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
