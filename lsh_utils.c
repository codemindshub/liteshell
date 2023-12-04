#include "liteshell.h"

/**
 * lsh_init - initializes the relevant objects needed for the shell's
 * operation
 *
 * Return: the initialized shell objects
 */
lsh_t *lsh_init(void)
{
	lsh_t *lsh = malloc(sizeof(lsh_t));

	/*
	 * Let's handle memory allocation errors. This could happen if the system
	 * is out of memory to alloccate for a new process, in which case our can't
	 * even start. We will graciously exit with -1
	 */
	if (check_err(lsh, 'm') == -1)
	{
		exit(EXIT_FAILURE);
	}

	lsh->aliases = malloc(sizeof(alias_t));
	if (check_err(lsh->aliases, 'm') == -1)
	{
		exit(EXIT_FAILURE);
	}

	lsh->exit_code = 0;
	lsh->user_input = NULL;
	lsh->aliases->head = NULL;
	lsh->aliases->tail = NULL;
	lsh->aliases->size = 0;

	return (lsh);
}

/**
 * check_err - a mini error checker
 * @ptr: the pointer to check for NULL
 * @ptr_type: the type of data the pointer points
 *
 * Pointer Types: 'l' is used to check for uninitialized lists.
 * 'm' checks for memory alllocation failures, 'a' is for all other pointer
 * types that needs to checked for NULL
 *
 * Return: 0 if not NULL, -1 otherwise
 */
int check_err(void *ptr, char ptr_type)
{
	if (ptr == NULL)
	{
		if (ptr_type == 'l')
		{
			fprintf(stderr, "The list is not initialized\n");
			return (-1);
		}

		/* let's check for memory allocation errors */
		if (ptr_type == 'm')
		{
			errno = ENOMEM;
			perror("check_err");
			return (-1);
		}

		/* all other NULL pointer checks */
		if (ptr_type == 'a')
		{
			fprintf(stderr, "This is a NULL pointer, don't proceed\n");
			return (-1);
		}
	}

	return (0);
}
