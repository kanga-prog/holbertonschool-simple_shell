#ifndef SHELL_H
#define SHELL_H

/* Inclusions des bibliothèques standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>  /* Pour manipuler les répertoires */

/* Définition de constantes */
#define BUFFER_SIZE 1024
#define MAX_HISTORY 50  /* Taille maximale de l'historique */

/* Déclaration des fonctions */

/* Fonction pour exécuter une commande */
void execute_command(char *command);

/* Fonction pour lister les fichiers d'un répertoire */
void list_directory_contents(void);

/* Fonction pour gérer l'entrée de l'utilisateur et l'exécution des commandes */
void handle_input(char *line);

/* Fonction pour ajouter une commande à l'historique */
void add_to_history(const char *line);

/* Fonction pour afficher l'historique des commandes */
void print_history(void);

int main(void);

#endif /* SHELL_H */
