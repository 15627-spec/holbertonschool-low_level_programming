#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main(void)
{
    char *s1 = "Best";
    char *s2 = "School";
    char *s3;

    s3 = str_concat(s1, s2);
    if (s3 == NULL)
    {
        printf("failed\n");
        return (1);
    }
    printf("%s\n", s3);
    free(s3);
    return (0);
}