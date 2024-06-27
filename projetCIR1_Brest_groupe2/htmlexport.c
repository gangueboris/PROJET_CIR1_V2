#include "person.h"
#include "filemanager.h"
#include "htmlexport.h"

int titreHTMLPerson(char *buffer, person *p) {// Fonction qui écrit dans un buffer le deuxième titre de la page
    int written = sprintf(buffer, "<h2>%s, %s</h2>", p->firstname, p->lastname); // écriture du titre nom, prénom
    return written;
}

int fichePath(char *buffer, person *p ,int choix) {// Fonction qui écrit dans un buffer le chemin d'accès du fichier
    int written;
    if (choix==0){
        written = sprintf(buffer, "export/%d-info.html", p->id); // écriture du nom de la fiche cas information
    }
    if (choix==1){
        written = sprintf(buffer, "export/%d-arbre.html", p->id); // écriture du nom de la fiche cas arbre
    }
    if (choix==2){
        written = sprintf(buffer, "export/%d-fratrie.html", p->id); // écriture du nom de la fiche cas fratrie
    }
    return written;
}

void exportPersonToHTML(population *t, person *p, char *path, int choix){ // Fonction qui exporte la page html en fonction de l'option choisie
    FILE *file = fopen(path, "w"); // ouverture et vérification du fichier
    if (file == NULL) {
        perror("Erreur à l'ouverture du fichier");
        return;
    }

    fprintf(file, "<!DOCTYPE html>\n");
    fprintf(file, "<html lang=\"fr\">\n");
    fprintf(file, "<head>\n");
    fprintf(file, "    <meta charset=\"UTF-8\">\n");
    fprintf(file, "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n");
    fprintf(file, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n");
    fprintf(file, "    <title>Fiche de %s %s</title>\n", p->firstname, p->lastname);
    fprintf(file, "    <link rel=\"stylesheet\" href=\"assets/arbre.css\">\n");
    fprintf(file, "    <style>@import url('https://fonts.googleapis.com/css2?family=Dancing+Script:wght@400..700&display=swap');</style>\n");
    fprintf(file, "</head>\n");
    fprintf(file, "<body>\n");
    if (choix==0){
        fprintf(file, "    <h1>Informations</h1>\n");
    }
    if (choix==1){
        fprintf(file, "    <h1>My Family Tree</h1>\n");
    }
    if (choix==2){
        fprintf(file, "    <h1>My Brotherhood</h1>\n");
    }

    char buffer[255]; // buffer du titre
    titreHTMLPerson(buffer, p); // écriture du titre
    fprintf(file, "    %s\n", buffer); // écriture du titre dans le fichier

    char treeBuffer[2048]; // buffer de l'arbre ou de la fratrie ou de la fiche
    if (choix==0){
        printInformationToHtml(treeBuffer, p); // écriture des informations de la personne choisie
    }
    if (choix==1){
        printAncestorsToHTML(treeBuffer, t, p); // écriture de la partie de l'arbre dans le buffer
    }
    if (choix==2){
        printBrotherhoodToHtml(treeBuffer, t, p); // écriture de la partie de la fratrie dans le buffer
    }

    fprintf(file, "%s\n", treeBuffer); // écriture du buffer dans le fichier

    fprintf(file, "</body>\n");
    fprintf(file, "</html>\n");

    // Ferme le fichier
    fclose(file);
}

int printAncestorsToHTML(char *buffer, population *t, person *p) { // Fonction qui écrit l'arbre des ancêtres dans un buffer
    person **ancestors = ancestorsPersons(t, p); // calcul des ancêtres de la personne "p"
    int written = 0; // initialisation de l'entier pour le buffer
    int choix =1; // choix à 1 car on veut l'arbre de tout le monde

    written += sprintf(buffer + written, "  <div class=\"layout\">\n");

    // Section enfant
    written += sprintf(buffer + written, "      <div id=\"enfant\">\n");
    written += sprintf(buffer + written, "          <img src=\"assets/profil.png\">\n");
    written += sprintf(buffer + written, "          <p>%s %s</p>\n", p->firstname, p->lastname); // nom prénom
    written += sprintf(buffer + written, "          <p>%02d/%02d/%04d</p>\n", p->birthday, p->birthmonth, p->birthyear); // date de naissance
    written += sprintf(buffer + written, "          <p>%s</p>\n", p->birthzipcode); // lieu de naissance
    written += sprintf(buffer + written, "      </div>\n");

    // Section parents
    written += sprintf(buffer + written, "      <div id=\"parent1\">\n");
    if (ancestors[1]) {
        char fileLink[255];
        fichePath(fileLink, ancestors[1],choix); // écriture de l'emplacement du fichier du parent 1
        if (ancestors[1]->id == 0){ // vérification si la personne est inconnue
            
            written += sprintf(buffer + written, "          <img src=\"assets/profil_vide.png\">\n");
            written += sprintf(buffer + written, "          <p>Inconnu</p>\n");
        }
        else {
            exportPersonToHTML(t,ancestors[1],fileLink,choix);
            written += sprintf(buffer + written, "          <img src=\"assets/profil.png\">\n");
            written += sprintf(buffer + written, "          <p><a href=\"%d-arbre.html\">%s %s</a></p>\n", ancestors[1]->id, ancestors[1]->firstname, ancestors[1]->lastname);
            written += sprintf(buffer + written, "          <p>%02d/%02d/%04d</p>\n", ancestors[1]->birthday, ancestors[1]->birthmonth, ancestors[1]->birthyear);
        }
    }
    written += sprintf(buffer + written, "      </div>\n");

    written += sprintf(buffer + written, "      <div id=\"parent2\">\n");
    if (ancestors[2]) {
        char fileLink[255];
        fichePath(fileLink, ancestors[2],choix); // écriture de l'emplacement du fichier du parent 2
        if (ancestors[2]->id == 0){ // vérification si la personne est inconnue
                written += sprintf(buffer + written, "          <img src=\"assets/profil_vide.png\">\n");
                written += sprintf(buffer + written, "          <p>Inconnu</p>\n");
            }
            else {
                exportPersonToHTML(t,ancestors[2],fileLink,choix);
                written += sprintf(buffer + written, "          <img src=\"assets/profil.png\">\n");
                written += sprintf(buffer + written, "          <p><a href=\"%d-arbre.html\">%s %s</a></p>\n", ancestors[2]->id, ancestors[2]->firstname, ancestors[2]->lastname);
                written += sprintf(buffer + written, "          <p>%02d/%02d/%04d</p>\n", ancestors[2]->birthday, ancestors[2]->birthmonth, ancestors[2]->birthyear);
            }
    }
    written += sprintf(buffer + written, "      </div>\n");

    // Section grands parents
    for (int i = 3; i <= 6; i++) {
        written += sprintf(buffer + written, "      <div id=\"grand_parent%d\">\n", i-2);
        if (ancestors[i]) {
            char fileLink[255];
            fichePath(fileLink, ancestors[i],choix); // écriture de l'emplacement du fichier du grand-parent-i
            if (ancestors[i]->id == 0){ // vérification si la personne est inconnue
                written += sprintf(buffer + written, "          <img src=\"assets/profil_vide.png\">\n");
                written += sprintf(buffer + written, "          <p>Inconnu</p>\n");
            }
            else {
                exportPersonToHTML(t,ancestors[i],fileLink,choix); // créer l'arbre de la personne 
                written += sprintf(buffer + written, "          <img src=\"assets/profil.png\">\n");
                written += sprintf(buffer + written, "          <p><a href=\"%d-arbre.html\">%s %s</a></p>\n", ancestors[i]->id, ancestors[i]->firstname, ancestors[i]->lastname);
                written += sprintf(buffer + written, "          <p>%02d/%02d/%04d</p>\n", ancestors[i]->birthday, ancestors[i]->birthmonth, ancestors[i]->birthyear);
            }
        } 
        written += sprintf(buffer + written, "      </div>\n");
    }

    written += sprintf(buffer + written, "  </div>\n");

    free(ancestors); // libération de la mémoire pour le tableau d'ancêtres
    return written;
}

int printBrotherhoodToHtml(char *buffer, population *t, person *p){ // Fonction qui écrit la fratrie dans un buffer
    int taille;
    int choix=0; // choix pour faire des pages informations
    person **fratrie = trouverFratrie(t, p, &taille); // calcul de la fratrie de la personne "p"
    int written = 0; // initialisation de l'entier pour le buffer
    printf("%d\n",taille);
    written += sprintf(buffer + written, "  <div class=\"layout\">\n");

    // Section enfant
    written += sprintf(buffer + written, "      <div id=\"enfant1\">\n");
    written += sprintf(buffer + written, "          <img src=\"assets/profil.png\">\n");
    written += sprintf(buffer + written, "          <p>%s %s</p>\n", p->firstname, p->lastname);
    written += sprintf(buffer + written, "          <p>%02d/%02d/%04d</p>\n", p->birthday, p->birthmonth, p->birthyear);
    written += sprintf(buffer + written, "          <p>%s</p>\n", p->birthzipcode);
    written += sprintf(buffer + written, "      </div>\n");
    

    // Section fratrie
    for (int i = 0; i < taille; i++) {
        written += sprintf(buffer + written, "        <div id=\"fratrie\">\n");
        if (fratrie[i]) {
            char fileLink[255];
            fichePath(fileLink, fratrie[i],choix);
            if (fratrie[i]->id != 0){
                exportPersonToHTML(t,fratrie[i],fileLink,choix);
                written += sprintf(buffer + written, "            <img src=\"assets/profil.png\">\n");
                written += sprintf(buffer + written, "            <p><a href=\"%d-info.html\">%s %s</a></p>\n",fratrie[i]->id, fratrie[i]->firstname, fratrie[i]->lastname);
                written += sprintf(buffer + written, "            <p>%02d/%02d/%04d</p>\n", fratrie[i]->birthday, fratrie[i]->birthmonth, fratrie[i]->birthyear);
            }
        } 
        written += sprintf(buffer + written, "         </div>\n");
    }
    written += sprintf(buffer + written, "  </div>\n");

    free(fratrie); // libération de la mémoire pour le tableau d'ancêtres
    return written;
}

int printInformationToHtml(char *buffer, person *p){ // Fonction pour afficher les informations d'une personne dans un buffer
    int written = 0; // initialisation de l'entier pour le buffer

    written += sprintf(buffer + written, "  <div class=\"layout\">\n");

    // Section enfant
    written += sprintf(buffer + written, "      <div id=\"enfant\">\n");
    written += sprintf(buffer + written, "          <img src=\"assets/profil.png\">\n");
    written += sprintf(buffer + written, "          <p><strong>%s %s</strong></p>\n", p->firstname, p->lastname);
    written += sprintf(buffer + written, "          <p>Date de naissance : %02d/%02d/%04d</p>\n", p->birthday, p->birthmonth, p->birthyear);
    written += sprintf(buffer + written, "          <p>Lieu de naissance : %s</p>\n", p->birthzipcode);
    written += sprintf(buffer + written, "          <p>Id de la mère : %d</p>\n", p->p_mother->id);
    written += sprintf(buffer + written, "          <p>Id du père : %d</p>\n", p->p_father->id);
    written += sprintf(buffer + written, "          <p>Nom de la mère : %s %s</p>\n", p->p_mother->firstname, p->p_mother->lastname);
    written += sprintf(buffer + written, "          <p>Nom du père : %s %s</p>\n", p->p_father->firstname, p->p_father->lastname);
    written += sprintf(buffer + written, "      </div>\n");
    written += sprintf(buffer + written, "  </div>\n");
    return written;
}