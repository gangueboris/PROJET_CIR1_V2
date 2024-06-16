#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "person.h"

typedef struct population {
    int size;
    int capacity;
    Person** popDatas;
}population;



int hash_O(population pop, int key);

// fonction pour initialiser le struct population
population popInitialization();

// fonction pour lire un fichier CSV et stocker les informations de chaque personne
population read_csv(const char* filename);

// fonction pour supprimer les  retours à la ligne au niveau de chaque ligne de lecture
void chomp(char *line);

// fonction pour insérer dans le hashMap(population) une personne
void insert(population* p, int key, Person* data);

// fonction pour retrouver une personne par son id
Person* getPerson(population pop, int id);

// fonction pour lié chaque chaque personne dans la population à ces parents
void linkPopulation(population p);

// fonction pour libérer la mémoire pour chaque personne et le tableau de personne
void freePersons(Person** p, int capacity);

// fonction pour compter le nombre de personne qui ont le même prénom dans la population
int count_firstname(population pop, Person* p);
#endif