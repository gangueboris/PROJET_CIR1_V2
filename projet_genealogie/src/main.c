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
  return;
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
    if (argc < 2) {
        printf("Usage: %s <option> [id]\n", argv[0]);
        return;
    }

    int option = atoi(argv[1]);
    int id = (argc >= 3) ? atoi(argv[2]) : 0; // modify after by adding string

    switch (option) 
    {
        case 1: // Option 1: Afficher les ancêtres d'une personne par id 
            displayancestors(pop, id);
            break;
        case 2: // Option 2: Afficher la fratrie d'une personne par id
           displayFratrie(pop, id);
            break;
        case 3: // Option 3: Afficher la fratrie d'une personne par ordre de vieillesse
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
    printf("argc: %d\t argv: %s \t%s\t%s\n", argc, argv[0], argv[1], argv[2]);

    freePersons(pop.personstorage, pop.capacity);
    return EXIT_SUCCESS;
}