#ifndef _PERSON_H_
#define _PERSON_H_

typedef struct person {
    int id;
    int father_id;
    int mother_id;
    char lastname[20]; // nom de famille
    char firstname[20]; // prénom
    int birthday; int birthmonth; int birthyear;
    char birthzipcode[30];
    struct person *p_father;
    struct person *p_mother;
} Person;

// Déclaration de la fonction iniPerson
Person *initPerson(char* csvline);

#endif
