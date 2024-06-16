### Le programme C

Module 1 (Structure):
 - Structuration de l'information en ajoutant des fonctions
 . ``Person* initPerson(char *csvline)``: Cette fonction prend en paramêtre une ligne du fichier csv, décompose chaque élément et initialise la structure `Person` que l'on retourne.
Cette fonction utilise une fonction de la bibliothèque 'string.h', strtok() qui nous permet de diviser la ligne du csv en une série de sous-chaînes basés sur un ensemble de délimiteurs. 

. Afin de stocker la population, nous avons décidé de définir la structure de cette manière: ``typedef struct population {
                                                                                                                int size;
                                                                                                                int capacity;
                                                                                                                Person** popDatas;
                                                                                                            }population;
                                                                                              ``
la variable *size* nous permet de tracker le nombre actuelle des éléments dans la structure de données choisi pour plutard savoir quand réallouer la mémoire au cas où notre structure de données serait pleine.
La structure de données choisi pour stocker nos données est un *hashMap* afin d'être capable de retrouver n'importe quelle personne dans la population avec une complexité temps plus ou moins O(1).

Module 2 (Lecture):
- Lecture et remplisage des structures de données du fichier

Module 3 (Avancé):
- implémentation des fonctions capables d'effectuer des traitements de haut niveau sur les données

Module 4 (Export):
- implementation des fonctions qui permettent d'exporter les données sous forme de fichier HTML

Module 5 (Menu):
- implementation d'une interface user pour réponse à des questions sur la génalogie d'une personne.



-freeing
- pop->popDatas, q(queue)[Done], frat.fratrieList,  ances.ancestorsList 