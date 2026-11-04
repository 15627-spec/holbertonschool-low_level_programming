#include "main.h"

/**
 * leet - encodes a string into 1337
 * @s: string to encode
 *
 * Return: pointer to s
 */
char *leet(char *s)
{
	int i = 0;
	int j;
	char *a = "aAeEoOtTlL";
	char *b = "4433007711";

	while (s[i] != '\0')
	{
		j = 0;
		while (a[j] != '\0')
		{
			if (s[i] == a[j])
				s[i] = b[j];
			j++;
		}
		i++;
	}

	return (s);
}
