#include "liteshell.h"

/**
  * createNode - Auxilliary Function
  * Description: This function creates an alias node and populates the members
  * with the name and value params
  * @aliasList: pointer to alias list
  * @name: name to be assigned a value
  * @value: value assigned to a name
  * Return: (alias_node *) node on Success, NULL on Failure
  */

alias_node *initAlias(alias_t *aliasList, const char *name, const char *value)
{
	alias_node *node;

	node = (alias_node *) malloc(sizeof(alias_node));
	if (node == NULL)
		return (NULL);
	node->name = (char *) name;
	node->value = (char *) value;
	node->next = NULL;
	aliasList->head = node;
	aliasList->tail = node;
	return (node);
}

/**
  * addAlias - Auxilliary Function
  * Description: This function creates a node and adds the newNode to the alias
  * linked list.
  * @aliasList: pointer to the alias list)
  * @name: name to be assigned a value
  * @value: value assigned to a name
  * Return: (alias_node *) newnode on Success, NULL on Failure
  */

alias_node *addAlias(alias_t *aliasList, const char *name, const char *value)
{
	alias_node *newnode;

	newnode = (alias_node *) malloc(sizeof(alias_node));
	if (newnode == NULL)
		return (NULL);

	newnode->next = NULL;
	newnode->name = (char *) name;
	newnode->value = (char *) value;
	aliasList->tail->next = newnode;
	aliasList->tail = newnode;
	return (newnode);
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
		if (!strcmp(current->name, name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**
  * printAliases - Auxilliary Function
  * Description: This function prints the aliases in an alias list
  * @aliasList: pointer to the alias list
  * Return: Nothing
  */

void printAliases(alias_t *aliasList)
{
	alias_node *current;

	if (aliasList->head)
	{
		current = aliasList->head;
		while (current)
		{
			printf("%s='%s'", current->name, current->value);
			current = current->next;
		}
	}
	else
		return;
}


/**
  * aliasExecutor - Entry Point
  * Description: This function executes the alias command function call
  * sequence
  * @aliasList: pointer to alias list
  * @arguments: tokenized array of strings from user input starting from the
  * first index i.e after the command string
  * Return: Nothing
  */

void aliasExecutor(alias_t *aliasList, char **arguments)
{
	int i = 0;
	char **als, *name, *value;

	while (arguments)
	{
		als = tokenize(arguments[i], "=");
		if (!als) /** could not tokenize arguments[i] */
			exit(1);
		/** alias "name" */
		else if (str_arr_size(als) == 1)
		{
			name = als[0];
			value = findAlias(aliasList, name);
			if (value == NULL)
			{
				dprintf(2, "alias: %s not found\n", value);
				exit(1);
			}
			printf("%s='%s'\n", name, value);
			exit(0);
		}
		/** alias "name=value" */
		else if (str_arr_size(als) == 2)
		{
			name = als[0];
			value = als[1];
			if (!(aliasList->head)) /** empty alias list*/
			{
				/** alias list inits if condition is false */
				if (initAlias(aliasList, name, value) == NULL)
					exit(1);
			}
			if (addAlias(aliasList, name, value) == NULL)
				exit(1);
			exit(0);
		}
	}
	/** alias */
	printAliases(aliasList);
	exit(0);
}
