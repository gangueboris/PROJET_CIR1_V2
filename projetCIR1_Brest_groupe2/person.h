#ifndef PERSON_PERSON_H
#define PERSON_PERSON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 1000 // taille de la table de hachage fixée à 1000 peut être changer mais pas nécessaire
#define MAX_GENERATIONS 30 // nombre de générations max pour les ancêtres communs

typedef struct person{
	int id;
	int father_id;
	int mother_id;
	char lastname[20];
	char firstname[20];
	int birthday; int birthmonth; int birthyear;
	char birthzipcode[30];
	struct person* p_father;
	struct person* p_mother;
}person;

typedef struct node_person{
	person* p; // pointeur sur personne
	struct node_person *next; // pointeur next sur struct node_person
}node_person;

typedef struct population {
    node_person* table[TABLE_SIZE]; // tableau de pointeurs sur node_person
} population;

person* initPerson(char *csvline);

int hash(int id);

void initpopulation(population* ht);

void insert(population* p, person *data );

void linkPopulation(population* ht);

person* findPersonne(population* ht, int id);

person* findPersonBirthdate(population *population, int day, int month, int year);

person* findName(population *population, const char *firstname, const char *lastname);

person** ancestorsPersons(population* t, person *p);

person** trouverFratrie(population* ht, person *p, int* tailleFratrie);

person *findCommonAncestor(person *p1, person *p2);

#endif