#ifndef STRUCTURES_H
#define STRUCTURES_H

// === Structure de l'étudiant ===
typedef struct {
    char matricule[10];          // Identifiant unique
    char nom[50];                // Nom de l'étudiant
    char prenom[50];             // Prénom
    char email[100];             // ✅ Ajouté
    char date_naissance[20];     // ✅ Ajouté (format texte : JJ/MM/AAAA)
    char codeClasse[10];         // Code de la classe (clé étrangère)
} Etudiant;

// === Structure de la classe ===
typedef struct {
    char codeClasse[10];         // Code unique
    char nom[50];                // Nom de la classe
    char niveau[10];             // ✅ Ajouté ('Licence' ou 'Master')
} Classe;

// === Structure de la matière ===
typedef struct {
    char refMatiere[10];         // Référence unique
    char libelle[50];            // Nom de la matière
    int coefficient;             // ✅ Ajouté
} Matiere;

// === Structure de la note ===
typedef struct {
    char matricule[10];          // Identifiant de l'étudiant
    char refMatiere[10];         // Référence de la matière
    float noteCC;                // Note de contrôle continu
    float noteDS;                // Note d’examen
} Note;

#endif
