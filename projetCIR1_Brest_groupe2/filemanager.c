#include "person.h"
#include "filemanager.h"
#include "htmlexport.h"

void chomp(char *line) { // Remplacement du \n ou \r en fin de ligne par un \0
   char *c = line;
   while (*c != '\0') {
       if (*c == '\n' || *c == '\r') { 
           *c = '\0'; 
           return; 
       }
       c++; 
   }
}

void lireCSV(population* ht, char* nomFichier) { // Fonction qui s'occupe de lire les informations du csv et les écrit dans chaque personne créée
    FILE* file = fopen(nomFichier, "r"); // ouverture du fichier
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier CSV"); // gestion d'erreur d'ouverture du fichier
        return;
    }
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), file)) { // lecture du fichier ligne par ligne
        chomp(ligne); // code pour supprimer le \n ou le \r et le remplacer par un \0
        person* p = initPerson(ligne); // initialisation des personnes avec leurs données
        if (p != NULL) { 
            insert(ht,p); // insertion de la personne dans le tableau
        }
    }
    fclose(file); // fermeture du fichier
}