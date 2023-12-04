#include "liteshell.h"

/**
  * createNode - Auxilliary Function
  * Description: This function creates an alias node and populates the members
  * with the key and value params
  * @key: key to be assigned a value
  * @value: value assigned to a key
  * Return: (alias_node *) node on Success, NULL on Failure
  */

alias_node *createNode(const char *key, const char *value)
{
	alias_node *node;

	node = (alias_t *) malloc(sizeof(alias_t));
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

/**
  * addAlias - Auxilliary Function
  * Description: This function creates a node and adds the newNode to the alias
  * linked list.
  * @aliasList: pointer to alias_t custom type (points to the list)
  * @key: key to be assigned a value
  * @value: value assigned to a key
  * Return: Nothing
  */

void addAlias(alias_t *aliasList, const char *key, const char *value)
{
	alias_node *newNode;

	newNode = createNode(key, value);
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
  * Description: Finds a key that matches key param in the list, and returns the
  * corresponding value.
  * @aliasList: pointer to linked list
  * @key: key entry to be matched
  * Return: (char *) current->value on Success, NULL on Failure
  */

char *findAlias(alias_t *aliasList, const char *key)
{
	alias_node *current;

	current = aliasList->head;
	while (current)
	{
		if (current->key == key)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
