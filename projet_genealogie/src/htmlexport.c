#include <stdio.h>
#include <stdlib.h>

#include "htmlexport.h"
#include "advanced.h"
#include "person.h"
#include "population.h"

#define BUFFER_SIZE 5000

const char* htmlHeader = "<!DOCTYPE html>\n"
                          "<html lang=\"en\">\n"
                          "<head>\n"
                                "<meta charset=\"UTF-8\">\n"
                                "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                                "<link rel=\"stylesheet\" href=\"../others/style.css\">\n"
                                "<title> id-fiche.html</title>\n"
                           "</head>\n"
                           "<body>\n";


const char* htmlEnd = "</body>\n"
                       "</html>\n";

// Implémentation de la fonction qui permet d'écrire le titre d'une personne dans une balise h2
int titreHTMLPerson(char* buffer, Person *p)
{
    // <h2> Dupont, Jean</h2> 
    return sprintf(buffer, "\t<h2> %s, %s </h2>\n", p->lastname, p->firstname);
}

// Implémenter de la fonction qui écrit le nom de la fiche dans un buffer
int fichePath(char* buffer, Person* p)
{
    // [id_person]-fiche.html
    return sprintf(buffer, "[%d]-fiche.html", p->id);
}

void exportPersonToHTML(const population pop, Person* p, char* path, int (*f)(char* buffer, const population pop, Person* p))
{
    FILE* file = fopen(path, "w"); // creation du fichier dans le dossier de destination
    if (file == NULL)
    {
        perror("Can't open file to write in  !! \n");
        exit(EXIT_FAILURE);
    }
    // Initialisation du buffer 
    char buffer[BUFFER_SIZE];

    // Ecriture dans le buffer HTML
    printContentToHTML(buffer,pop, p, f);

    // Ecriture dans le fichier HTML
    fprintf(file, "%s", buffer);
    fclose(file);
}

// Implémentation de la fonction qui permet n'importe quelle contenu dans le buffer html
int printContentToHTML(char* buffer,const population pop, Person* p, int (*f)(char* buffer, const population pop, Person* p))
{
    // Mise en page de l'en tête
    int n = sprintf(buffer,"%s", htmlHeader);
   
   /*-------------------- C'est dans cette partie que l'on écrira le contenu de la page HTML (ancestor, fratrie, ...) ---------------*/
    // Ecriture du titre dans le buffer

    n += titreHTMLPerson(buffer + n, p);
    
    // Ecriture du contenu dans le buffer HTML avec la fonction pointer sur fonction
    n += (*f)(buffer + n, pop, p);
    
    // Ajout des balises fermantes
    n += sprintf(buffer + n,"%s", htmlEnd);
    return n;
}

// Implémentation des fonctions contentAncestors et contentFratrie

// Implémentation de la fonction  ancestors
int contentAncestors(char* buffer, const population pop, Person* p)
{
   return 0;
}