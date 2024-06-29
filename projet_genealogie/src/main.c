#include <stdio.h>
#include <stdlib.h>

#include "person.h"
#include "population.h"
#include "filemanager.h"
#include "advanced.h"
#include "htmlexport.h"


// Implémentation des fonctions qui les options du menu
void displayancestors(population pop, int id)
{
  helperContentAncestors(pop, pop.personstorage[getHash(pop, id)]);
}

void displayFratrie(population pop, int id)
{
  char path[PATH_SIZE];

  fichePath(path, pop.personstorage[getHash(pop, id)]);
  exportPersonToHTML(pop, pop.personstorage[getHash(pop, id)],path, contentFratrie);
}

void displayNbyTown(population pop, int id)
{
   return;
}

void displaySameFirstName(population pop, int id)
{
  return;
}
// Implémentation du menu
void menu(population pop,int argc, char* argv[]) 
{
    
    const int option = atoi(argv[1]); // récupérer l'option dans la ligne de commande
    const int id = atoi(argv[2]);
    switch (option) 
    {
        case 1: // Option 1: Afficher les ancêtres d'une personne par id 
            displayancestors(pop, id);
            break;
        case 2: // Option 2: Afficher la fratrie d'une personne par ordre de vieillesse
           displayFratrie(pop, id);
            break;
        case 3: // Option 3: Afficher les personnes par ville
            displayNbyTown(pop, id);
            break;
        case 4: // Option 4: Afficher les informations des personnes ayant le même prénom
            displaySameFirstName(pop, id);
          break;
        default:
            printf("Option invalide\n");
            break;
    }
   
}


int main(int argc, char* argv[]) 
{
    const char filename[] = "../ressources/40.csv";
    population pop = read_csv(filename);
    linkPopulation(pop);

    menu(pop, argc, argv);
    //printf("argc: %d\t argv: %s \t%s\t%s\n", argc, argv[0], argv[1], argv[2]);

    freePersons(pop.personstorage, pop.capacity);
    return EXIT_SUCCESS;
}