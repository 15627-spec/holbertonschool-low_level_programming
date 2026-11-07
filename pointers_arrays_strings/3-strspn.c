#include "main.h"

/**
 * _strspn - gets the length of a prefix substring
 * @s: string
 * @accept: allowed characters
 *
 * Return: number of leading bytes of s made only of accept characters
 */
unsigned int _strspn(char *s, char *accept)
{
unsigned int i = 0;
char *a;
int found;

while (s[i])
{
found = 0;
for (a = accept; *a; a++)
{
if (s[i] == *a)
{
found = 1;
break;
}
}
if (!found)
break;
i++;
}
return (i);
}