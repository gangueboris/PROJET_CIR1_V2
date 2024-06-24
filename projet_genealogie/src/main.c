#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "population.h"
#include "filemanager.h"

int main(void)
{
    char filename[] = "../ressources/40.csv";

    population pop = read_csv(filename);
    for(int i = 0; i < pop.capacity; i++)
    {
        if (pop.personstorage[i])
          {
            printf("%d\n",pop.personstorage[i]->id);
          }
    }




    return EXIT_SUCCESS;
}

