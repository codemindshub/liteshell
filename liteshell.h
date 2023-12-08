#ifndef LITESHELL_H
#define LITESHELL_H

/*
 * CodeMinds `liteshell` team project
 *
 * Based on the feature you are implementing, add the function prototypes along
 * with any helper functions you use here. Strive on organizing them based on
 * the usage and purposes. If it already, don't touch it, use it as is. The
 * only time you are allowed to change anything here is when you have raised an
 * issue or planning an update. Changing anything here could cause the other
 * parts of the project that depend on the existing function prototype to
 * break. As a consenting adult, trust is placed in your hands to do what is
 * right for the best of us all.
 */

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* the command tokenizer function */
char **tokenize(const char *str, const char *delim);

/* returns the full path to the command received on the command line */
char *get_cmd_path(const char *command);

/**
 * struct alias_node - a blueprint for alias nodes
 * @name: the name of the alias
 * @value: the command(s) being aliased
 * @next: pointer to the next alias node
 */
typedef struct alias_node
{
	char *name;
	char *value;
	struct alias_node *next;
} alias_node;

/**
 * struct alias_t - a list of aliases
 * @size: size of the aliases list (basically, number of aliases)
 * @head: keeps track of the head node
 * @tail: keeps track of the tail node (helps in faster insertion at the end of
 * the list, achieving an O(1) in terms of time complexity)
 */
typedef struct alias_t
{
	size_t size;
	alias_node *head;
	alias_node *tail;
} alias_t;

/**
 * struct lsh - contains relevant references to objects the shell uses for its
 * functionalities
 *
 * @exit_code: keeps track of the exit codes of each executed program (useful
 * when `echo $?` is received or when the `exit` command is received on the
 * command line without any argument)
 * @cmd_count: increment this value every time you receive user input
 * @user_input: contains the string the user will enter (pass the address when
 * calling the `getline()` function)
 * @shell_name: store the value of `argv[0]` in this variable (this is how use
 * print the name of the shell in error messages that require the name of the
 * shell to present)
 * @commands: contains the list of commands (tokenized input -> string array)
 * @aliases: a list of aliases
 */
typedef struct lsh
{
	int exit_code;
	size_t cmd_count;
	char *user_input;
	char **commands;
	const char *shell_name;
	alias_t *aliases;
} lsh_t;

/* initializes the shell structure */
lsh_t *lsh_init(void);

/* safer way to deallocate memory */
void _free(void **ptr);
#define safe_free(ptr) _free((void **)&(ptr))

/* a function to create an alias node */
alias_t *initAliasList(alias_t *aliasList);

/* a function to add an alias to linked list */
int addAlias(alias_t *aliasList, const char *name, const char *value);

/* a function that returns the value member of an alias node*/
alias_node *findAlias(alias_t *aliasList, const char *name);

/* a function that prints all stored aliases in linked list */
int printAliasList(alias_t *aliasList);

/* a function to an alias node */
int printAlias(alias_node *alias, const char *name);

/* entry point function to handle single or multiple alias arguments */
int handleAlias(alias_t *aliasList, char **arguments);

/* a function that handles each alias argument */
int handleAliasCommands(alias_t *aliasList, char *argument);
/* a function to remove an alias node - unalias */
int removeAlias(alias_t *aliasList, const char *name);

/* a function to free an alias node */
void freeAlias(alias_node *node);

/* a function to free an alias list */
void freeAliasList(alias_t *aliasList);

/* a function to free tokens */
void freeTokens(char **tokens);

/* implements basic error checking for NULL pointers */
int check_err(void *ptr, char ptr_type);

/* environment variables */
extern char **environ;

#endif /* LITESHELL_H */
