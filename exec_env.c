#include "main.h"

/**
 * exec_env - function to execute environment variables
*/

void exec_env() {
	char *command[] = {"sh", "-c", "env", NULL};
	char **env = environ;

	/* Create a child process */
	pid_t pid = fork();

	if (pid == 0) {
		/* This is the child process */
		execve("/bin/sh", command, env);
		/* execve only returns if an error occurs */
		perror("execve");
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
