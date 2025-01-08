#ifndef SHELL_H
#define SHELL_H

/* Inclusions des bibliothèques standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

/* Définition de constantes */
#define BUFFER_SIZE 1024
#define MAX_HISTORY 50  /* Taille maximale de l'historique */

/* Déclaration des fonctions */

void execute_command(char *command);

void list_directory_contents(void);

void handle_input(char *line);

void add_to_history(const char *line);

void print_history(void);

int search_in_path(char *command);

void list_directory_contents(void);

int main(void);

#endif /* SHELL_H */
