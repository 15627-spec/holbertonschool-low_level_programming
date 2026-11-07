#include "main.h"
#include <stddef.h>

/**
 * _strpbrk - searches a string for any of a set of bytes
 * @s: string
 * @accept: characters to look for
 *
 * Return: pointer to first match in s, or NULL
 */
char *_strpbrk(char *s, char *accept)
{
char *a;

while (*s)
{
for (a = accept; *a; a++)
{
if (*s == *a)
return (s);
}
s++;
}
return (NULL);
}