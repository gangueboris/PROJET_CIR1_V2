#include "person.h"
#include "filemanager.h"
#include "htmlexport.h"

person* initPerson(char *csvline) { // Fonction qui initialise la personne avec les informations d'une ligne du csv
    person* p = (person*)malloc(sizeof(person));// Allocation de la mémoire
    if (!p) {// Vérification
        perror("erreur d'allocation mémoire");
        return NULL;
    }

    p->p_father = NULL; // Pointeur vers père et mère mis à NULL, seront liées plus tard
    p->p_mother = NULL;

    char date_naissance[11];
    //Ecriture des information dans le strcut à partir de la csvline
    sscanf(csvline, "%d,%d,%d,%19[^,],%19[^,],%10[^,],%29[^\n]",&p->id, &p->father_id, &p->mother_id, p->lastname, p->firstname, date_naissance, p->birthzipcode);
    sscanf(date_naissance, "%d/%d/%d", &p->birthday, &p->birthmonth, &p->birthyear);

    return p;
}

void insert(population* ht, person* data) {// Fonction qui insère la personne dans la table de hachage
    int key = hash(data->id); // calcul du hash

    node_person* new_node = (node_person*)malloc(sizeof(node_person)); // allocation de la mémoire au new_node
    if (!new_node) {
        perror("erreur d'allocation mémoire pour node_person");
        return;
    }
    new_node->p = data; // attribution de la data
    new_node->next = ht->table[key]; // déplacement du pointeur pour la collision
    ht->table[key] = new_node; // attribution en tête de liste
}

person* findPersonne(population* ht, int id) {// Fonction de recherche par id de complexité O(1)
    int key = hash(id); // calcul du hash
    node_person* current = ht->table[key]; // attribution de la personne courante
    while (current != NULL) { // parcours de la liste chaînée
        if (current->p->id == id) {
            return current->p;//renvoie la personne voulue
        }
        current = current->next; // pointeur suivant
    }
    return NULL;
}

person** trouverFratrie(population* ht, person *p, int* tailleFratrie) { // Fonction qui renvoie un tableau de la fratrie de la personne et sa taille
    if (p == NULL || (p->father_id && p->mother_id) == 0) { // cas où l'individu cherché n'existe pas ou que ses deux parents sont inconnus
        *tailleFratrie = 0; // renvoie la taille de la fratrie à 0
        return NULL;
    }

    int father_id = p->father_id; // récupère l'id du père et de la mère
    int mother_id = p->mother_id;
    int id = p->id;

    person** fratrie = (person**)malloc(TABLE_SIZE * sizeof(person*)); // création du tableau de la fratrie
    int taille = 0;

    for (int i = 0; i < TABLE_SIZE; i++) { // parcours de la population
        node_person* node = ht->table[i]; // personne choisie en fonction de l'indice i
        while (node != NULL) {
            if (node->p->father_id == father_id && node->p->mother_id == mother_id && node->p->id != id) { // condition pour que l'individu p soit un frère/soeur de l'individu trouvé
                fratrie[taille++] = node->p; // l'individu qui correspond aux conditions est ajouté au tableau 
            }
            node = node->next; // pointeur suivant de la liste chaînée (cas de collision)
        }
    }

    *tailleFratrie = taille; // retourne la taille de la fratrie
    return fratrie; // retourne le tableau de la fratrie
}

person** ancestorsPersons(population* ht, person* p) { // Fonction qui renvoie un tableau de l'arbre généalogique de la personne et sa taille
    int maxAncestors = 7; // Maximum pour 3 niveaux (peut être modifié afin de le rentrer en paramètre pour créer un arbre plus grand si besoin mais ne correspond pas avec le html)
    person** ancestors = (person**)malloc(maxAncestors * sizeof(person*)); // création du tableau des ancêtres
    for (int i = 0; i < maxAncestors; i++) { // initialisation du tableau à NULL
        ancestors[i] = NULL;
    }

    ancestors[0] = p; // La première case est l'individu

    for (int i = 0; i < maxAncestors; i++) {
        if (ancestors[i] != NULL) { // Si la personne à l'indice i existe
            if (2 * i + 1 < maxAncestors && ancestors[i]->p_father != NULL) { // Vérifie si l'indice 2*i+1 est dans les limites
                ancestors[2 * i + 1] = ancestors[i]->p_father; // Attribue le père
            }
            if (2 * i + 2 < maxAncestors && ancestors[i]->p_mother != NULL) { // Vérifie si l'indice 2*i+2 est dans les limites
                ancestors[2 * i + 2] = ancestors[i]->p_mother; // Attribue la mère
            }
        }
    }
    return ancestors;
}

void Ancestors(person *p, person **ancestors, int *size) { // Fonction pour récupérer les ancêtres d'une personne en fonction de MAX_GENERATIONS
    if (p == NULL || *size >= MAX_GENERATIONS) return; // vérification si la personne n'est pas null et que size n'est pas plus grand que MAX_GENERATIONS

    ancestors[*size] = p; // ajout des ancêtres dans le tableau
    (*size)++; // ajout de 1 à la taille

    Ancestors(p->p_father, ancestors, size); // fonction récursive pour trouver tous les ancêtres du coté père et mère
    Ancestors(p->p_mother, ancestors, size);
}

person *findCommonAncestor(person *p1, person *p2) { // Fonction pour trouver l'ancêtre commun le plus proche entre deux personnes
    person *ancestors1[MAX_GENERATIONS] = {NULL}; // initialisation des tableaux à NULL
    person *ancestors2[MAX_GENERATIONS] = {NULL};

    int size1 = 0, size2 = 0; // initialise l'indice des tailles à 0 

    Ancestors(p1, ancestors1, &size1); // fonction récursive pour p1 et p2
    Ancestors(p2, ancestors2, &size2);

    for (int i = 0; i < size1; i++) { // parcours de la liste des deux personnes pour trouver un ancêtre commun le plus proche entre les deux
        for (int j = 0; j < size2; j++) {
            if (ancestors1[i] == ancestors2[j]) {
                return ancestors1[i]; // renvoie l'ancêtre commun le plus proche
            }
        }
    }
    return NULL;
}