#include <stdio.h>
#include <stdlib.h>
#include "population.h"

#define BUFFER_SIZE 255

// Implémentation de la fonction de lecture du fichier csv
population read_csv(const char *filename)
{
    // Initialisation de la population
    population pop = initPopulation();

    FILE* file = fopen(filename, "r"); // Ouverture du fichier
    if(file == NULL)
    {
        perror("Error, can't open file \n");
        exit(EXIT_FAILURE);
    }
    // lecture du fichier
    char buffer[BUFFER_SIZE];
    while(fgets(buffer, sizeof(buffer), file))
    {
       Person* p = initPerson(buffer);

       insert(&pop, getHash(pop, p->id), p);  // Get transform the id to a key
    }
    fclose(file);
    return pop;
}
