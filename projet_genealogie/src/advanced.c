#include <stdio.h>  
#include <stdlib.h>
#include "advanced.h"
#include "population.h"

#define CAPACITY_FRATERIE 10

// Definition des fonctions de la queue
queue *new_queue(int q_size)
{
    queue *newQueue = malloc(sizeof(queue));
    if (!newQueue)
    {
        printf("ERROR: Memory allocation failed for queue!\n");
        exit(EXIT_FAILURE);
    }
    newQueue->array = malloc(q_size * sizeof(int));
    if (!newQueue->array)
    {
        printf("ERROR: Memory allocation failed for queue array!\n");
        free(newQueue);  // Free the queue structure before exiting
        exit(EXIT_FAILURE);
    }
    newQueue->tail = -1;
    newQueue->top = -1;
    newQueue->q_size = q_size;
    return newQueue;
}

int is_queue_empty(queue *q)
{
    return q->top == -1 && q->tail == -1;
}

int is_queue_full(queue *q)
{
    return (q->tail + 1) % q->q_size == q->top;
}

void enqueue(queue *q, int value)
{
    if (!is_queue_full(q))
    {
        q->tail = (q->tail + 1) % q->q_size;
        q->array[q->tail] = value;
        if (q->top == -1) // Pour la premiere insertion
        {
            q->top = 0;
        }
    }
    else
    {
        fprintf(stderr, "The queue is full !!\n");
        exit(EXIT_FAILURE);
    }
}

int dequeue(queue *q)
{
    if (!is_queue_empty(q))
    {
        int returnValue = q->array[q->top];
        if (q->top == q->tail) // Case ou il y a un seul element dans la file
        {
            q->top = q->tail = -1;
        }
        else
        {
            q->top = (q->top + 1) % q->q_size;
        }
        return returnValue;
    }
    else
    {
        printf("Queue underflow: Can't dequeue!\n");
        exit(EXIT_FAILURE);
    }
}

void free_queue(queue* q)
{
    free(q->array);
    free(q);
}

// Finding siblings (fratrie) of a person
fratrie findFratrie(population pop, Person* p)
{
    fratrie frat;
    frat.size = 0;
    frat.capacity = CAPACITY_FRATERIE;
    frat.fratrieList = calloc(CAPACITY_FRATERIE, sizeof(Person*));
    if (frat.fratrieList == NULL)
    {
        fprintf(stderr, "Allocation failed for fraterieList\n");
        exit(EXIT_FAILURE);
    }

    if (p == NULL)
    {
        fprintf(stderr, "Person p is NULL\n");
        return frat;
    }

    // Information about the person
    int father_id = p->father_id;
    int mother_id = p->mother_id;
    int id = p->id;

    // Searching the entire population for siblings
    for (int i = 0; i < pop.capacity; i++)
    {
        if (pop.popDatas[i])
        {
            // Check if it is a sibling
            if (pop.popDatas[i]->id != id && pop.popDatas[i]->father_id == father_id && pop.popDatas[i]->mother_id == mother_id)
            {
                if (frat.size == frat.capacity - 1)
                {
                    frat.fratrieList = realloc(frat.fratrieList, 2 * frat.capacity * sizeof(Person*));
                    if (frat.fratrieList == NULL)
                    {
                        fprintf(stderr, "Reallocation failed for fratrieList\n");
                        exit(EXIT_FAILURE);
                    }
                    
                    frat.capacity *= 2;
                }
                // Adding the sibling to the list
                frat.fratrieList[frat.size++] = pop.popDatas[i];
            }
        }
    }
    return frat;
}

ancestors ancestorsPersons(population pop, Person* p) {
    ancestors ances;
    ances.capacity = pop.capacity;
    ances.ancestorsSize = 0;
    ances.ancestorsList = malloc(ances.capacity * sizeof(Person*));
    if (ances.ancestorsList == NULL) {
        fprintf(stderr, "Memory allocation failed for ances.ancesList !!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the queue
    queue* q = new_queue(ances.capacity);
    enqueue(q, hash_O(pop, p->id));

    while (!is_queue_empty(q)) {
        if (ances.ancestorsSize == ances.capacity) {
            ances.capacity *= 2;
            ances.ancestorsList = realloc(ances.ancestorsList, ances.capacity * sizeof(Person*));
            if (ances.ancestorsList == NULL) {
                fprintf(stderr, "Memory reallocation failed for ancestorsList\n");
                exit(EXIT_FAILURE);
            }
        }

        int index = dequeue(q);
        ances.ancestorsList[ances.ancestorsSize++] = pop.popDatas[index];

        if (index) {
            
            int father_id = pop.popDatas[index]->father_id;
            int mother_id = pop.popDatas[index]->mother_id;

            // Ensure that the father exists
            if (father_id)
                enqueue(q, hash_O(pop, father_id));
                else
                enqueue(q, hash_O(pop, 0));

            if (mother_id)
                enqueue(q, hash_O(pop, mother_id));
            else
                enqueue(q, hash_O(pop, 0));
        }
    }

    free_queue(q);
    return ances;
}
