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

void displayFratrie(population pop, int id)
{
  char path[PATH_SIZE];

  fichePath(path, pop.personstorage[getHash(pop, id)]);
  exportPersonToHTML(pop, pop.personstorage[getHash(pop, id)],path, contentFratrie);
}

void displayNbyTown(population pop,int n, char* ville)
{
  //printf("I'm inside the function displatSameFirstName\n");
  population popclone = findNbyTown(pop);
 // printf("Nom d'entré: %s\n", nom);
  char change[MAX_SIZE] = ""; 
  int count = 1;
  for (int i = 0; i < popclone.size; i++)
  {
    /*
      Maintenant que c'est fait, je vais essayer d'écrire dans la console ce que je voudrais générer en HTML et aller le faire.
    */
    //printf("%d  - %s, %d\n",i, popclone.personstorage[i]->birthzipcode, popclone.personstorage[i]->id);

    if (strcmp(change, popclone.personstorage[i]->birthzipcode) != 0) // vu que c'est trié, lorqu'on rencontre une nouvelle personne ...
    {
      printf("      %d. %s\n",count, popclone.personstorage[i]->birthzipcode);
      strcpy(change, popclone.personstorage[i]->birthzipcode);
      count++;
    }
    printf("%d, %s, %s\n",popclone.personstorage[i]->id, popclone.personstorage[i]->lastname, popclone.personstorage[i]->firstname);
      
  }
  //freePersons(popclone.personstorage, popclone.capacity); // libération de la mémoire alloué dans initPopulation()
}


// Implémentation du menu
void menu(population pop,int argc, char* argv[]) 
{
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


    /*// Debug: Print the arguments received
    printf("Option: %d\n", option);
    printf("ville: %s\n", ville);
    printf("n: %d\n", n);*/

  

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
    const char filename[] = "../ressources/40.csv"; // 10 vile in 40.csv && 41 in 200.csv
    population pop = read_csv(filename);
    linkPopulation(pop);
    menu(pop, argc, argv);
    //printf("argc: %d\t argv: %s \t%s\t%s\n", argc, argv[0], argv[1], argv[2]);

    freePersons(pop.personstorage, pop.capacity);
    return EXIT_SUCCESS;
}