#ifndef _EXPORT_HTML_H_
#define _EXPORT_HTML_H_

#include "person.h"
#include "population.h"
int titreHTMLPerson(char *buffer, Person *p);

int fichePath(char* buffer, Person* p);

void exportPersonToHTML(const population pop, Person* p, char* path, int (*f)(char* buffer, const population pop, Person* p));

int printContentToHTML(char* buffer,const population pop, Person* p, int (*f)(char* buffer, const population pop, Person* p));

int contentAncestors(char* buffer, const population pop, Person* p);
int contentFratrie(char* buffer, const population pop, Person* p);
#endif