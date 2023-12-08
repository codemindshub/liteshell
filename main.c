#include "main.h"

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
		exec_env();
	}

	return (0);
}
