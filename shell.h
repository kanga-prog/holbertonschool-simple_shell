#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>      /* Pour printf, perror, fprintf */
#include <stdlib.h>     /* Pour exit, malloc, free, getenv, strdup */
#include <unistd.h>     /* Pour fork, execve, access, chdir, isatty */
#include <string.h>     /* Pour strtok, strlen, strcmp */
#include <sys/types.h>  /* Pour pid_t */
#include <sys/wait.h>   /* Pour wait, waitpid */
#include <errno.h>      /* Pour la gestion des erreurs, errno */

/* Taille du tampon pour les commandes */
#define BUFFER_SIZE 1024

/**
 * execute_command - Exécute une commande en créant un processus enfant.
 * @command: La commande à exécuter.
 *
 * Description: Cette fonction crée un processus enfant pour exécuter une
 * commande en utilisant execve. Si execve échoue, une erreur est affichée
 * et le processus enfant se termine avec un code de sortie 1.
 */
void execute_command(char *command);

/**
 * handle_input - Gère l'entrée de l'utilisateur et l'exécution des commandes.
 * @line: La ligne de commande à traiter.
 *
 * Description: Cette fonction analyse l'entrée de l'utilisateur. Si la commande
 * est valide, elle est exécutée. Si la commande est "exit", le programme se
 * termine.
 */
void handle_input(char *line);

/**
 * main - Point d'entrée principal du programme shell.
 *
 * Return: Toujours 0.
 *
 * Description: Cette fonction initialise le shell, affiche un prompt, lit
 * l'entrée de l'utilisateur et appelle handle_input pour traiter la commande
 * entrée. Le shell continue à fonctionner en boucle jusqu'à ce que l'utilisateur
 * quitte le programme.
 */
int main(void);

#endif /* SHELL_H */


