#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "population.h"
#include "advanced.h"
#define PATH_SIZE 50
// test de la fonction 
void menu (char* filename)
{
    char path[PATH_SIZE];
    strcpy(path, filename);
    population pop = read_csv(path);


    int option;
    printf("1. Rechercher la fratrie d'une personne par ID\n");
    printf("2. Rechercher toute la géneration d'une personne par ID\n");
    printf("3. Rechercher les n premières personnes de la population par ID\n");
    printf("4. Rechercher la famille: NOM_DE_FAMILLE\n");
    printf("\nChoississez une option: ");
    scanf(" %d", &option);
    printf("\n");

    switch (option)
    {
        int id, n;
        case 1:
             printf("Entrer l'ID de la personne: ");
             scanf("%d", &id);
             printf("\n");
           // test de la fonction fratrie
            fratrie frat = findFratrie(pop, getPerson(pop, id));
            printf("Voici les des frères et soeurs de ' %s ' :\n", pop.popDatas[hash_O(pop, id)]->firstname);
            for(int i = 0; i < frat.capacity; i++)
            {
                if(frat.fratrieList[i]) 
                printf("%s \t",frat.fratrieList[i]->firstname);
            }
            printf("\n");
            break;
        case 2:
             printf("Entrer l'ID de la personne: ");
             scanf("%d", &id);
             printf("\n");

             linkPopulation(pop);
             ancestors ances = ancestorsPersons(pop, pop.popDatas[hash_O(pop, id)]);
             printf("Voici toute la génération de ' %s' :\n",pop.popDatas[hash_O(pop, id)]->firstname);
             for (int i = 1; i < ances.ancestorsSize; i++) 
             {
                if (ances.ancestorsList[i] != NULL) 
                { 
                    printf("%s\t", ances.ancestorsList[i]->firstname);
                }
            }
            printf("\n");
            free(ances.ancestorsList);
            break;
        case 3:
            printf("Entrer un nombre n: ");
            scanf(" %d", &n);
            if(n >= pop.capacity) printf("Cet nombre est hors du champ de notre base de données !!\n");
            else
            {
                for(int i = 0; i < n; i++)
                {
                    if(pop.popDatas[i])
                    printf("ID: %d\t Nom: %s\t Prénom: %s\n", pop.popDatas[i]->id, pop.popDatas[i]->lastname,pop.popDatas[i]->firstname);   
                }
            }
            break;
        case 4:
            /* code */
            break;

        default:
            break;
    }
}
int main ()
{
  /// --------------------------------- MENU ------------------------------------------------///
   char path[] = "../ressources/40.csv";
   menu(path);



    return EXIT_SUCCESS;
}