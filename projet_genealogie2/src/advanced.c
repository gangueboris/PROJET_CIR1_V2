#include <stdio.h>  
#include <stdlib.h>
#include "advanced.h"
#include "population.h"

#define CAPACITY_FRATERIE 10

// implémentation de la fonction d'initialisation de la file
queue *new_queue(int q_size)
{
    queue *newQueue = malloc(sizeof(queue));
    if (!newQueue)
    {
        printf("ERROR:Echec d'allocation pour newqueue !!\n");
        exit(EXIT_FAILURE);
    }
    newQueue->array = malloc(q_size * sizeof(int));
    if (!newQueue->array)
    {
        printf("ERROR: Echec d'allocation pour q->array !!\n");
        free(newQueue); 
        exit(EXIT_FAILURE);
    }
    newQueue->tail = -1;
    newQueue->top = -1;
    newQueue->q_size = q_size;
    return newQueue;
}

// fonction permettant de vérifier si la file est vide ou pas
int is_queue_empty(queue *q)
{
    return q->top == -1 && q->tail == -1;
}

// fonction permettant de vérifier si la file est pleine ou pas
int is_queue_full(queue *q)
{
    return (q->tail + 1) % q->q_size == q->top;
}

// fonction permettant d'ajouter un nouvel élément dans la file
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
        fprintf(stderr, "La file est pleine !!\n");
        exit(EXIT_FAILURE);
    }
}

// fonction permettant de récupérer le premier élément de la liste
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
        printf("la file est vide, Impossible de dequeue !!\n");
        exit(EXIT_FAILURE);
    }
}

// fonction permettant de libérer la mémoire alloué pour la file
void free_queue(queue* q)
{
    free(q->array);
    free(q);
}

// implémentation de la fonction permettant de retrouver la fratrie d'une personne dans la population
fratrie findFratrie(population pop, Person* p)
{
    fratrie frat;
    // initialisation de la variable frat
    frat.size = 0;
    frat.capacity = CAPACITY_FRATERIE;
    frat.fratrieList = calloc(CAPACITY_FRATERIE, sizeof(Person*));
    if (frat.fratrieList == NULL)
    {
        fprintf(stderr, "Echec d'allocation pour fraterieList\n");
        exit(EXIT_FAILURE);
    }

    // récupération des informations sur la personne
    int father_id = p->father_id;
    int mother_id = p->mother_id;
    int id = p->id;

    //recherche dans toute la population les frères et soeurs de la personne
    for (int i = 0; i < pop.capacity; i++)
    {
        if (pop.popDatas[i]) // si on tombe sur une position valide, 
        {
            // vérification qu'il s'agisse d'un frère ou d'une soeur
            if (pop.popDatas[i]->id != id && pop.popDatas[i]->father_id == father_id && pop.popDatas[i]->mother_id == mother_id && pop.popDatas[i]->father_id != 0 && pop.popDatas[i]->mother_id != 0)
            {
                // gestion de l'espace de stockage dans la table de hachage
                if (frat.size == frat.capacity - 1)
                {
                    frat.fratrieList = realloc(frat.fratrieList, 2 * frat.capacity * sizeof(Person*));
                    if (frat.fratrieList == NULL)
                    {
                        fprintf(stderr, "Echec de reallocation pour fratrieList\n");
                        exit(EXIT_FAILURE);
                    }
                    
                    frat.capacity *= 2;
                }
                // ajouter du frère ou de la soeur à la list de la fratrie
                frat.fratrieList[frat.size++] = pop.popDatas[i];
            }
        }
    }
    return frat;
}

// implémentation de la fonction permettant de les ancêtres d'une personne
ancestors ancestorsPersons(population pop, Person* p) {
    ancestors ances;
    // initialisation de la variable ances
    ances.capacity = pop.capacity;
    ances.ancestorsSize = 0;
    ances.ancestorsList = malloc(ances.capacity * sizeof(Person*));
    if (ances.ancestorsList == NULL) {
        fprintf(stderr, "Echec d'allocation pour ances.ancesList !!\n");
        exit(EXIT_FAILURE);
    }
    
    //Note: Dans cette partie, j'ai opté pour un level order traversal afin de stocker les personnes par génération

    // Initialisation de la file 
    queue* q = new_queue(ances.capacity);
    enqueue(q, hash_O(pop, p->id)); // ajout de la première personne dans la file
  
    while (!is_queue_empty(q)) // Continiué le process tant que la file n'est pas vide
    {
        // gestion de la capacité de stockage du tableau contenant les ancêtres de la personne
        if (ances.ancestorsSize == ances.capacity) 
        {
            ances.capacity *= 2;
            ances.ancestorsList = realloc(ances.ancestorsList, ances.capacity * sizeof(Person*));
            if (ances.ancestorsList == NULL) {
                fprintf(stderr, "Memory reallocation failed for ancestorsList\n");
                exit(EXIT_FAILURE);
            }
        }
         // recupérer la personne en tête de la file et l'ajouter au tableau de la génération
        int index = dequeue(q);
        ances.ancestorsList[ances.ancestorsSize++] = pop.popDatas[index];
        
        if (index)  // S'assurer que la personne en tête du tableau n'est pas la personne inconnu (car elle est la dernière personne de la génération)
        {
            // récupération des indices des parents de la personne acctuelle
            int father_id = pop.popDatas[index]->father_id;
            int mother_id = pop.popDatas[index]->mother_id;

            if (father_id) // si le père exist, l'ajouter à la file
                enqueue(q, hash_O(pop, father_id));
                else       // au cas contraire, le père de la personne est la personne inconnu, donc on ajoute la personne inconnu à la file
                enqueue(q, hash_O(pop, 0));

            if (mother_id) // si le mère exist, l'ajouter à la file
                enqueue(q, hash_O(pop, mother_id));
            else           // au cas contraire, le mère de la personne est la personne inconnu, donc on ajoute la personne inconnu à la file
                enqueue(q, hash_O(pop, 0));
        }
    }

    free_queue(q); // libération de la mémoire alloué pour queue
    return ances;
}
