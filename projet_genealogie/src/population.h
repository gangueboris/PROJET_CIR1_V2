#ifndef _POPULATION_H_
# define _POPULATION_H_

#include "person.h"
#define POP_SIZE 100
// définition de la structure population
typedef struct
{
    int size; // pour tracker le nombre de personne présente dans la population
    int capacity; // pour être capable de redimensionné le tableau
    Person** personstorage; // tableau
}population;

// Définition de la fonction qui permet d'initialiser la population
population initPopulation();

// Définition de la fonction qui permet de redimensionné la population
void resizeArray(Person** *array, const int newCapacity);

// Définition de la fonction qui permet d'inserer les personnes dans la population
void insert(population pop, int key, Person* p);

// Définition de la fonction qui permet de lier les personnes par parenté
void linkPopulation(population pop);

int getHash (population pop, int id);
#endif