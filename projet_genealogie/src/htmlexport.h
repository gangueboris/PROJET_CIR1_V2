#ifndef _EXPORT_HTML_H_
#define _EXPORT_HTML_H_

#include "person.h"
#include "population.h"

#define PATH_SIZE 255

int titreHTMLPerson(char* buffer, Person* p);

int fichePath(char* buffer, Person* p);

void exportPersonToHTML(const population pop, Person* p, char* path, int (*f)(char* buffer, const population pop, Person* p));

void exportPersonToHTMLV2(const population pop, int n, char* ville, char* path, int (*f)(char* buffer, population pop, int n, char* ville));

int printContentToHTML(char* buffer,const population pop, Person* p, int (*f)(char* buffer, const population pop, Person* p));

int printContentToHTMLV2(char* buffer,const population pop, int n, char* ville, int (*f)(char* buffer, population pop, int n, char* ville));

int contentAncestors(char* buffer, const population pop, Person* p);

int contentFratrie(char* buffer, const population pop, Person* p);

void helperContentAncestors(const population pop, Person* p);

int contentNbyTown(char* buffer, population pop, int n, char* ville);

#endif