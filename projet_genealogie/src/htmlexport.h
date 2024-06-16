#ifndef PERSON_HTML_H
#define PERSON_HTML_H

#include "person.h"
#include "population.h"
#define BUFFER_SIZE 1024

// Fonction pour créer un titre HTML pour une personne
int titreHTMLPerson(char *buffer, Person *p);

// Fonction pour écrire le chemin du fichier dans le buffer
int fichePath(char *buffer, Person *p);

// fonction permettant d'exporter les données voulues en HTML
void exportPersonToHTML(const population pop, Person *p, char *path);

#endif