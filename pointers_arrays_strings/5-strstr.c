#include "main.h"
#include <stddef.h>

/**
 * _strstr - locates a substring
 * @haystack: string to search in
 * @needle: substring to find
 *
 * Return: pointer to start of needle in haystack, or NULL
 */
char *_strstr(char *haystack, char *needle)
{
char *h, *n;

while (*haystack)
{
h = haystack;
n = needle;
while (*n && *h == *n)
{
h++;
n++;
}
if (!*n)
return (haystack);
haystack++;
}
if (!*needle)
return (haystack);
return (NULL);
}