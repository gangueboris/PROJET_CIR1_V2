#ifndef MENU_MENU_H
#define MENU_MENU_H

void menu(population *population);

void majPremierelettre(char *str);

void afficherAncetreCommun(population *population);

person* choisirPersonne(person** resultats, int taille);

void rechercherParNom(population* population, char* nom, person** resultats, int* taille);

void rechercherParPrenom(population* population, char* prenom, person** resultats, int* taille);

void rechercherParNomPrenom(population* population, char* nom, char* prenom, person** resultats, int* taille);

void rechercherParLieuNaissance(population* population, char* lieu, person** resultats, int* taille);

void rechercherParDateNaissance(population* population, int day, int month, int year, person** resultats, int* taille);

person* recherchePersonne(population* population);

#endif