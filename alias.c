#include "liteshell.h"

/**
  * initAliasList - Initializer Function
  *
  * Description: This function initializes the alias linked list
  *
  * @aliasList: a pointer to already initialized linked list
  *
  * Return: (alias_t *) pointer to initialized aliasList on Success,
  * NULL on Failure
  */

alias_t *initAliasList(alias_t *aliasList)
{
	if (aliasList != NULL)
		return (aliasList);

	aliasList = (alias_t *) malloc(sizeof(alias_t));
	if (aliasList == NULL)
		return (NULL);

	aliasList->head = NULL;
	aliasList->tail = NULL;
	aliasList->size = 0;
	return (aliasList);
}

/**
  * addAlias - Auxilliary Function
  *
  * Description: This function adds a new alias node to the alias linked list
  *
  * @aliasList: pointer to the alias list
  *
  * @name: name member of alias node to be added
  *
  * @value: value member of alias node to be added
  *
  * Return: 0 on Success, 1 on Failure
  */

int addAlias(alias_t *aliasList, const char *name, const char *value)
{
	alias_node *newAlias;

	newAlias = (alias_node *) malloc(sizeof(alias_node));
	if (newAlias == NULL)
	{
		dprintf(2, "Failed to malloc\n");
		return (1);
	}

	newAlias->name = strdup(name);
	newAlias->value = strdup(value);
	newAlias->next = NULL;

	if (aliasList->head == NULL)
		aliasList->head = newAlias;
	else
		aliasList->tail->next = newAlias;

	aliasList->tail = newAlias;
	aliasList->size++;
	return (0);
}

/**
  * findAlias - Auxilliary Function
  *
  * Description: This function locates a specific alias node in the linked list
  * based on its name
  *
  * @aliasList: pointer to alias list
  *
  * @name: Name of the alias node to be found
  *
  * Return: (alias_node *) pointer to alias node whose name member
  * matches name on Success, NULL on Failure
  */

alias_node *findAlias(alias_t *aliasList, const char *name)
{
	alias_node *currAlias = aliasList->head;

	while (currAlias)
	{
		if (strcmp(currAlias->name, name) == 0)
			return (currAlias);
		currAlias = currAlias->next;
	}
	return (NULL);
}

/**
  * printAlias - Auxilliary Function
  *
  * Description: This is a function that prints the members of an alias node in
  * the aliasList
  *
  * @alias: alias node to be printed
  *
  * @name: name member of the alias node
  *
  * Return: 0 on Success, 1 on Failure
  */

int printAlias(alias_node *alias, const char *name)
{
	if (!alias)
	{
		printf("alias: %s not found\n", name);
		return (1);
	}
	printf("%s='%s'\n", alias->name, alias->value);
	return (0);
}

/**
  * removeAlias - Auxilliary Function
  *
  * Description: This is the function that removes an alias node from an
  * aliasList
  *
  * @aliasList: pointer to the alias list
  *
  * @name: name member of the alias node
  *
  * Return: 0 on Success, 1 on Failurw
  */

int removeAlias(alias_t *aliasList, const char *name)
{
	alias_node *currAlias, *prevAlias;

	if (!aliasList)
		return (1);

	currAlias = aliasList->head;
	prevAlias = NULL;

	while (currAlias)
	{
		if (strcmp(currAlias->name, name) == 0)
		{
			if (prevAlias == NULL)
				aliasList->head = currAlias->next;
			else
				prevAlias->next = currAlias->next;

			freeAlias(currAlias);
			aliasList->size--;
		}
		prevAlias = currAlias;
		currAlias = currAlias->next;
	}
	return (0);
}
