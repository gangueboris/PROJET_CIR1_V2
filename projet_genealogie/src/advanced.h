#ifndef _ADVANCED_H_
#define _ADVANCED_H_
#define QUEUE_SIZE 50
#include "person.h"
#include "population.h"

//Définition de la structure Fratries
typedef struct fratrie
{
    int size;
    int capacity;
    Person** fratrieList;
}fratrie;

// Définition de la sturture ancestors
typedef struct ancestors
{
    int ancestorsSize;
    int capacity;
    Person** ancestorsList;
}ancestors;

// fonction permettant de retrouver la fratrie d'une personne dans la population
fratrie findFratrie(population pop, Person* p);

// fonction permettant de les ancêtres d'une personne
ancestors ancestorsPersons(population pop, Person* p);

// struture de la structure de données: file
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

#endif