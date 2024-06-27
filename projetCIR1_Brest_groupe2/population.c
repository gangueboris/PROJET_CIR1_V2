#include "person.h"
#include "filemanager.h"
#include "htmlexport.h"

int hash(int id){ // Fonction de Hash
    return id % TABLE_SIZE; // calcul de la clé de hachage
}

void initpopulation(population* ht) { // Initialisation du tableau population à null pour chaque case
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

void linkPopulation(population* ht) { // Fonction qui s'occupe de lier les enfants avec les parents
    for (int i = 0; i < TABLE_SIZE; i++) { // Parcourir la liste chaînée
        node_person* node = ht->table[i];
        while (node != NULL) { // Parcourir la liste chaînée
            person* p = node->p;
            if (p->father_id != 0) {
                p->p_father = findPersonne(ht, p->father_id);
            }
            if (p->mother_id != 0) {
                p->p_mother = findPersonne(ht, p->mother_id);
            }
            if (p->father_id == 0) {
                p->p_father = findPersonne(ht, 0); // Liaison avec l'inconnu si l'indice est 0
            }
            if (p->mother_id == 0) {
                p->p_mother = findPersonne(ht, 0);
            }
            node = node->next; // passer à la personne suivante dans la liste chaînée
        }
    }
}