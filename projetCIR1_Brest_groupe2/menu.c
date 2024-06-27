#include "person.h"
#include "filemanager.h"
#include "htmlexport.h"
#include "menu.h"

int menuRecherche() { // Fonction pour afficher le menu de recherche
    int reponse;
    printf("------------------------------------------------------------\n");
    printf("1. Rechercher par ID\n");
    printf("2. Rechercher par nom\n");
    printf("3. Rechercher par prénom\n");
    printf("4. Rechercher par nom et prénom\n");
    printf("5. Rechercher par lieu de naissance\n");
    printf("6. Rechercher par date de naissance\n");
    printf("7. Rechercher par année\n");
    printf("8. Revenir au menu principal\n");
    printf("------------------------------------------------------------\n");
    printf("Votre choix : ");
    scanf(" %d", &reponse);
    getchar();  // supression de la nouvelle ligne lors du scanf
    return reponse;
}

void majPremierelettre(char *str) { // Mettre la première lettre en majuscule si ce n'est pas le cas
    if (str[0] != '\0' && str[0] >= 'a' && str[0] <= 'z') {
        str[0] = str[0] - ('a' - 'A');
    }
}

person* choisirPersonne(person** resultats, int taille) { // Fonction pour afficher les résultats de recherche et choisir une personne
    if (taille == 0) {
        printf("Aucun résultat trouvé.\n");
        return NULL;
    }

    for (int i = 0; i < taille; i++) {
        printf("%d. %s %s, né le %02d/%02d/%04d\n", i + 1, resultats[i]->firstname, resultats[i]->lastname, resultats[i]->birthday, resultats[i]->birthmonth, resultats[i]->birthyear);
    }

    int choix;
    printf("Choisissez une personne (1-%d) : ", taille);
    scanf("%d", &choix);
    getchar();  // supression de la nouvelle ligne lors du scanf

    if (choix < 1 || choix > taille) {
        printf("Choix invalide.\n");
        return NULL;
    }
    return resultats[choix - 1];
}

void rechercherParNom(population* population, char* nom, person** resultats, int* taille) { // Fonction pour rechercher des personnes par nom
    *taille = 0; // initialisation de la taille de la liste à 0
    for (int i = 0; i < TABLE_SIZE; i++) { // parcours de la table de hachage
        node_person* node = population->table[i];
        while (node != NULL) {
            if (strcmp(node->p->lastname, nom) == 0) { // comparaison entre le nom inscrit et le nom à l'indice i
                if (resultats != NULL) { // cas où on veut uniquement la taille 
                    resultats[*taille] = node->p; // si oui ajout du résultat au tableau 
                }
                (*taille)++; // ajout de 1 à la taille
            }
            node = node->next; // pointeur suivant de la liste chainée (cas de collision)
        }
    }
}

void rechercherParPrenom(population* population, char* prenom, person** resultats, int* taille) { // Fonction pour rechercher des personnes par prénom
    *taille = 0;
    for (int i = 0; i < TABLE_SIZE; i++) { // parcours de la table de hachage
        node_person* node = population->table[i];
        while (node != NULL) {
            if (strcmp(node->p->firstname, prenom) == 0) { // comparaison entre le prénom inscrit et le prénom de l'indice i
                if (resultats != NULL) { // cas où on veut uniquement la taille 
                    resultats[*taille] = node->p; // si oui ajout du résultat au tableau 
                }
                (*taille)++; // ajout de 1 à la taille
            }
            node = node->next; // pointeur suivant de la liste chainée (cas de collision)
        }
    }
}

void rechercherParNomPrenom(population* population, char* nom, char* prenom, person** resultats, int* taille) { // Fonction pour rechercher des personnes par nom et prénom
    *taille = 0; // initialisation de la taille de la liste à 0
    for (int i = 0; i < TABLE_SIZE; i++) { // parcours de la table de hachage
        node_person* node = population->table[i];
        while (node != NULL) {
            if (strcmp(node->p->lastname, nom) == 0 && strcmp(node->p->firstname, prenom) == 0) { // comparaison entre le nom inscrit et le nom de l'indice i et le prénom
                if (resultats != NULL) { // cas où on veut uniquement la taille 
                    resultats[*taille] = node->p; // si oui ajout du résultat au tableau 
                }
                (*taille)++; // ajout de 1 à la taille
            }
            node = node->next; // pointeur suivant de la liste chainée (cas de collision)
        }
    }
}

void rechercherParLieuNaissance(population* population, char* lieu, person** resultats, int* taille) { // Fonction pour rechercher des personnes par lieu de naissance
    *taille = 0; // initialisation de la taille de la liste à 0
    for (int i = 0; i < TABLE_SIZE; i++) { // parcours de la table de hachage
        node_person* node = population->table[i];
        while (node != NULL) {
            if (strcmp(node->p->birthzipcode, lieu) == 0) { // comparaison entre le lieu inscrit et le lieu de l'indice i
                if (resultats != NULL) { // cas où on veut uniquement la taille
                    resultats[*taille] = node->p; // si oui ajout du résultat au tableau 
                }
                (*taille)++; // ajout de 1 à la taille
            }
            node = node->next; // pointeur suivant de la liste chainée (cas de collision)
        }
    }
}

void rechercherParDateNaissance(population* population, int day, int month, int year, person** resultats, int* taille) { // Fonction pour rechercher des personnes par date de naissance
    *taille = 0; // initialisation de la taille de la liste à 0
    for (int i = 0; i < TABLE_SIZE; i++) { // parcours de la table de hachage
        node_person* node = population->table[i];
        while (node != NULL) {
            if (node->p->birthday == day && node->p->birthmonth == month && node->p->birthyear == year) { // comparaison entre la date inscrite et la date de l'indice i
                if (resultats != NULL) { // cas où on veut uniquement la taille 
                    resultats[*taille] = node->p; // si oui ajout du résultat au tableau 
                }
                (*taille)++; // ajout de 1 à la taille
            }
            node = node->next; // pointeur suivant de la liste chainée (cas de collision)
        }
    }
}

void rechercherParAnnee(population* population, int year, person** resultats, int* taille) { // Fonction pour rechercher des personnes par année de naissance
    *taille = 0; // initialisation de la taille de la liste à 0
    for (int i = 0; i < TABLE_SIZE; i++) {
        node_person* node = population->table[i];
        while (node != NULL) {
            if (node->p->birthyear == year) { // comparaison entre la date inscrite et la date de l'indice i
                if (resultats != NULL) { // cas où on veut uniquement la taille 
                    resultats[*taille] = node->p; // si oui ajout du résultat au tableau
                }
                (*taille)++; // ajout de 1 à la taille
            }
            node = node->next; // pointeur suivant de la liste chainée (cas de collision)
        }
    }
}

person* recherchePersonne(population* population) { // Fonction principale de recherche
    while (1) { // Boucle du menu tant qu'aucun choix n'est fait 
        int choix = menuRecherche(); // demande à l'utilisateur son choix
        person* resultats[100]; // déclaration du tableau des résultats possibles lors des recherches
        int taille; // taille de la liste finale à parcourir

        switch (choix) {
            case 1: {
                int id;
                printf("Entrez l'ID de la personne : ");
                scanf(" %d",&id);
                return findPersonne(population,id);
            }
            case 2: {
                char nom[20];
                printf("Entrez le nom de famille : ");
                fgets(nom, sizeof(nom), stdin);
                nom[strcspn(nom, "\n")] = '\0'; // Supprime le \n si présent
                majPremierelettre(nom);
                rechercherParNom(population, nom, resultats, &taille);
                return choisirPersonne(resultats, taille);
            }
            case 3: {
                char prenom[20];
                printf("Entrez le prénom : ");
                fgets(prenom, sizeof(prenom), stdin);
                prenom[strcspn(prenom, "\n")] = '\0'; // Supprime le \n si présent
                majPremierelettre(prenom);
                rechercherParPrenom(population, prenom, resultats, &taille);
                return choisirPersonne(resultats, taille);
            }
            case 4: {
                char nom[20], prenom[20];
                printf("Entrez le prénom : ");
                fgets(prenom, sizeof(prenom), stdin);
                prenom[strcspn(prenom, "\n")] = '\0'; // Supprime le \n si présent
                printf("Entrez le nom de famille : ");
                fgets(nom, sizeof(nom), stdin);
                majPremierelettre(nom);
                majPremierelettre(prenom);
                nom[strcspn(nom, "\n")] = '\0'; // Supprime le \n si présent
                rechercherParNomPrenom(population, nom, prenom, resultats, &taille);
                return choisirPersonne(resultats, taille);
            }
            case 5: {
                char lieu[30];
                printf("Entrez le lieu de naissance : ");
                fgets(lieu, sizeof(lieu), stdin);
                lieu[strcspn(lieu, "\n")] = '\0'; // Supprime le \n si présent
                majPremierelettre(lieu);
                rechercherParLieuNaissance(population, lieu, resultats, &taille);
                return choisirPersonne(resultats, taille);
            }
            case 6: {
                int day, month, year;
                printf("Entrez la date de naissance au format JJ/MM/AAAA : ");
                char ligne[11];
                fgets(ligne, sizeof(ligne), stdin);
                ligne[strcspn(ligne, "\n")] = '\0'; // Supprime le \n si présent
                if (sscanf(ligne, "%2d/%2d/%4d", &day, &month, &year) != 3) {
                    printf("Format de date invalide.\n");
                } else {
                    rechercherParDateNaissance(population, day, month, year, resultats, &taille);
                    return choisirPersonne(resultats, taille);
                }
                break;
            }
            case 7: {
                int year_1;
                printf("Entrez l'année de naissance : ");
                scanf(" %d",&year_1);
                rechercherParAnnee(population, year_1, resultats, &taille);
                return choisirPersonne(resultats, taille);
                break;
            }

            case 8:
                return NULL;
            default:
                printf("\n");
                printf("Entrée invalide.\n");
                printf("\n");
                break;
        }
    }
}

void afficherAncetreCommun(population* population) { // Fonction pour rechercher et afficher l'ancêtre commun le plus proche
    printf("Recherche de la première personne.\n");
    person* p1 = recherchePersonne(population); // initialisation de la première personne à comparer
    if (p1 == NULL) return;

    printf("Recherche de la deuxième personne.\n");
    person* p2 = recherchePersonne(population); // initialisation de la deuxième personne à comparer
    if (p2 == NULL) return;

    person* ancestor = findCommonAncestor(p1, p2); // recherche de l'ancêtre commun le plus proche
    char path[255]; // pour le répertoire
    int choix;
    if (ancestor != NULL && ancestor->id != 0) { // vérifie si le résulat renvoyé est un ancêtre connu
        printf("L'ancêtre commun le plus proche de %s %s et %s %s est %s %s\n", p1->firstname, p1->lastname, p2->firstname, p2->lastname, ancestor->firstname, ancestor->lastname);
        printf("Voulez-vous l'arbre généalogique de la personne (1) ou sa fiche info (2) ? (1,2).\n");
        scanf(" %d",&choix);
        switch (choix){
        case 1:
            fichePath(path, ancestor, 1); // Génération du chemin du fichier
            exportPersonToHTML(population, ancestor, path, 1); // export l'arbre généalogique de la personne
            break;
        case 2:
            fichePath(path, ancestor, 1); // Génération du chemin du fichier
            exportPersonToHTML(population, ancestor, path, 1); // export les informations de la personne
            break;
        default:
            printf("Entrée invalide.\n");
            break;
        }
        printf("\n");
        printf("Fichier de %d généré.\nOuvrez le fichier : %s\n", ancestor->id, path);
        printf("\n");
    } else {
        printf("\n");
        printf("Aucun ancêtre commun trouvé.\n");
        printf("\n");
    }
}

void menu(population *population) { // Fonction menu qui s'occupe d'appeler toutes les autres fonctions en fonction du choix de l'utilisateur
    int choix_principal = 0;
    char path[255];

    while (1) {
        printf("Que voulez-vous faire ?\n");
        printf("------------------------------------------------------------\n");
        printf("1. Montrer l'arbre généalogique d'un individu\n");
        printf("2. Afficher la fratrie d'un individu\n");
        printf("3. Montrer les informations d'un individu\n");
        printf("4. Afficher l'ancêtre commun le plus proche\n");
        printf("5. Afficher le nombre de personnes nées dans la même ville\n");
        printf("6. Afficher le nombre de personnes ayant le même prénom\n");
        printf("7. Afficher le nombre de personnes ayant le même nom\n");
        printf("8. Afficher le nombre de personnes ayant le même nom et prénom\n");
        printf("9. Afficher le nombre de personnes ayant la même date de naissance\n");
        printf("10. Afficher le nombre de personnes ayant la même année de naissance\n");
        printf("11. Ne rien faire\n");
        printf("------------------------------------------------------------\n");
        printf("Votre choix : ");
        scanf("%d", &choix_principal);
        getchar(); 

        switch (choix_principal) {
            case 1:
                person *p_a = recherchePersonne(population);
                if (p_a!=NULL){
                    fichePath(path, p_a, 1); // Génération du chemin du fichier
                    exportPersonToHTML(population, p_a, path, 1);
                    printf("\n");
                    printf("Fichier arbre de %d généré.\nOuvrez le fichier : %s\n", p_a->id, path);
                    printf("\n");
                }
                else{
                    printf("\n");
                    printf("Personne introuvable.\n");
                    printf("\n");
                }
                break;

            case 2:
                person *p_f=recherchePersonne(population);
                if (p_f!=NULL){
                    fichePath(path, p_f, 2); // Génération du chemin du fichier
                    exportPersonToHTML(population, p_f, path, 2);
                    printf("\n");
                    printf("Fichier fratrie de %d généré.\nOuvrez le fichier : %s\n", p_f->id, path);
                    printf("\n");
                }
                else{
                    printf("\n");
                    printf("Personne introuvable.\n");
                    printf("\n");
                }
                break;

            case 3: 
                person *p_i=recherchePersonne(population);
                if (p_i!=NULL){
                    fichePath(path, p_i, 0); // Génération du chemin du fichier
                    exportPersonToHTML(population, p_i, path, 0);
                    printf("\n");
                    printf("Fichier informations de %d généré.\nOuvrez le fichier : %s\n", p_i->id, path);
                    printf("\n");
                }
                else{
                    printf("\n");
                    printf("Personne introuvable.\n");
                    printf("\n");
                }
                break;
                
            case 4:
                afficherAncetreCommun(population);
                break;
            
            case 5:
                int taille_l;
                char lieu[30];
                printf("Entrez le lieu de naissance : ");
                fgets(lieu, sizeof(lieu), stdin);
                lieu[strcspn(lieu, "\n")] = '\0'; // Supprime le \n si présent
                majPremierelettre(lieu);
                rechercherParLieuNaissance(population, lieu, NULL, &taille_l);
                printf("\n");
                printf("Voici le nombre de personnes nées à %s : %d\n",lieu,taille_l);
                printf("\n");
                break;
            case 6:
                int taille_p;
                char prenom[30];
                printf("Entrez le prénom : ");
                fgets(prenom, sizeof(prenom), stdin);
                prenom[strcspn(prenom, "\n")] = '\0'; // Supprime le \n si présent
                majPremierelettre(prenom);
                rechercherParPrenom(population, prenom, NULL, &taille_p);
                printf("\n");
                printf("Voici le nombre de personnes ayant pour prénom %s : %d\n",prenom,taille_p);
                printf("\n");
                break;
            case 7:
                int taille_n;
                char nom[30];
                printf("Entrez le nom : ");
                fgets(nom, sizeof(nom), stdin);
                nom[strcspn(nom, "\n")] = '\0'; // Supprime le \n si présent
                majPremierelettre(nom);
                rechercherParNom(population, nom, NULL, &taille_n);
                printf("\n");
                printf("Voici le nombre de personnes ayant pour nom %s : %d\n",nom,taille_n);
                printf("\n");
                break;
            case 8:
                char nom_r[20], prenom_r[20];
                int taille_np;
                printf("Entrez le prénom : ");
                fgets(prenom_r, sizeof(prenom_r), stdin);
                prenom_r[strcspn(prenom_r, "\n")] = '\0'; // Supprime le \n si présent
                printf("Entrez le nom de famille : ");
                fgets(nom_r, sizeof(nom_r), stdin);
                majPremierelettre(nom_r);
                majPremierelettre(prenom_r);
                nom_r[strcspn(nom, "\n")] = '\0'; // Supprime le \n si présent
                rechercherParNomPrenom(population, nom, prenom, NULL, &taille_np);
                printf("\n");
                printf("Voici le nombre de personnes ayant pour même nom et prénom , %s %s : %d\n", nom_r, prenom_r, taille_n);
                printf("\n");
                break;
            
            case 9:
                int taille_d;
                int day_r, month_r, year_r;
                printf("Entrez la date de naissance au format JJ/MM/AAAA : ");
                char ligne[11];
                fgets(ligne, sizeof(ligne), stdin);
                ligne[strcspn(ligne, "\n")] = '\0'; // Supprime le \n si présent
                if (sscanf(ligne, "%2d/%2d/%4d", &day_r, &month_r, &year_r) != 3) {
                    printf("Format de date invalide.\n");
                } else {
                    rechercherParDateNaissance(population, day_r, month_r, year_r, NULL, &taille_d);
                    printf("\n");
                    printf("Voici le nombre de personnes nées le %02d/%02d/%04d : %d\n",day_r, month_r, year_r, taille_d);
                    printf("\n");
                }
                break;
                
            case 10:
                int year_a;
                int taille_a;
                printf("Entrez l'année de naissance : ");
                scanf(" %d",&year_a);
                rechercherParAnnee(population, year_a, NULL, &taille_a);
                printf("\n");
                printf("Voici le nombre de personnes nées en %d : %d\n",year_a, taille_a);
                printf("\n");
                break;
            case 11:
                printf("\n");
                printf("Au revoir.\n");
                return;

            default:
                printf("\n");
                printf("Entrée invalide.\n");
                printf("\n");
                break;
        }
    }
}