<a href="https://zupimages.net/viewer.php?id=25/02/4rvj.jpg"><img src="https://zupimages.net/up/25/02/4rvj.jpg" alt="" /></a>
# Simple Shell

## Overview:
simple_shell is a simple Unix shell program built as part of an educational project at Holberton School. The goal of this project is to better understand the workings of shell programs, focusing on parsing commands and interacting with the operating system. This shell program provides basic functionalities, including executing external commands, supporting built-in commands like 'exit' and 'env', and handling input/output redirection.

## Features:
- Interactive and non-interactive mode support.
- Built-in commands:
  - `exit`: Exits the shell.
  - `env`: Prints the current environment variables.
- Executes external programs.
- Input/output redirection support.
- Supports multiple commands via pipes.

## Requirements:
- C programming language (compliant with the C90 standard).
- Linux or any POSIX-compatible system.
- A C compiler such as `gcc`.
## Flowchart : 
<a href="https://zupimages.net/viewer.php?id=25/02/792p.png"><img src="https://zupimages.net/up/25/02/792p.png" alt="" /></a>


## Installation:
To compile and use the shell program, follow these steps:

**Clone the repository:**

    git clone https://github.com/[Your_Username]/simple_shell.git

**Navigate to the project directory:**

    cd /holbeton-simple_shell

**Compile the project:**

    gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell

This command will generate the simple_shell executable. 

**Usage:**

You can run the shell by executing the following command:

$ ./simple_shell

This will start the shell in interactive mode, where you can enter commands and receive output. You can also provide commands via input redirection.

**Example Usage:**

***Start the shell:***

    $ ./simple_shell
    #cisfun$ ls
    AUTHORS    core.457  execute_full_path.c  hsh parse_and_execute.c  shell  shell_0.3
    README.md  core.467   man_1_simple_shell  remove_quotes.c  shell.c  simple_shell.h
    #cisfun$ env
    USER=your_user
    PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
    HOME=/home/your_user
    #cisfun$ exit

Run in non-interactive mode (via file):

    $ echo "ls" | ./simple_shell

**Built-in Commands:**

*exit* : Exits the shell. No arguments are required. 

*env* : Prints the current environment variables.

**Features in Development:**

Command history (persisting commands for later use).

Handling of more built-in commands.

**Authors:**
[![Typing SVG](https://readme-typing-svg.herokuapp.com?font=Fira+Code&pause=1000&width=435&lines=AUTEURS+++%3A+Wilfried+Panol+Gu%C3%A9l%C3%A9+;Kanga+kouakoua+brice;Nomen+Ratsimba)](https://git.io/typing-svg)



[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/shareArticle?url=https%3A%2F%2Fwww.linkedin.com%2Fme%3Ftrk%3Dp_mwlite_feed-secondary_nav&mini=true)
****  
[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/kanga-kouakou-brice-8a787a16a/)

**Acknowledgments:**

This project was developed as part of the curriculum at Holberton School. We acknowledge the support and guidance provided by the school and its staff.

If you encounter any issues or bugs, please feel free to open an issue in the GitHub repository: 

 https://github.com/kanga-prog/simple_shell/issues
