#include "simple_shell.h"

/**
 * my_exit - Simule la commande exit dans un shell.
 * @status_code: Code de sortie à retourner lors de la fermeture du shell.
 *
 * Description: Cette fonction arrête l'exécution du programme avec un
 * code de sortie donné. Elle est appelée quand l'utilisateur tape
 * la commande "exit" dans le shell.
 */
void my_exit(int status_code)
{
    exit(status_code);  /* Quitter le programme avec le code de sortie donné */
}
