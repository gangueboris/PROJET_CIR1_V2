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
typedef struct queue
{
    int top;
    int tail;
    int q_size;
    int* array;
}queue;

// fonctions associées à la structure de données : file
queue * new_queue(int q_size); 
void enqueue(queue*, int val); 
int dequeue(queue *); 
int is_queue_empty(queue *);
int is_queue_full(queue *);
void free_queue(queue* q);


// Implémentation d'autres options en +
int compareDate(const void *a, const void *b);
int compareStrings(const void *a, const void *b);

population findNbyTown(population pop);
#endif 