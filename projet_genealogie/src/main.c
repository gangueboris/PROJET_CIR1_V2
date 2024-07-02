#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"
#include "population.h"
#include "filemanager.h"
#include "advanced.h"
#include "htmlexport.h"

#define MAX_SIZE 50

// Implémentation des fonctions qui les options du menu
void displayancestors(population pop, int id)
{
  helperContentAncestors(pop, pop.personstorage[getHash(pop, id)]);
}

// Fonction d'option d'affichage pour la fratrie
void displayFratrie(population pop, int id)
{
  char path[PATH_SIZE];

  fichePath(path, pop.personstorage[getHash(pop, id)]);
  exportPersonToHTML(pop, pop.personstorage[getHash(pop, id)],path, contentFratrie);
}

// Cette fonction affiche les informations des n premières personnes de la ville 
void displayNbyTown(population pop,int n, char* ville)
{
  char path[PATH_SIZE];

  fichePath(path, NULL);
  exportPersonToHTMLV2(pop, n, ville, path, contentNbyTown);
}


// Implémentation du menu
void menu(population pop,int argc, char* argv[]) 
{
  if (argc == 1) // Condition pour éviter un seg fault lorsqu'on compile sans avoir mit les arguments dans la console
  {
    printf("Aucun argument dans la console, impossible d'excéter le programme !\n"); // Pour excécuter le programme, il faut se rendre dans le script
    return;
  }
    int option, n, id;
    char* ville = NULL;
    option = atoi(argv[1]);
    if (argc == 3) 
    {  if (option == 3)
          ville = argv[2];
        else
          id = atoi(argv[2]);
    }
    else if (argc == 4)
    {
        n = atoi(argv[2]);
        ville = argv[3];
        //printf("argc: %d\t argv: %s \t%s\t%s\t%s\n", argc, argv[0], argv[1], argv[2], argv[3]);
    }
    else
    {
       printf("There is an error in menu, argc, argv \n");
       return;
    }


    switch (option) 
    {
        case 1: // Option 1: Afficher les ancêtres d'une personne par id 
            displayancestors(pop, id);
            break;
        case 2: // Option 2: Afficher la fratrie d'une personne par ordre de vieillesse
           displayFratrie(pop, id);
            break;
        case 3: // Option 3: Afficher les personnes par ville
            displayNbyTown(pop, n, ville);
            break;
        default:
            printf("Option invalide\n");
            break;
    }
   
}


int main(int argc, char* argv[]) 
{
    const char filename[] = "../ressources/200.csv"; // 10 vile in 40.csv && 41 in 200.csv
    population pop = read_csv(filename);
    linkPopulation(pop);
    menu(pop, argc, argv);
    //printf("argc: %d\t argv: %s \t%s\t%s\n", argc, argv[0], argv[1], argv[2]);

    freePersons(pop.personstorage, pop.capacity);
    return EXIT_SUCCESS;
}