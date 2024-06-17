#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htmlexport.h"
#include "person.h"
#include "population.h"
#include "advanced.h"

const char* htmlTop = "<!DOCTYPE html>\n"
                    "<html lang=\"en\">\n"
                    "<head>\n"
                    "    <meta charset=\"UTF-8\">\n"
                    "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                    "    <link rel=\"stylesheet\" href=\"../others/style.css\">\n"
                    "    <title>Projet CIR 2024</title>\n"
                    "</head>\n"
                    "<body>\n";

const  char* htmlEnd = "</body>\n"
                       "</html>\n";

//implémentation de la fonction pour créer un titre HTML pour une personne
int titreHTMLPerson(char *buffer, Person *p){
    return sprintf(buffer, "\n\t<h2>%s, %s</h2>\n", p->firstname, p->lastname);
}

// Fonction pour écrire la date dans le buffer
void dateHTMLPerson(char *buffer, Person *p){
    sprintf(buffer, "\t<p>%d / %d / %d</p>\n", p->birthday, p->birthmonth, p->birthyear);
}

// Fonction pour écrire la ville dans le buffer
void villeHTMLPerson(char *buffer, Person *p){
    sprintf(buffer, "\t<p>%s</p>", p->birthzipcode);
}

// implémentation de la fonction pour écrire le chemin du fichier dans le buffer
int fichePath(char *buffer, Person *p){
   return sprintf(buffer, "%d-fiche.html", p->id);
}

void exportPersonToHTML(const population pop, Person *p, char *path)
{
    // définition du header de la page HTML

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

    printAncestorsToHTML(buffer,pop,p);
    //titreHTMLPerson(buffer, p);
    //dateHTMLPerson(buffer + strlen(buffer), p);
   // villeHTMLPerson(buffer + strlen(buffer), p);
   
    // Ajout du titre h2 dans le fichier HTML
    fprintf(file, "%s", buffer);

    // Ajout du reste du content de la page HTML
    fprintf(file, "%s", htmlEnd);

    // fermeture du fichier
    fclose(file);
}



int printAncestorsToHTML(char *buffer, const population pop, Person *p) {
    ancestors ances = ancestorsPersons(pop, p);
    // prendre la taille du buffer contenant le header du html
    int offset = strlen(buffer);
   
    
    int generation = 1;
    offset += sprintf(buffer + offset, "<div class=\"generation-%d\"><h2>%s, %s</h2></div>\n", 0, ances.ancestorsList[0]->firstname, ances.ancestorsList[0]->lastname);
    for (int i = 1; i < ances.ancestorsSize; i++) 
    {
        Person* p = ances.ancestorsList[i];
        //addPersonToBuffer(p, generation,strlen(buffer), buffer);
        offset += sprintf(buffer + offset, "<div class=\"generation-%d\"><h2>%s, %s</h2></div>\n", generation, p->firstname, p->lastname);
        //printf("<div class=\"generation-%d\"><h2>%s, %s</h2></div>\n", generation, ances.ancestorsList[i]->firstname, ances.ancestorsList[i]->lastname);
    
        // passe à une autre génération
        if (i % 2 == 1) {
            generation++;
        }
    }

    free(ances.ancestorsList);
    return offset;
}

