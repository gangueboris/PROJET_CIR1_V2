#ifndef HTMLEXPORT_HTMLEXPORT_H
#define HTMLEXPORT_HTMLEXPORT_H

int titreHTMLPerson(char *buffer, person *p);

int fichePath(char *buffer, person *p ,int choix);

void exportPersonToHTML(population *t, person *p, char *path, int choice);

int printAncestorsToHTML(char *buffer, population *t, person *p);

int printBrotherhoodToHtml(char *buffer, population *t, person *p);

int printInformationToHtml(char *buffer, person *p);

#endif