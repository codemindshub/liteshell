#include "liteshell.h"

/**
  * createNode - Auxilliary Function
  * Description: This function creates an alias node and populates the members
  * with the key and value params
  * @name: name to be assigned a value
  * @value: value assigned to a name
  * Return: (alias_node *) node on Success, NULL on Failure
  */

alias_node *createNode(const char *name, const char *value)
{
	alias_node *node;

	node = (alias_node *) malloc(sizeof(alias_t));
	if (node == NULL)
		return (NULL);
	node->name = (char *) name;
	node->value = (char *) value;
	node->next = NULL;
	return (node);
}

/**
  * addAlias - Auxilliary Function
  * Description: This function creates a node and adds the newNode to the alias
  * linked list.
  * @aliasList: pointer to alias_t custom type (points to the list)
  * @name: name to be assigned a value
  * @value: value assigned to a name
  * Return: Nothing
  */

void addAlias(alias_t *aliasList, const char *name, const char *value)
{
	alias_node *newNode;

	newNode = createNode(name, value);
	if (newNode == NULL)
	{
		dprintf(STDERR_FILENO, "Error creating\n");
		exit(EXIT_FAILURE);
	}

	if (!aliasList || !(aliasList->head))
		aliasList->head = newNode;
	else
	{
		newNode->next = aliasList->head;
		aliasList->head = newNode;
	}
}

/**
  * findAlias - Auxilliary Function
  * Description: Finds a name that matches name param in the list, and returns
  * the corresponding value.
  * @aliasList: pointer to linked list
  * @name: name entry to be matched
  * Return: (char *) current->value on Success, NULL on Failure
  */

char *findAlias(alias_t *aliasList, const char *name)
{
	alias_node *current;

	current = aliasList->head;
	while (current)
	{
		if (current->name == name)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**
  * aliasExecutor - Entry Point
  * Description: This function executes the alias command function call
  * sequence
  * @aliasList: pointer to linked list
  * @arguments: tokenized array of strings from user input starting from the first
  * index i.e after the command string
  * alias command) 
  * Return: Nothing
  */

void aliasExecutor(alias_t *aliasList, char *arguments[])
{
	int i = 0;
	char **als, *name, *value;

	/** char *arguments[] should be passed in as arguments[1:] in the main
	 * shell file. This passes the array starting from the first index
	 */
	while (arguments[i])
	{
		als = tokenize(arguments[i], "=");

		if (str_arr_size(als) == 1)
		{
			name = als[0];
			value = findAlias(aliasList, name);
			if (value == NULL)
			{
				dprintf(STDERR_FILENO, "alias %s not found\n",
						value);
				exit(1);
			}
			printf("alias %s='%s'\n", name, value);
		}
		else if (str_arr_size(als) == 2)
		{
			name = als[0];
			value = als[1];
			addAlias(aliasList, name, value);
		}
		else
		{
			dprintf(STDERR_FILENO, "Unsupported alias format\n");
			exit(EXIT_FAILURE);
		}
	}
}
