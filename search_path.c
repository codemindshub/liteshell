#include "liteshell.h"
/**
* search_path - 
*
*/
int search_path(lsh_t *lsh)
{
	char *full_path = NULL; /*Will hold all the directories in PATH seperated by colons*/
	char *command_and_path = NULL;
	char *delimiter = ":";
	char *temp = NULL;

	/*if the command and path given by the user is executable do not search in path. (Eg. A C program they wrote themselves)*/
	if(access(*(lsh->commands), X_OK) == 0)
	{
		lsh->exit_code = EXIT_SUCCESS;
		exit(EXIT_SUCCESS);
	}

	/*copy PATH from getenv function */
	full_path = strdup(getenv("PATH"));
	if (full_path == NULL)
	{
		perror("PATH variable not availerble");
		lsh->exit_code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	/*tokenize PATH so each of the directories is a seperate string*/
	temp = strtok(full_path, delimiter);
	while(temp != NULL)
	{	/*concat '/command_name' to each directory and check if the command exists*/
		command_and_path = malloc(sizeof(temp) + sizeof(*(lsh->commands)));
		strcpy(command_and_path, temp);
		strcat(command_and_path, "/");
		strcat(command_and_path, *(lsh->commands));

		if (access(command_and_path, X_OK) == 0)
		{	/*if command exists change name to full command path name and return*/
			lsh->exit_code = EXIT_SUCCESS;
			*(lsh->commands) = command_and_path;
			free(full_path);
			return(0);
		}
		/*if command does not exist check next directoy in PATH*/
		temp = strtok(NULL, delimiter);
		free(command_and_path);
	}
	free(full_path);
	free(command_and_path);
	lsh->exit_code = EXIT_FAILURE;
	return(1);
}