#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "person.h"

typedef struct population {
    int size;
    int capacity;
    Person** popDatas;
}population;

/*
Le choix d'un tableau comme structure de stockage est dù au fait qu'ici nous voulons juste stocker les personnes contenues dans le fichier CSV, des personnes qui possècent des identifiants.
Par la suite pour une quelconque opération de recherche dans la population, nous pourrons retrouver cette personne avec une complexité temps de 1, O(1).
NB: S'il y'a plusieurs personnes avec des parents manquants, j'utiliserai un hashMap comme structure de données.
Sinon, je m'entiendrai au tableau.
Vu qu'il existe une possibilité que les identifiants ne soit pas toujours consécutifs, il est préférable d'utiliser un <hashTable> comme structure de données.
*/


// Hash table struct
int hash_O(population pop, int key);

population popInitialization();

population read_csv(const char* filename);
void chomp(char *line);


void insert(population* p, int key, Person* data);
Person* getPerson(population pop, int id);
void linkPopulation(population p);

#endif