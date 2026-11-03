#include "main.h"

/**
 * rev_string - reverses a string in place
 * @s: the string to reverse
 *
 * Return: nothing.
 */
void rev_string(char *s)
{
	int i;
	int len;
	char tmp;

	len = 0;
	while (s[len] != '\0')
		len++;
	for (i = 0; i < len / 2; i++)
	{
		tmp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = tmp;
	}
}
