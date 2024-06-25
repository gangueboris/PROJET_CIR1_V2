#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

// Implémentation de la fonction d'initialisation d'une personne
Person* initPerson(char* csvline)
{
    Person* p = malloc(sizeof(Person));
    if (p == NULL)
    {
        perror("Memory allocation failed for p in initPerson\n");
        exit(EXIT_FAILURE);
    }
    
    char* token = strtok(csvline, ","); // get the first token, the id
    p->id = atoi(token);
    
    token = strtok(NULL, ",");
    p->father_id = atoi(token);

    token = strtok(NULL, ",");
    p->mother_id = atoi(token);
    
    token = strtok(NULL, ",");
    strcpy(p->lastname, token);

    token = strtok(NULL, ",");
    strcpy(p->firstname, token);

    char* date_token = strtok(NULL, ","); // get the date

    token = strtok(NULL, ",");
    strcpy(p->birthzipcode, token);

    // split the date
    if(strcmp(date_token, "-") == 0)
    {
        p->birthday = 0;
        p->birthmonth = 0;
        p->birthyear = 0;
    }
    else
    {
        date_token = strtok(date_token, "/");
        p->birthday = atoi(date_token);
        date_token = strtok(NULL, "/");
        p->birthmonth = atoi(date_token);
        date_token = strtok(NULL, "/");
        p->birthyear = atoi(date_token);
    }


    

    // Initial is parent to NULL
    p->p_father = NULL;
    p->p_mother = NULL;

    return p;
} 
