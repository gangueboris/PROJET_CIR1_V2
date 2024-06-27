#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "population.h"
#include "filemanager.h"
#include "advanced.h"
#include "htmlexport.h"

#define PATH_SIZE 255
int main(void)
{
    char filename[] = "../ressources/40.csv";

    population pop = read_csv(filename);
    linkPopulation(pop);

    // Test to print person_id, father_id, mother_id
    /*for(int i = 0; i < pop.capacity; i++)
    {
        if (pop.personstorage[i])
          {
            printf("%d\t%d\t%d\n",pop.personstorage[i]->id, pop.personstorage[i]->p_father->id, pop.personstorage[i]->p_mother->id);
          }
    }*/

   /*------------------------Test de la fonction findFratrie -------------------------*/
   /*fratrie frat = findFratrie(pop, 0);
    for (int i = 0; i < frat.size; i++)
    {
        printf("%d\n", frat.fratrieTab[i]->id);
    }
   freePersons(pop.personstorage, pop.capacity);
   */
  /*------------------------ Test de la fonction ancestoresPersons -------------------------*/
  /*ancestors ances = ancestorsPersons(pop, 9);
  for(int i = 0; i < ances.size; i++)
  {
    if(ances.ancestorsTab[i])
      printf("%d\t", ances.ancestorsTab[i]->id);
  }
  printf("\n");
  */

  /*------------------------ Test de la fonction ExportHtml -------------------------*/

  char path[PATH_SIZE]; // Definition de chemin de savergarde du fichier
  fichePath(path, pop.personstorage[getHash(pop, 2)]);
  
exportPersonToHTML(pop, pop.personstorage[getHash(pop, 2)],path, contentAncestors);
  
 
    return EXIT_SUCCESS;
}

