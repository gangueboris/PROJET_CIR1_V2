#ifndef _ADVANCED_H_
#define _ADVANCED_H_
#define QUEUE_SIZE 50
#include "person.h"
#include "population.h"

//Fratries
typedef struct fratrie
{
    int size;
    int capacity;
    Person** fratrieList;
}fratrie;

typedef struct ancestors
{
    int ancestorsSize;
    int capacity;
    Person** ancestorsList;
}ancestors;

fratrie findFratrie(population pop, Person* p);

// Ancêtres
ancestors ancestorsPersons(population pop, Person* p);

// prototypes de la file
typedef struct queue
{
    int top;
    int tail;
    int q_size;
    int* array;
}queue;

queue * new_queue(int q_size); 
void enqueue(queue*, int val); 
int dequeue(queue *); 
int is_queue_empty(queue *);
int is_queue_full(queue *);
void free_queue(queue* q);

#endif