#include "liteshell.h"

/**
  * str_arr_size - Auxilliary Functions
  * Description: This is a function that counts the words in an array of
  * strings.
  * @str_arr: String Array
  * Return: (size_t) count if array is populaated, 0 if array is NULL array
  */

size_t str_arr_size(char **str_arr)
{
	size_t count = 0;

	while (str_arr[count])
		++count;
	return (count);
}
