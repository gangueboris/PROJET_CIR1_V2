#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "advanced.h"
#include "population.h"

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
        if(pop.personstorage[i] && pop.personstorage[i]->id != 0 && pop.personstorage[i]->father_id != 0 && pop.personstorage[i]->mother_id != 0 && id != pop.personstorage[i]->id && father_id == pop.personstorage[i]->father_id && mother_id == pop.personstorage[i]->mother_id)
        {
            frat.fratrieTab[frat.size] = pop.personstorage[i];
            frat.size++ ;
        }
    }
    return frat;
}

// Implémentation des fonctions utilitaires
// Fonction d'initialisation de la file
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

// Implémentation de la fonction qui permet de générer un tableau d'ancêtre d'une personne
ancestors ancestorsPersons(population pop, int id) {
    ancestors ances;
    // initialisation de la variable ances
    ances.capacity = pop.capacity;
    ances.size = 0;
    ances.ancestorsTab = malloc(ances.capacity * sizeof(Person*));
    if (ances.ancestorsTab == NULL) {
        fprintf(stderr, "Echec d'allocation pour ances.ancesList !!\n");
        exit(EXIT_FAILURE);
    }
    
    //Note: Dans cette partie, j'ai opté pour un level order traversal afin de stocker les personnes par génération

    // Initialisation de la file 
    queue* q = new_queue(ances.capacity);
    enqueue(q, getHash(pop, id)); // ajout de la première personne dans la file
  
    while (!is_queue_empty(q)) // Continiué le process tant que la file n'est pas vide
    {
        // gestion de la capacité de stockage du tableau contenant les ancêtres de la personne
        if (ances.size == ances.capacity) 
        {
            ances.capacity *= 2;
            ances.ancestorsTab = realloc(ances.ancestorsTab, ances.capacity * sizeof(Person*));
            if (ances.ancestorsTab == NULL) {
                fprintf(stderr, "Memory reallocation failed for ancestorsList\n");
                exit(EXIT_FAILURE);
            }
        }
         // recupérer la personne en tête de la file et l'ajouter au tableau de la génération
        int index = dequeue(q);
        ances.ancestorsTab[ances.size++] = pop.personstorage[index];
        
        if (index)  // S'assurer que la personne en tête du tableau n'est pas la personne inconnu (car elle est la dernière personne de la génération)
        {
            // récupération des indices des parents de la personne acctuelle
            int father_id = pop.personstorage[index]->father_id;
            int mother_id = pop.personstorage[index]->mother_id;

            if (father_id) // si le père exist, l'ajouter à la file
                enqueue(q, getHash(pop, father_id));
                else       // au cas contraire, le père de la personne est la personne inconnu, donc on ajoute la personne inconnu à la file
                enqueue(q, getHash(pop, 0));

            if (mother_id) // si le mère exist, l'ajouter à la file
                enqueue(q, getHash(pop, mother_id));
            else           // au cas contraire, le mère de la personne est la personne inconnu, donc on ajoute la personne inconnu à la file
                enqueue(q, getHash(pop, 0));
        }
    }

    free_queue(q); // libération de la mémoire alloué pour queue
    return ances;
}


/*------------------------------------------Implémentation des fonctions en + ----------------------------------------------*/

// function de comparaison pour qsort

int compareDate(const void *a, const void *b) 
{
    Person *personA = *(Person **)a;
    Person *personB = *(Person **)b;
    //printf("a: %d\tb : %d\n",personA->birthyear, personB->birthyear);
    if (personA->birthyear < personB->birthyear) return -1;
    if (personA->birthyear > personB->birthyear) return 1;


    // If years are the same, compare months
    if (personA->birthmonth < personB->birthmonth) return -1;
    if (personA->birthmonth > personB->birthmonth) return 1;

    // If months are also the same, compare days
    if (personA->birthday < personB->birthday) return -1;
    if (personA->birthday > personB->birthday) return 1;

    return 0; // If all are the same, the persons are equal
}


// Implémentation de la fonction qui permet de trouver les personne qui le même prénom dans la population
/*
Dans cette partie, je trie d'abord et j'aurai ainsi les personnes ordonées par ville.Se sera dans la partie html je vais gérer par affichage par ville
*/
// Fonction de comparaison pour des chaine de charatères
int compareStrings(const void *a, const void *b)
{
    Person* A = *(Person**)a;
    Person* B = *(Person**)b;

    return strcmp(A->birthzipcode, B->birthzipcode);
}


population findNbyTown(population pop)
{
    // Dans cette partie, je fais en sorte que les personnes soit contigu dans un nouveau tableau
    population popclone = initPopulation(pop.capacity);
    for (int i = 0; i < popclone.capacity; i++)
    {
        if(pop.personstorage[i])
        {
            popclone.personstorage[popclone.size] = pop.personstorage[i];
            popclone.size++; // Mise à jour de la taille  
              
        }
    }
   
    //printf("Capacity: %d\tSize: %d\n", popclone.capacity, popclone.size);
    qsort(popclone.personstorage, popclone.size, sizeof(Person*), compareStrings);  

    return popclone;
}
