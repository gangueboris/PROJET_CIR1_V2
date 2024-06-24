# Nom de l'exécutable final
TARGET = program

# Dossier de sortie
OUTPUT_DIR = output

# Fichiers source
SOURCES = advanced.c person.c population.c htmlexport.c filemanager.c main.c 

# Fichiers d'en-tête
HEADERS = advanced.h person.h population.h htmlexport.h filemanager.h

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c11

# Options d'édition des liens
LDFLAGS =

# Nom des fichiers objets générés
OBJECTS = $(addprefix $(OUTPUT_DIR)/, $(SOURCES:.c=.o))

# Règle par défaut, compile le programme
all: $(OUTPUT_DIR) $(OUTPUT_DIR)/$(TARGET)

# Créer le dossier de sortie s'il n'existe pas
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Règle pour l'exécutable final
$(OUTPUT_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Règle pour les fichiers objets
$(OUTPUT_DIR)/%.o: %.c $(HEADERS) | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(OUTPUT_DIR)
	rm -f ../export/*.html
	rm -f *.d

# Règle pour tout nettoyer
distclean: clean

# Règles de dépendance
-include $(SOURCES:.c=$(OUTPUT_DIR)/.d)

# Génération des fichiers de dépendance
$(OUTPUT_DIR)/%.d: %.c | $(OUTPUT_DIR)
	$(CC) -MM $(CFLAGS) $< > $@

.PHONY: all clean distclean
