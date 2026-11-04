#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @str: string to modify
 *
 * Return: pointer to str
 */
char *cap_string(char *str)
{
	int i = 0;
	int j;
	int new_word = 1;
	char sep[] = " \t\n,;.!?\"(){}";

	while (str[i] != '\0')
	{
		if (new_word && str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		new_word = 0;
		j = 0;
		while (sep[j] != '\0')
		{
			if (str[i] == sep[j])
				new_word = 1;
			j++;
		}
		i++;
	}

	return (str);
}
