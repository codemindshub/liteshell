#include "litshell.c"
/**
 * tokenize - function returns an array of string based on given delimiter
 *
 * @str: string to be tokenized
 * @delim: delimiter seperating the substrings
 *
 * Return: An array of strings
 */
char **tokenize(const char *str, const char *delim)
{
	static char *array_token[1024]; /* Declare an array to store substrings */
	int x = 0; /* Index of array of strings */
	char *temp_str; /* Save str in temp_str */ 

	if (str != NULL)
	{
		temp_str = strdup(str); /* if str not null assign value to temp_str */
	}

	if (delim == NULL)
	{
		delim = " \t"; /* If delim is NULL assume space and tabs as delim */
	}
	char *token = strtok(temp_str, delim); /* Store first token */

	while (token != NULL)
	{
		array_token[x] = token; /* Store first token in index 0 of array */
		token = strtok(NULL, delim);
		x++; /* Increment index of array of string */
	}
	return (array_token);
}
