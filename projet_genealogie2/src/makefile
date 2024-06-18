# Nom de l'exécutable final
TARGET = program

# Fichiers source
SOURCES = advanced.c person.c population.c htmlexport.c main.c 

# Fichiers d'en-tête
HEADERS = advanced.h person.h population.h htmlexport.h 

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c11

# Options d'édition des liens
LDFLAGS =

# Nom des fichiers objets générés
OBJECTS = $(SOURCES:.c=.o)

# Règle par défaut, compile le programme
all: $(TARGET)

# Règle pour l'exécutable final
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Règle pour les fichiers objets
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f ../export/*.html

# Règle pour tout nettoyer
distclean: clean

# Règles de dépendance
-include $(SOURCES:.c=.d)

# Génération des fichiers de dépendance
%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

.PHONY: all clean distclean
