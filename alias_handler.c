#include "liteshell.h"

/**
  * tokenizeAliasArguments - Tokenizer Function
  *
  * Description: This function tokenizes the argument (string) based on the "="
  * delimeter
  *
  * @argument: String argument to be tokenized
  *
  * Return: (char **) tokens array on Success, EXIT on Failure
  */

char **tokenizeAliasArguments(char *argument)
{
	char **tokens, *equalToSign;
	size_t len_name, len_value;

	tokens = (char **) malloc(sizeof(char *) * 2);
	if (!tokens)
	{
		dprintf(2, "Failed to allocate memory for tokens\n");
		exit(EXIT_FAILURE);
	}
	tokens[0] = NULL;
	tokens[1] = NULL;
	equalToSign = strchr(argument, '=');
	if (equalToSign)
	{
		len_name = equalToSign - argument;
		tokens[0] = (char *) malloc(len_name + 1);
		if (!tokens[0])
		{
			dprintf(2, "Failed to allocate memory for name token\n");
			exit(EXIT_FAILURE);
		}
		strncpy(tokens[0], argument, len_name);
		tokens[0][len_name] = '\0';
		len_value = strlen(equalToSign + 1);
		tokens[1] = (char *) malloc(len_value + 1);
		if (!tokens[1])
		{
			dprintf(2, "Failed to allocate memory for value token\n");
			exit(EXIT_FAILURE);
		}
		strncpy(tokens[1], equalToSign + 1, len_value);
		tokens[1][len_value] = '\0';
	}
	else
	{
		tokens[0] = strdup(argument);
		tokens[1] = NULL;
	}
	return (tokens);
}

/**
  * handleAlias - Socket Function
  *
  * Description: This function acts as an interface between the user of the
  * alias feature and the alias handler functions. An aliasList must have been
  * initialized before using this function.
  *
  * @aliasList: pointer to an alias linked list
  *
  * @arguments: arguments for the alias command
  *
  * Return: 0 on Success, 1 on Failure
  */

int handleAlias(alias_t *aliasList, char **arguments)
{
	int i;
	char *name, *value;

	if (!arguments[0])
		return (printAliasList(aliasList));

	for (i = 0; arguments[i]; ++i)
		handleAliasCommands(aliasList, arguments[i]);
	/** will handle returns */
}

/**
  * handleAliasCommands - Helper Function
  *
  * Description: This function utilizes a tokenizer to separate the alias
  * arguments into an array DS of size 2 containing the name and value pairs.
  * It also calls other auxilliary functions and passes on their return values
  * to handleALias()
  *
  * @aliasList: pointer to the alias linked list
  *
  * @argument: arguments for alias command
  *
  * Return: 0 on Success, 1 on Failure
  */

int handleAliasCommands(alias_t *aliasList, char *argument)
{
	char **aliasTokens, *name, *value;
	alias_node *alias;

	aliasTokens = tokenizeAliasArguments(argument);

	name = aliasTokens[0];
	value = aliasTokens[1];

	if (value == NULL)
	{
		alias = findAlias(aliasList, name);
		return (printAlias(alias, name));
	}
	else
	{
		alias = findAlias(aliasList, name);
		if (alias == NULL)
			return (addAlias(aliasList, name, value));
		free(alias->value);
		alias->value = strdup(value);
	}
	return (0);
}

/**
  * main - Entry Point
  *
  * Description: This is a test suit interface for users of the alias command
  *
  * Return: Always 0 on Success
  */

int main(void)
{
	alias_t *aliasList = NULL;
	/**
	  * Run the strings in this array as arguments to the alias command and
	  * compare with result from sh
	  */
	char *arguments[] = {
		"pot",
		"al=alias",
		"ll=lampholder",
		"lorem=ipsum",
		"al",
		"lorem",
		"al=back-it-up",
		NULL
	};
	/**char *arguments[] = {NULL};*/

	aliasList = initAliasList(aliasList);

	handleAlias(aliasList, arguments);
	printAliasList(aliasList);
	removeAlias(aliasList, "lorem");
	printAliasList(aliasList);

	freeAliasList(aliasList);
	printf("See alias_handler.c ;)\n");

	return (0);
}
