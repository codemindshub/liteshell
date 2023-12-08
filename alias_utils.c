#include "liteshell.h"

/**
  * printAliasList - Auxilliary Function
  *
  * Description: This function prints an alias linked list
  *
  * @aliasList: pointer to linked list
  *
  * Return: 0 on Success, 1 on Failure
  */

int printAliasList(alias_t *aliasList)
{
	alias_node *currAlias;

	if (!aliasList)
		return (0);

	currAlias = aliasList->head;

	while (currAlias)
	{
		printf("%s='%s'\n", currAlias->name, currAlias->value);
		currAlias = currAlias->next;
	}
	return (0);
}

/**
  * freeAlias - Auxilliary Function
  *
  * Description: This function frees an alias node
  *
  * @node: node to be freed
  *
  * Return: Nothing
  */

void freeAlias(alias_node *node)
{
	free(node->name);
	free(node->value);
	free(node);
	node = NULL;
}

/**
  * freeAliasList - Auxilliary Function
  *
  * Description: This function frees an aliasList
  *
  * @aliasList: pointer to the aliasList
  *
  * Return: Nothing
  */

void freeAliasList(alias_t *aliasList)
{
	alias_node *currAlias, *nextAlias;

	currAlias = aliasList->head;

	while (currAlias)
	{
		nextAlias = currAlias->next;
		freeAlias(currAlias);
		currAlias = nextAlias;
	}
	free(aliasList);
}

/**
  * freeTokens - Auxilliary Function
  *
  * Description: This function frees an array of tokens
  *
  * @tokens: array of tokens
  *
  * Return: Nothing
  */

void freeTokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i]; ++i)
		free(tokens[i]);

	free(tokens);
}
