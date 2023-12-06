#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - function to execute environment variables
 * @argc: number of arguments
 * @argv: Array of strings containing command-line arguments.
 * @environ: Array of strings representing the environment variables.
 * Return: 0 on success
*/

int main(int argc, char **argv, char **environ) {
    char **env = environ;

    if (argc > 1 && strcmp(argv[1], "invoke_env") == 0) {
		/* Print environment variables */
		while (*env != NULL) {
			printf("%s\n", *env);
			env++;
        }
    } else {
        /* Construct the command without using system, avoiding shell injection */
        char *command[] = {"sh", "-c", "env", NULL};

        // Create a child process
        pid_t pid = fork();

        if (pid == 0) {
			/* This is the child process */
		    execve("/bin/sh", command, environ);
			/* execve only returns if an error occurs */            perror("execve");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
			/* Fork failed */
		    perror("fork");
            exit(EXIT_FAILURE);
        } else {
		/* This is the parent process */
		/* Wait for the child to complete */
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
