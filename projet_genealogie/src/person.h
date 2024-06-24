#ifndef _PERSON_H_
#define _PERSON_H_

// définition du struct d'une personne
typedef struct person{ 
    int id; 
    int father_id; 
    int mother_id; 
    char lastname[20]; 
    char firstname[20]; 
    int birthday; int birthmonth; int birthyear; 
    char birthzipcode[30]; 
    struct person * p_father; 
    struct person * p_mother; 
}Person;

//Déclaration de la fonction d'initialisation d'une personne
Person * initPerson(char *csvline); 
#endif 
