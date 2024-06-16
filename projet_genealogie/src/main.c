#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "population.h"
#include "advanced.h"
#define PATH_SIZE 50


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
    printf("5. Compter le nombre de personne qui ont le même prénom qu'une personne\n");
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

            // Test de la fonction fratrie
            fratrie frat = findFratrie(pop, getPerson(pop, id));
            printf("Voici les frères et soeurs de '%s' :\n", pop.popDatas[hash_O(pop, id)]->firstname);
            for (int i = 0; i < frat.size; i++) {
                if (frat.fratrieList[i]) {
                    printf("%s\t", frat.fratrieList[i]->firstname);
                }
            }
            printf("\n");

            // Libérer la mémoire de la fratrie
            free(frat.fratrieList);
            break;
        case 2:
            printf("Entrer l'ID de la personne: ");
            scanf("%d", &id);
            printf("\n");

            linkPopulation(pop); // Liaison des personnes à leurs parents
            ancestors ances = ancestorsPersons(pop, pop.popDatas[hash_O(pop, id)]);
            printf("Voici toute la génération de '%s' :\n", pop.popDatas[hash_O(pop, id)]->firstname);
            for (int i = 1; i < ances.ancestorsSize; i++) {
                if (ances.ancestorsList[i] != NULL) {
                    printf("%s\t", ances.ancestorsList[i]->firstname);
                }
            }
            printf("\n");

            // Libérer la mémoire des ancêtres
            free(ances.ancestorsList);
            break;
        case 3:
            printf("Entrer un nombre n: ");
            scanf(" %d", &n);
            if (n >= pop.capacity) {
                printf("Ce nombre est hors du champ de notre base de données !!\n");
            } else {
                for (int i = 0; i < n; i++) {
                    if (pop.popDatas[i]) {
                        printf("ID: %d\t Nom: %s\t Prénom: %s\n", pop.popDatas[i]->id, pop.popDatas[i]->lastname, pop.popDatas[i]->firstname);
                    }
                }
            }
            break;
        case 4:
            // Option 4 pas encore implémenté !!
            break;
        case 5:
            printf("Entrer le nom de l'ID de la personne: ");
            scanf(" %d", &id);
            Person* p = getPerson(pop, id);
            int count = count_firstname(pop, p);
            printf("Le nombre de personnes qui portent le prénom de %s est: %d\n", p->firstname, count);
            break;
        default:
            printf("Option invalide.\n");
            break;
    }
    freePersons(pop.popDatas, pop.capacity); // libération de la mémoire alloué pour la population
}

int main ()
{
  /// --------------------------------- MENU ------------------------------------------------///
   char path[] = "../ressources/60000.csv";
   menu(path);


   
    return EXIT_SUCCESS;
}