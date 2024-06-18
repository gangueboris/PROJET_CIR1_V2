#ifndef PERSON_HTML_H
#define PERSON_HTML_H

#include "person.h"
#include "population.h"
#define BUFFER_SIZE 3000

// Fonction pour créer un titre HTML pour une personne
int titreHTMLPerson(char *buffer, Person *p);

// Fonction pour écrire le chemin du fichier dans le buffer
int fichePath(char *buffer, Person *p);

// fonction permettant d'exporter les données voulues en HTML
void exportPersonToHTML(const population pop, Person *p, char *path, int(*f)(char *buffer, const population pop, Person *p));

//fonction qui permet de représenter l'arbre généalogique d'une personne
int printAncestorsToHTML(char *buffer, const population t, Person *p); // faire demain

// fonction qui permet de représenter la fratrie d'une personne en HTML
int printFratrieToHTML(char *buffer, const population pop, Person *p);

#endif