#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "population.h"
#include "filemanager.h"
#include "advanced.h"
#include "htmlexport.h"

int main(void)
{


  /*------------------------ Test de la fonction ExportHtml -------------------------*/

    const int id = 2;
    helperContentAncestors(pop, pop.personstorage[getHash(pop, id)]);

    


  return EXIT_SUCCESS;
}

// Implémentation du menu
void menu(int argc, char* argv[]) 
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
        case 4: // Option 4: Afficher les personnes n premières personnes par ville
            displaySameTown(id);
          break;
        case 5: // Option 5: Afficher les informations des personnes ayant le même prénom
            displaySameFirstName(id);
          break;
        default:
            printf("Option invalide\n");
            break;
    }
}


int main(int argc, char* argv[]) 
{
    const char filename[] = "../ressources/40.csv";
    const population pop = read_csv(filename);
    linkPopulation(pop);

    menu(pop, argc, argv);
    printf("argc: %d\t argv: %s\n", argc, argv);

    freePersons(pop.personstorage, pop.capacity);
    return EXIT_SUCCESS;
}