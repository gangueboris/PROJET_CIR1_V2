#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "population.h"
#include "filemanager.h"
#include "advanced.h"
#include "htmlexport.h"

const char filename[] = "../ressources/40.csv";
const population pop = read_csv(filename);
linkPopulation(pop);

int main(void)
{


  /*------------------------ Test de la fonction ExportHtml -------------------------*/

    const int id = 2;
    helperContentAncestors(pop, pop.personstorage[getHash(pop, id)]);

    


  return EXIT_SUCCESS;
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
            displayancestors(id);
            break;
        case 2: // Option 2: Afficher la fratrie d'une personne par id
           displayFratrie(id);
            break;
        case 3: // Option 3: Afficher la fratrie d'une personne par ordre de vieillesse
            displayOldestFratrie(id);
            break;
        case 4: // Option 4: Afficher les personnes nées dans la même ville
            displaySameTown(id);
          break;
        case 5: // Option 5: Afficher les personnes ayant le même prénom
            displaySameFirstName(id);
          break;
        default:
            printf("Option invalide\n");
            break;
    }
  freePersons(pop.personstorage, pop.capacity);
}


int main(int argc, char* argv[]) 
{
    menu(pop, argc, argv);

    return EXIT_SUCCESS;
}