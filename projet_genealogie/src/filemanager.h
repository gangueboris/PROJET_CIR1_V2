#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_
#include "population.h"

void chomp(char *line);

// Définition de la fonction de lecture du fichier csv
population read_csv(const char *filename);
#endif