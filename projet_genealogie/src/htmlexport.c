#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htmlexport.h"
#include "person.h"
#include "population.h"

//implémentation de la fonction pour créer un titre HTML pour une personne
int titreHTMLPerson(char *buffer, Person *p)
{
    return sprintf(buffer, "\n\t<h2>%s, %s</h2>\n", p->firstname, p->lastname);
}

// implémentation de la fonction pour écrire le chemin du fichier dans le buffer
int fichePath(char *buffer, Person *p)
{
   return sprintf(buffer, "%d-fiche.html", p->id);
}

void exportPersonToHTML(const population pop, Person *p, char *path)
{
    // définition du header de la page HTML
    char* htmlTop = "<!DOCTYPE html>\n"
                "<html lang=\"en\">\n"
                "<head>\n"
                "    <meta charset=\"UTF-8\">\n"
                "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                "    <title></title>\n"
                "</head>\n"
                "<body>\n";

char* htmlEnd = "</body>\n"
                "</html>\n";

    
    // Création / ouverture du fichier [id_person]-fiche.html
    FILE *file = fopen(path, "w");
    
    // Vérifier si le fichier a été ouvert correctement
    if (file == NULL) {
        perror("Erreur dans l'ouverture du fichier \n");
        exit(EXIT_FAILURE);
    }

    // Ecriture dans le fichier
    fprintf(file, "%s", htmlTop); // mettre l'en-tête
    
    // Ecriture du titre
    char buffer[BUFFER_SIZE];
    int n = sprintf(buffer, "<h2>%s, %s</h2>\n", p->lastname, p->firstname); // Use appropriate format for title
    printf("%s\t%d\n", buffer,n);
    
    // Ajout du titre h2 dans le fichier HTML
    fprintf(file, "%s", buffer);

    // Ajout du reste de content de la page HTML
    fprintf(file, "%s", htmlEnd);

    // fermeture du fichier
    fclose(file);
}
