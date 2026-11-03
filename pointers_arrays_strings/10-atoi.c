#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: the string
 *
 * Return: the integer, or 0 if there are no digits.
 */
int _atoi(char *s)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		if (s[i] == '-')
			sign = -sign;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (sign == 1)
			result = result * 10 + (s[i] - '0');
		else
			result = result * 10 - (s[i] - '0');
		i++;
	}
	return (result);
}
