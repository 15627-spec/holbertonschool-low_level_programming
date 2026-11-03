#include "main.h"

/**
 * puts2 - prints one character out of two, starting with the first
 * @str: the string to print
 *
 * Return: nothing.
 */
void puts2(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (i % 2 == 0)
			_putchar(str[i]);
	}
	_putchar('\n');
}
