#include <stdio.h>
#include <stdlib.h>
#include "population.h"
#include "advanced.h"

// test de la fonction 
int main ()
{
    // test de la fonction lecture de fichier
    char path[] = "../ressources/40.csv";
    population pop = read_csv(path);
/*
    for(int i = 0; i < pop.capacity; i++)
    {
        if(pop.popDatas[i])
           printf("my id: %d\t father_id: %d\t mother_id:%d\n", pop.popDatas[i]->id, pop.popDatas[i]->father_id,pop.popDatas[i]->mother_id);
           //printf("%s\t%d\n",pop.popDatas[i]->birthzipcode, pop.popDatas[i]->id);
        else
        printf("\t%d\n", 0);
    }
*/
    /*Petit probleme au niveau de birthzipcode, je n'arrive pas à les print.  */

//Test the function getPerson
/*for(int i = 0; i < pop.capacity ;i++)
{    Person* p = getPerson(pop, i);
    if(p)
    {
        printf("%d\t",p->id);
    }
    else
      printf("!%d\t",i);
}
printf("\nAll element in the list: \n");

for(int i = 0; i < pop.capacity; i++)
    {
        if(pop.popDatas[i])
           printf("%d\t", pop.popDatas[i]->id);
        else
        printf("%d\t", 0);
    }
printf("\n");
*/

    // test de la fonction fratrie
 
    fratrie frat = findFratrie(pop, getPerson(pop, 7));
    // printf fratrie ===> VALIDE !!!
    printf("the size of fratList : %d Capacity: %d\n",frat.size, frat.capacity);
    for(int i = 0; i < frat.capacity; i++)
    {
        if(frat.fratrieList[i]) 
           printf("Mon id: %d et l'id du frère ou de la soeur: %d\n",getPerson(pop, 27)->id, frat.fratrieList[i]->id);
    }

/*
    // Link population to set up parent pointers
    linkPopulation(pop);

    // Find ancestors for a specific person, in this case, person with ID 11
    ancestors ances = ancestorsPersons(pop, pop.popDatas[5]);

    // Print the IDs of the ancestors
    printf("Les ids de la descendance de %d sont: \n", 5);
    for (int i = 0; i < ances.ancestorsSize; i++) {
        if (ances.ancestorsList[i] != NULL) { // Ensure we don't dereference null pointers
            printf("id: %d\n", ances.ancestorsList[i]->id);
        }
    }

    // Free allocated memory for ancestors
    free(ances.ancestorsList);

*/
    return EXIT_SUCCESS;
}