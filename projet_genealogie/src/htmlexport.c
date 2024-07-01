#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    // [id_person]-fiche.html or ville.html
    return p == NULL ? sprintf(buffer, "../export/ville.html"):sprintf(buffer, "../export/%d-fiche.html", p->id);
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

// Cette version nous permet d'exporter d'autres format qui ne prenne pas en entrer la personne p
void exportPersonToHTMLV2(const population pop, int n, char* ville, char* path, int (*f)(char* buffer, population pop, int n, char* ville))
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
    printContentToHTMLV2(buffer,pop, n, ville, f);

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
    
    // Ecriture du contenu dans le buffer HTML avec la fonction pointer sur fonction
    n += (*f)(buffer + n, pop, p);
    
    // Ajout des balises fermantes
    n += sprintf(buffer + n,"%s", htmlEnd);
    return n;
}

// Cette version nous permet d'utiliser d'autres format qui ne prenne pas en entrer la personne p
int printContentToHTMLV2(char* buffer,const population pop, int n, char* ville, int (*f)(char* buffer, population pop, int n, char* ville))
{
    // Mise en page de l'en tête
    int k = sprintf(buffer,"%s", htmlHeader);
   
   /*-------------------- C'est dans cette partie que l'on écrira le contenu de la page HTML (ancestor, fratrie, ...) ---------------*/
    
    // Ecriture du contenu dans le buffer HTML avec la fonction pointer sur fonction
    k += (*f)(buffer + k, pop, n, ville);
    
    // Ajout des balises fermantes
    k += sprintf(buffer + k,"%s", htmlEnd);
    return k;
}


// Implémentation des fonctions contentAncestors et contentFratrie

// Implémentation de la fonction  ancestors
int contentAncestors(char* buffer, const population pop, Person* p)
{ 
    ancestors ances = ancestorsPersons(pop, p->id);
    
    // Présentation, en-tête 
    // NB: Pas besoin ici d'ajouter de l'offset car déjà ajouter lors de l'appel
    int offset = sprintf(buffer, "   <h1 class = \"titre-h1\"> ARBRE GENEALOGIQUE </h1>\n");
    offset += sprintf(buffer + offset, "   <div class = \"container\">\n");
    
    // Niveau 1: Personne don't on a les ancêtres
    offset += sprintf(buffer + offset, "    <div class=\"level-1 rectangle\">\n");
    offset += sprintf(buffer + offset, "        <h2> %s %s </h2>\n", p->firstname, p->lastname);
    offset += sprintf(buffer + offset, "        <p>%d / %d / %d </p>\n", p->birthday, p->birthmonth, p->birthyear);
    offset += sprintf(buffer + offset, "        <p> %s </p>\n", p->birthzipcode);
    offset += sprintf(buffer + offset, "    </div>\n\n");

    // Niveau 2: parents
    offset += sprintf(buffer + offset, "    <ol class=\"level-2-wrapper\">\n");
  
    for (int i = 1; i < ances.size && i <= 2 ; i++)    // i <= ances.size car on peut avoir moins de deux personnes comme ancêtres
    {
        offset += sprintf(buffer + offset, "        <li>\n");
        offset += sprintf(buffer + offset, "            <h2 class=\"level-2 rectangle\"><a href='%d-fiche.html'>%s<hr>  %s</a></h2>\n",ances.ancestorsTab[i]->id, ances.ancestorsTab[i]->firstname, ances.ancestorsTab[i]->lastname);
        offset += sprintf(buffer + offset, "            <ol class=\"level-3-wrapper\">\n");
        for (int j = 2 * i + 1; j < 2 * i + 3 && j < ances.size; j++)
        {
            offset += sprintf(buffer + offset, "                <li>\n");
            offset += sprintf(buffer + offset, "                    <h2 class=\"level-3 rectangle\"><a href='%d-fiche.html'>%s<hr>  %s</a></h2>\n",ances.ancestorsTab[j]->id, ances.ancestorsTab[j]->firstname, ances.ancestorsTab[j]->lastname);
            offset += sprintf(buffer + offset, "                </li>\n");
        }
        offset += sprintf(buffer + offset, "            </ol>\n");

        offset += sprintf(buffer + offset, "        </li>\n");    
    }

    offset += sprintf(buffer + offset, "    </ol>\n");


    offset += sprintf(buffer + offset, "</div>\n");

    free(ances.ancestorsTab); // Libération de la mémoire alloué les ancêtres
    return offset;
}



int contentFratrie(char* buffer, const population pop, Person* p)
{
    // récupérer la fratrie de la personne
    fratrie frat = findFratrie(pop, p->id);

    // Trier la fratrie date de naissance
    qsort(frat.fratrieTab, frat.size, sizeof(Person*), compareDate);
    

    /*---- Dans cette partie, nous écrivons du script html en C -----*/
    // NB: Pas besoin ici d'ajouter de l'offset car déjà ajouter lors de l'appel
    int offset = sprintf(buffer, "   <h1 class =\"titre-h1\">FRATRIE de %s</h1>\n", p->firstname);
    offset += sprintf(buffer + offset, "   <div class=\"fratrie-container\">\n");

    for (int i = 0; i < frat.size; i++) 
    {
        Person* sibling = frat.fratrieTab[i];
        offset += sprintf(buffer + offset, "        <div class=\"sibling rectangle\">\n");
        offset += sprintf(buffer + offset, "            <h2>%s, %s</h2>\n", sibling->firstname, sibling->lastname);
        offset += sprintf(buffer + offset, "            <p> %02d/%02d/%04d </p>\n", sibling->birthday, sibling->birthmonth, sibling->birthyear);
        offset += sprintf(buffer + offset, "            <p> %s </p>\n", sibling->birthzipcode);
        offset += sprintf(buffer + offset, "        </div>\n");
    }
    if (frat.size == 0)
    {
        offset += sprintf(buffer + offset, "        <p>%s n'a pas de fratrie.</p>\n", p->firstname);
    }
    
    offset += sprintf(buffer + offset, "   </div>\n");

    free(frat.fratrieTab);
    return offset;
}

// Cette fonction nous permet de générer les fichiers html du reste de la génération
void helperContentAncestors(const population pop, Person* p) 
{
    ancestors ances = ancestorsPersons(pop, p->id);
   
    char path[PATH_SIZE]; // Definition de chemin de savergarde du fichier

    // Générer les fichiers HTML pour toute la génération
    for (int i = 0; i < ances.size; i++) 
    {
        fichePath(path, pop.personstorage[getHash(pop, ances.ancestorsTab[i]->id)]); //Le contenue du path est écrasé à chaque appel
        exportPersonToHTML(pop, pop.personstorage[getHash(pop, ances.ancestorsTab[i]->id)],path, contentAncestors);
    }

    // Libérer la mémoire allouée pour les ancêtres
    free(ances.ancestorsTab);
}

// Implémentation de la fonction qui permet de remplir le contenu pour la page HTML de la recherche de la ville
int contentNbyTown(char* buffer, population pop, int n, char* ville)
{
    // popclone contient toute la pupulation sans gap entre les personnes et trié par ville
    population popclone = findNbyTown(pop);
    
     
     /*---------------- code HTMl -------------------*/
    int offset = sprintf(buffer, "   <h1 class =\"titre-h1\">Ville de %s</h1>\n", ville);
    offset += sprintf(buffer + offset, "   <div class=\"ville-container\">\n");

    int count = 0;
    int i = 0;
    while( i < popclone.size)
    {
        //printf("%d  - %s, %d\n",i, popclone.personstorage[i]->birthzipcode, popclone.personstorage[i]->id);
        if (strcmp(ville, popclone.personstorage[i]->birthzipcode) == 0)
        {
            while (strcmp(ville, popclone.personstorage[i]->birthzipcode) == 0)
            {
                Person* personne = popclone.personstorage[i];

                offset += sprintf(buffer + offset, "        <div class=\"sibling rectangle\">\n");
                offset += sprintf(buffer + offset, "            <h2>%s, %s</h2>\n", personne->firstname, personne->lastname);
                offset += sprintf(buffer + offset, "            <p> %02d/%02d/%04d </p>\n", personne->birthday, personne->birthmonth, personne->birthyear);
                offset += sprintf(buffer + offset, "        </div>\n");

                //printf("%d, %s, %s\n",popclone.personstorage[i]->id, popclone.personstorage[i]->lastname, popclone.personstorage[i]->firstname);
                count++;
                if (count == n) break;
                i++;
            }  
        }
        if (count == n) break;
        i++; 
    }
    if (!count)
    {
        offset += sprintf(buffer + offset, "        <p>%s n'existe pas !</p>\n",ville);
    }
    offset += sprintf(buffer + offset, "   </div>\n");

    freePersons(popclone.personstorage, popclone.capacity);
    return offset;

}