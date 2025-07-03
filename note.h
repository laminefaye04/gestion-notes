#ifndef NOTE_H
#define NOTE_H

void menuNotes();

void ajouterNoteParMatiere();       // 1. Étudiant dans une matière
void ajouterNotesEtudiant();        // 2. Étudiant dans toutes ses matières
void ajouterNotesClasseMatiere();   // 3. Toute une classe dans une matière

void afficherNotesEtudiantMatiere();    // 1. Notes étudiant + matière
void afficherNotesEtudiantToutes();     // 2. Notes étudiant + toutes matières
void afficherNotesClasseMatiere();      // 3. Notes classe + une matière

#endif
