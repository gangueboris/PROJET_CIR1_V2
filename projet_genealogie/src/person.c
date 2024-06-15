#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
#include "population.h"

//Initialisation d’une personne
Person *initPerson(char *csvline)
{
    Person* p = malloc(sizeof(Person));
    if (!p)
    {
        fprintf(stderr, "Memory not allocated !!\n");
        exit(EXIT_FAILURE);
    }

    // Tokenisation et stockage the information dans 'person'
    char* token = strtok(csvline, ",");
    if (token) p->id = atoi(token);

    token = strtok(NULL, ",");
    if (token) p->father_id = atoi(token);

    token = strtok(NULL, ",");
    if (token) p->mother_id = atoi(token);

    token = strtok(NULL, ",");
    if (token) {
        strncpy(p->lastname, token, sizeof(p->lastname) - 1);
        p->lastname[sizeof(p->lastname) - 1] = '\0';
    }

    token = strtok(NULL, ",");
    if (token) {
        strncpy(p->firstname, token, sizeof(p->firstname) - 1);
        p->firstname[sizeof(p->firstname) - 1] = '\0';
    }

    token = strtok(NULL, ",");
    if (token && strcmp(token, "-") != 0) {
        char* dateToken = strtok(token, "/");
        if (dateToken) p->birthday = atoi(dateToken);

        dateToken = strtok(NULL, "/");
        if (dateToken) p->birthmonth = atoi(dateToken);

        dateToken = strtok(NULL, "/");
        if (dateToken) p->birthyear = atoi(dateToken);
    } else {
        p->birthday = 0;
        p->birthmonth = 0;
        p->birthyear = 0;
    }

    token = strtok(NULL, ",");
    if (token) {
        printf("Hello\n");
        strncpy(p->birthzipcode, token, sizeof(p->birthzipcode) - 1);
        p->birthzipcode[sizeof(p->birthzipcode) - 1] = '\0';
    }

    // Initialization of parents to NULL
    p->p_father = NULL;
    p->p_mother = NULL;

    return p;
}