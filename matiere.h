// matiere.h
#ifndef MATIERE_H
#define MATIERE_H

typedef struct {
    char code[20];
    char nom[50];
    int coefficient;
} Matiere;

extern Matiere tabMatieres[];
extern int nbMatieres;

void ajouterMatiere();
void afficherMatieres();
int rechercherMatiere(char code[]);
void modifierMatiere();
void supprimerMatiere();
void menuMatieres();

#endif
