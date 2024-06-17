#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
#include "population.h"
#define CITY_SIZE 255

Person* initPerson(char *csvline)
{
    Person* p = malloc(sizeof(Person));
    if (p == NULL) // Savoir si l'allocation a reussi ou pas
    {
        fprintf(stderr, "Memory not allocated !!\n");
        exit(EXIT_FAILURE);
    }

    // Décomposition et stockage des informations dans 'person'
    char* token = strtok(csvline, ","); // initialisation de l'id de la person
    if (token) p->id = atoi(token);

    token = strtok(NULL, ",");
    if (token) p->father_id = atoi(token); // initialisation de l'id du père

    token = strtok(NULL, ",");
    if (token) p->mother_id = atoi(token); // initialisation de l'id de la mère

    token = strtok(NULL, ",");
    if (token) {                         // initialisation du nom de la person
        strncpy(p->lastname, token, sizeof(p->lastname) - 1);     
        p->lastname[sizeof(p->lastname) - 1] = '\0';
    }

    token = strtok(NULL, ",");
    if (token) {                         // initialisation du prénom de la person
        strncpy(p->firstname, token, sizeof(p->firstname) - 1);
        p->firstname[sizeof(p->firstname) - 1] = '\0';
    }

    token = strtok(NULL, ",");

    char dateAllToken[CITY_SIZE];
    strcpy(dateAllToken, token);// copie de la chaine de charactère actuelle pour la décomposer plustard
    
    token = strtok(NULL, ","); // passer directement à la ville
    if (token) 
    {
        strncpy(p->birthzipcode, token, sizeof(p->birthzipcode) - 1); // initialisation de l'adresse de naissance de la person
        p->birthzipcode[sizeof(p->birthzipcode) - 1] = '\0';
    }
    //NB: le strtok ne travaille qu'avec un seul caractère séparateur à la fois
    // Là maintenant, on s'occupe décomposer la date.
    if (dateAllToken && strcmp(dateAllToken, "-") != 0) { 
        char* dateToken = strtok(dateAllToken, "/");
        if (dateToken) p->birthday = atoi(dateToken); // initialisation du jour de naissance de la person

        dateToken = strtok(NULL, "/");
        if (dateToken) p->birthmonth = atoi(dateToken); // initialisation du mois de naissance de la person

        dateToken = strtok(NULL, "/");
        if (dateToken) p->birthyear = atoi(dateToken); // initialisation de l'année de naissance de la person

    } else {            // Dans le cas on n'a pas des informations sur la personne
        p->birthday = 0;
        p->birthmonth = 0;
        p->birthyear = 0;
    }


    // Initialization of parents to NULL
    p->p_father = NULL;
    p->p_mother = NULL;

    return p;
}