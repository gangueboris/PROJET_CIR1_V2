#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "population.h"

//Implémentation de la fonction qui permet d'initialiser la population
population initPopulation()
{
   population pop;
   pop.capacity = POP_SIZE;
   pop.size = 0;
   pop.personstorage = calloc(pop.capacity, sizeof(Person*));
   if ( pop.personstorage == NULL)
   {
      perror("Memory allocation failed for pop.personstorage in initpopulation \n");
      exit(EXIT_FAILURE);
   }
   return pop;
}

// Implémentation de la fonction permettant de redimensionné un tableau de personnes
void resizeArray(Person** *array, const int newCapacity)
{
    *array = realloc(*array, newCapacity * sizeof(Person*));
    if (*array == NULL)
    {
        perror("Memory allocation failed for *array in resizeArray \n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Memory successfuly reallocated \n");
    }

}

// Implémentation de la fonction d'insertion
void insert(population pop , int key, Person* p)
{
   for(int i = 0; i < pop.capacity; i++)
   {
       // Vérifier s'il est nécessaire de réalloué la mémoire
       if (pop.size == pop.capacity)
       {
           pop.capacity *= 2; // mettre à jour la nouvelle capacité du tableau
           resizeArray(&pop.personstorage, pop.capacity);
       }
       // application du linear probing afin d'insérer p dans pop
      int index = (key + i) % pop.capacity;
      if (pop.personstorage[index] == 0) // si position non occupé
      {
        pop.personstorage[index] = p;
        pop.size++; // mettre à jour le nombre de personnes dans la population
        break;
      }
   }
}

// Implémentation de la fonction qui retourne un index dans le range de la capacity
int getHash (population pop, int id)
{
    return id % pop.capacity;
}
// Implémentation de la fonction qui permet de lier une personne à sa paranté
void linkPopulation(population pop)
{
   for (int i = 0; i < pop.capacity; i++)
   {
      // ... une personne quelconque
      if (pop.personstorage[i])
      {
        int p_key = getHash(pop, pop.personstorage[i]->father_id);// get the index of father in the personstorage
        int m_key = getHash(pop, pop.personstorage[i]->mother_id);// get the index of mother in the personstorage

        if (pop.personstorage[p_key]->id) // vérifier si le père existe
            pop.personstorage[i]->p_father = pop.personstorage[p_key];
        else // sinon le père est le personne inconnue
            pop.personstorage[i]->p_father = pop.personstorage[getHash(pop, 0)]; 
        
        if (pop.personstorage[m_key])
           pop.personstorage[i]->p_mother = pop.personstorage[m_key];
        else
           pop.personstorage[i]->p_mother = pop.personstorage[getHash(pop, 0)];  
       }
   }
}