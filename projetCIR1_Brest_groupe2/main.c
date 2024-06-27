#include "person.h"
#include "filemanager.h"
#include "htmlexport.h"
#include "menu.h"

int main(int argc, char const *argv[]){
    population pl; // Création de la table de hachage
    initpopulation(&pl); // Initialisation de la table de hachage à null
    
    lireCSV(&pl,"resources/10000.csv"); // Lecture et stockage des personnes
    linkPopulation(&pl); // Liaison entre parents et enfant

    menu(&pl); // Menu

    return 0;
}
