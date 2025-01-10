# Project simple shell

[![Typing SVG](https://readme-typing-svg.herokuapp.com?font=Fira+Code&pause=1000&width=435&lines=AUTEURS+++%3A+Wilfried+Panol+Gu%C3%A9l%C3%A9+;Kanga+kouakoua+brice;Nomen+Ratsimba)](https://git.io/typing-svg)



Description :
Le projet Simple Shell est un interpréteur de ligne de commande de base conçu pour fonctionner dans un environnement de type UNIX. Il permet aux utilisateurs d'exécuter des commandes simples en les saisissant dans un terminal. Le shell affiche une invite, attend la saisie de l'utilisateur, puis exécute la commande correspondante. Il peut gérer les commandes sans arguments et fournit une gestion des erreurs de base pour les commandes introuvables.

# Simple Shell (hsh) - Interpréteur de commandes UNIX

## Introduction

Le projet **Simple Shell** consiste en la création d'un interpréteur de commandes basique pour les systèmes de type UNIX. Son objectif est d'implémenter les fonctionnalités essentielles d'un shell, tout en respectant les principes fondamentaux du système d'exploitation. Ce projet met l'accent sur la gestion des processus, l'exécution de commandes via des appels système et la manipulation de l'environnement de l'utilisateur.

La conception de ce shell repose sur une approche minimaliste, permettant une exécution directe de commandes sans fonctionnalités avancées comme les pipes, la redirection ou l'exécution en arrière-plan. Il permet néanmoins de comprendre le fonctionnement interne d'un shell à travers l'usage des appels système de bas niveau.

## Fonctionnalités principales

- **Affichage du prompt** : Le shell affiche un prompt interactif indiquant qu'il est prêt à recevoir une commande.
- **Exécution de commandes simples** : Il peut exécuter une commande simple sans arguments, en affichant un message d'erreur si la commande est introuvable.
- **Mode interactif et non interactif** : Il fonctionne en mode interactif (en attente de l'entrée de l'utilisateur) ou en mode non interactif (exécution de commandes à partir d'un fichier ou d'un pipe).
- **Gestion des erreurs** : Le shell gère les erreurs courantes, telles que l'absence de fichier ou de commande.
- **Commandes intégrées** : Implémentation de commandes de base telles que `exit` pour quitter le shell et `env` pour afficher les variables d'environnement.

## Compilation

Le projet est conçu pour être compilé sur un système Ubuntu 20.04 LTS à l'aide de `gcc`. Les fichiers source doivent être compilés avec les options suivantes :

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Cette commande génère un exécutable appelé hshqui peut être exécuté à partir du terminal

Utilisation
Une fois l'exécutable compilé, vous pouvez démarrer le shell en mode interactif avec la commande suivante :

frapper

Copier le code
./hsh
En mode interactif, le shell attend les entrées de l'utilisateur et affiche une invite (par défaut ($)).

Exemples
Mode interactif
frapper

Copier le code
$ ./hsh
($) /bin/ls
main.c  shell.c  prompt.c
($) exit
Mode non interactif
frapper

Copier le code
$ echo "/bin/ls" | ./hsh
main.c  shell.c  prompt.c
Détails techniques
Exécution des commandes : Le shell utilise le système d'appel execvepour exécuter les commandes. Lorsqu'une commande est donnée, le shell cherche son exécutable dans les répertoires définis par la variable d'environnement PATH.
Gestion des processus : Les commandes sont exécutées dans des processus enfants créés par l'appel système fork. Le shell attend ensuite la fin du processus enfant via wait.
Manipulation de l'environnement : Le shell peut afficher l'environnement courant de l'utilisateur à l'aide de la commande intégrée env.
Limites
Ce shell ne supporte pas encore certaines fonctionnalités avancées comme la gestion des tuyaux, des redirections ou l'exécution en arrière-plan. De plus, il ne prend en charge que des commandes sans arguments ou avec un nombre limité d'arguments.

<a href="https://zupimages.net/viewer.php?id=25/02/792p.png"><img src="https://zupimages.net/up/25/02/792p.png" alt="" /></a>
