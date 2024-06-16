#include "population.h"
#include "stdio.h"
#include "stdlib.h"
#define LINE_LENGTH 100
#define CAPACITY 100

// fonction de hashage qui nous permet de tranformer n'importe quelle ID en un ID indexable dans la capacité de notre structure hashMap
int hash_O(population pop, int key)
{
   return key % pop.capacity;
}

// implémentation de la fonction pour initialiser notre structure de données
population popInitialization()
{
    population pop;
    pop.capacity = CAPACITY;
    pop.size = 0;
    pop.popDatas = calloc(CAPACITY, sizeof(Person*)); // allocation de la mémoire

    if (pop.popDatas == NULL) // au cas où l'allocation serait un échec
    {
        fprintf(stderr, "error, allocation failed for pop.persons\n");
        exit(EXIT_FAILURE);
    }
    return pop;
}

// implémentation de la fonction pour inserer dans le hashMap(population) une personne
void insert(population* p, int key, Person* data) //NB: key est issue de la fonction de hashage
{
    for (int i = 0; i < p->capacity; i++)
    {
        int pos = (key + i) % p->capacity;  // pour pouvoir avancé d'un pas au cas où la position serait déjà prise

        if (p->popDatas[pos] == NULL) // S'assurer que la position est libre 
        {
            p->popDatas[pos] = data; // stocker la personne dans la structure de données à la position 'pos'
            p->size++; // incrémenter de 1 le nombre d'élément dans le tableau
            break; // arrêter la recherche d'une position valide
        }
    }
}
// implémentation de la fonction pour retrouver une personne par son id
Person* getPerson(population pop, int id) 
{
    for (int i = 0; i < pop.capacity; i++) {
        int pos = (hash_O(pop, id) + i) % pop.capacity; // id indexable dans la table de hachage
        
        if (pop.popDatas[pos] == NULL) { // si l'index tombe sur une position NULL, la personne n'est pas dans la table de hachage
            return NULL; 
        }

        if (pop.popDatas[pos]->id == id) { 
            return pop.popDatas[pos]; // Personne trouvé
        }
    }
    return NULL; // Personne non trouvé jusqu'à la fin de la recherche dans toute la table de hachage
}

// implémentation de la fonction pour supprimer les  retours à la ligne au niveau de chaque ligne de lecture
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


// implémentation de la fonction pour lire un fichier CSV et stocker les informations de chaque personne
population read_csv(const char* filename) {
    population pop = popInitialization(); // initialisation de la population

    FILE* file = fopen(filename, "r"); // ouverture du fichier
    if (!file) { // vérification sur l'ouverture fût un succès ou un échec
        fprintf(stderr, "Error: Can't open file %s\n", filename);
        return pop; // retourner une population vide
    }

    char buffer[LINE_LENGTH]; // Déclaration du buffer
    while (fgets(buffer, sizeof(buffer), file)) // lecture de chaque ligne
    { 
        chomp(buffer); // élimination des retour à la ligne dans chaque ligne
        Person* p = initPerson(buffer); // initialisation de chaque personne avec ces informations
    
        if (pop.size == pop.capacity ) // Vérifier si la table de hachage est pleine. si oui, réalloué de la mémoire en la doublant
        { 
            pop.popDatas = realloc(pop.popDatas, 2 * pop.capacity * sizeof(Person*));
            if(!pop.popDatas) printf("Echec de la reallocation de la mémoire !!\n");
            pop.capacity *= 2;
            printf("Mémoire realloué avec succès !! \n");
        }
        insert(&pop, hash_O(pop, p->id), p); // insérer la personne dans la table de hachage avec son indexable
    }
    fclose(file); // libérer la mémoire alloué pour le fichier
    return pop;
}

// implémentation de la fonction pour lié chaque chaque personne dans la population à ces parents
void linkPopulation(population pop)
{
    for (int i = 0; i < pop.capacity; i++)
    {
        if (pop.popDatas[i] == NULL) continue; // éviter les positions vides

        int father_id = pop.popDatas[i]->father_id;
        int mother_id = pop.popDatas[i]->mother_id;

        /*Il est dit dans le sujet que si les parents d'une personne sont inconnus les pointers parents pointeront sur la personne inconnu donc ...*/
        if (father_id == 0) // si le père est inconnu
        {
            pop.popDatas[i]->p_father = pop.popDatas[hash_O(pop, 0)]; // c'est que c'est la personne inconnu
        }
        else
        {
            pop.popDatas[i]->p_father = pop.popDatas[hash_O(pop, father_id)]; // initialisation du père
        }

        if (mother_id == 0) // si mère est inconnu, 
        {
            pop.popDatas[i]->p_mother = pop.popDatas[hash_O(pop, 0)]; // c'est que la mère est la personne inconnu
        }
        else
        {
            pop.popDatas[i]->p_mother = pop.popDatas[hash_O(pop, mother_id)]; // initialisation de la mère
        }
    }
}


void freePersons(Person** p, int capacity)
{
    for (int i = 0; i < capacity; i++) 
    {
        if (p[i]) // s'assurer que la position est valide pour être supprimer
        {
            free(p[i]); // Libérer chaque personne
        }
    }
    free(p); // Libérer le tableau des personnes
}