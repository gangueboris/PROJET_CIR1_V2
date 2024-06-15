#include "population.h"
#include "stdio.h"
#include "stdlib.h"
#define LINE_LENGTH 100
#define CAPACITY 20

/*-----------------implement for hash Table by using open addressing ---------------------*/
// get hash
/*
J'utilise une fonction de hashage, si mes données ont un id [1000-8000] alors que 
mon tab a un size de 7000, je veux être capable de stocké mes informations de 0 - 7000, la fonction de 
hashage me permet de rester dans le range.
*/
int hash_O(population pop, int key)
{
   return key % pop.capacity;
}

// fonction pour initialiser la population
population popInitialization()
{
    population pop;
    pop.capacity = CAPACITY;
    pop.size = 0;
    pop.popDatas = calloc(CAPACITY, sizeof(Person*));

    if (pop.popDatas == NULL)
    {
        fprintf(stderr, "error, allocation failed for pop.persons\n");
        exit(EXIT_FAILURE);
    }
    return pop;
}

// fonction insert()
void insert(population* p, int key, Person* data)
{
    for (int i = 0; i < p->capacity; i++)
    {
        // pour pouvoir avancer si lors de la première itération la position est prise. ce qui ne risque pas d'arriver puisque les ids sont uniques
        int prob = (key + i) % p->capacity;

        if (p->popDatas[prob] == NULL)
        {
            p->popDatas[prob] = data;
            p->popDatas[prob]->key = prob;
            p->size++;
            break;
        }
        // Le cas du else est à revoir: puisque les ids sont uniques, si 
    }
}

// Function to get a person by key (ID)
Person* getPerson(population pop, int id) 
{
    for (int i = 0; i < pop.capacity; i++) {
        int prob = (hash_O(pop, id) + i) % pop.capacity;
        
        if (pop.popDatas[prob] == NULL) {
            return NULL; // Person not found
        }

        if (pop.popDatas[prob]->id == id) {
            return pop.popDatas[prob]; // Person found
        }
    }
    return NULL; // Person not found after probing all possible slots
}

void chomp(char *line) 
{
   char *c = line;
   while (*c != '\0') {
       if (*c == '\n' || *c == '\r') { 
           *c = '\0'; 
           return; 
       }
       c++; 
   }
}

// Fonction lecture de fichier

// Function to read the CSV file and populate the population
population read_csv(const char* filename) {
    population pop = popInitialization();

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", filename);
        return pop; // Return an empty population
    }

    char buffer[LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file)) {
        chomp(buffer);
        Person* p = initPerson(buffer);
        if (p != NULL) {
            if (pop.size == pop.capacity - 1) { // Resize if necessary
                pop.popDatas = realloc(pop.popDatas, 2 * pop.capacity * sizeof(Person*));
                if(!pop.popDatas) printf("Memory reallocation failed\n");
                pop.capacity *= 2;
                printf("Memory successfully reallocated for the population!!\n");
            }
            insert(&pop, hash_O(pop, p->id), p);
        }
    }
    fclose(file);
    return pop;
}

void linkPopulation(population pop)
{
    for (int i = 0; i < pop.capacity; i++)
    {
        if (pop.popDatas[i] == NULL) continue; // Skip empty slots in the hash table

        int father_id = pop.popDatas[i]->father_id;
        int mother_id = pop.popDatas[i]->mother_id;

        // If father_id or mother_id is 0, it means unknown; the person points to itself.
        if (father_id == 0)
        {
            pop.popDatas[i]->p_father = pop.popDatas[i];
        }
        else
        {
            pop.popDatas[i]->p_father = pop.popDatas[hash_O(pop, father_id)];
        }

        if (mother_id == 0)
        {
            pop.popDatas[i]->p_mother = pop.popDatas[i];
        }
        else
        {
            pop.popDatas[i]->p_mother = pop.popDatas[hash_O(pop, mother_id)];
        }
    }
}
