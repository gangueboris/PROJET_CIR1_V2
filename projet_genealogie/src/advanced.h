#ifndef _FRATRIE_H_
#define _FRATRIE_H_

#include "person.h"
#include "population.h"

#define FRATRIE_SIZE 10
#define ANCES_SIZE 10
#define QUEUE_SIZE 100
typedef struct 
{
    int size;
    int capacity;
    Person** fratrieTab;
}fratrie;

typedef struct 
{
   int size;
   int capacity;
   Person** ancestorsTab;
}ancestors;

// Définition de la fonction qui permet de trouver la fratrie d'une personnne
fratrie findFratrie(population pop, int id);

// Définition de la fonction qui permet de trouver les ancêtres d'une personne dans la population
ancestors ancestorsPersons(population pop, int id);


// Fonctions utilitaires
/*------- Queue ------*/
typedef struct 
{
    int top;
    int tail;
    int capacity;
    int* array;
}queue;

void enqueue(queue q, int val);
queue initQueue(int size);
int dequeue (queue q);
int isEmpty(queue q);
int isFull(queue q);
void freeQueue(queue q);
/*------Set-----*/

typedef struct 
{
    int capacity;
    int* array;
}set;

set initSet(int size);
int inSet(set s, int value);
void add(set s, int value);

#endif 