#include <stdio.h>
#include <stdlib.h>
#include "advanced.h"

// Implémentation de la fonction qui permet de trouver la fratrie d'un personne
fratrie findFratrie(population pop, int id)
{
    // Iniitialisation de la fratrie 
    fratrie frat;
    frat.size = 0;
    frat.capacity = FRATRIE_SIZE;
    frat.fratrieTab = malloc(frat.capacity * sizeof(Person*));
    if (frat.fratrieTab == NULL)
    {
        perror("Memory allocation failed for frat.fratrieTab");
        exit(EXIT_FAILURE);
    }
    
    // Initialisation des parents de la personne
    int father_id = pop.personstorage[getHash(pop, id)]->father_id;
    int mother_id = pop.personstorage[getHash(pop, id)]->mother_id;

    for (int i = 0; i < pop.capacity; i++)
    {
        if(frat.size >= frat.capacity)
        {
           frat.capacity *= 2;
           frat.fratrieTab = resizeArray(frat.fratrieTab, frat.capacity);
        }
           
        // Recherche de la fratrie dans la population
        if(pop.personstorage[i] && id != pop.personstorage[i]->id && father_id == pop.personstorage[i]->father_id && mother_id == pop.personstorage[i]->mother_id)
        {
            frat.fratrieTab[frat.size] = pop.personstorage[i];
            frat.size++ ;
        }
    }
    return frat;
}

// Implémentation des fonctions utilitaires
// Fonction d'initialisation de la file
queue* initQueue(int size)
{
    queue* q = malloc(sizeof(queue));
    q->tail  = -1;
    q->top = -1;
    q->capacity = size;
    q->array = malloc(q->capacity * sizeof(int));
    if(q->array == NULL)
    {
        perror("Memory allocation failed for q.array !! \n");
        exit(EXIT_FAILURE);
    }
    return q;
}

void enqueue(queue* q, int val)
{
    if (!isFull(q))
    {
        if (q->top == -1)
        {
            q->top = 0;
        }
        q->tail = (q->tail + 1) % q->capacity;
        q->array[q->tail] = val;
       
    }
    else
    {
        printf("The queue is full \n");
    }
}

int dequeue(queue* q)
{
   if(!isEmpty(q))
   {
     int temp = q->array[q->top];
     if (q->top == q->tail) // Case ou il y a un seul element dans la file
     {
        q->top = q->tail = -1;
     }
    else
        {
            q->top = (q->top + 1) % q->capacity;
        }
     return temp;
   }
   else
   {
    printf("The queue is underflow !!\n");
    exit(EXIT_FAILURE);
   }
}
int isEmpty(queue* q)
{
    return q->tail == q->top;
}
int isFull(queue* q)
{
    return (q->top + 1) % q->capacity == q->tail;
}
// Fonction de libération de mémoire alloué pour la file
void freeQueue(queue* q)
{
    free(q->array);
    free(q);
}

// Implémentation de la fonction qui permet de générer un tableau d'ancêtre d'une personne
ancestors ancestorsPersons(population pop, int id)
{
    // Iniitialisation
    ancestors ances;
    ances.size = 0;
    ances.capacity = ANCES_SIZE;
    ances.ancestorsTab = malloc(ances.capacity * sizeof(Person*));
    if (ances.ancestorsTab == NULL)
    {
        perror("Memory allocation failed for ances.ancestorsTab");
        exit(EXIT_FAILURE);
    }

    queue* q = initQueue(pop.capacity);
    set visited = initSet(pop.capacity);
    enqueue(q, id);
    while(!isEmpty(q))
    {
        printf("gfdsgvezv f erg\n");
        int current = dequeue(q);
        ances.ancestorsTab[ances.size++] = pop.personstorage[getHash(pop, current)];
        if (!inSet(visited, current)) 
        {
           add(visited, current);
           //if (!inSet(visited, pop.personstorage[getHash(pop, current)]))
           enqueue(q,  pop.personstorage[getHash(pop, current)]->father_id);
           enqueue(q,  pop.personstorage[getHash(pop, current)]->mother_id);
        }
    }
    freeQueue(q);
    free(visited.array);
    return ances;
}

// Implémentation d'un set

set initSet(int size)
{
    set s;
    s.capacity = size;
    s.array = calloc(s.capacity, sizeof(int));
    return s;
}

int inSet(set s, int value)
{
    for(int i = 0; i < s.capacity; i++)
    { 
        int index = (value + i) % s.capacity;
        if(s.array[index] == value)
        {
            return 1;
        }
    }
    return 0;
}

void add(set s, int value)
{
    if(inSet(s, value))
        return;
    for(int i = 0; i < s.capacity; i++)
    {
        int index = (value + i) % s.capacity;
        if(s.array[index] == 0)
        {
            s.array[index] = value;
            return;
        }
    }
    printf("the set is full !!\n");
}