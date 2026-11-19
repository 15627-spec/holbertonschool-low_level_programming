#include <stdio.h>

/**
 * main - Program reads arguments
 * @argc: Number of arguments
 * @argv: Array of argument strings
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	/* Declare variable */
	int i;

	/* Set loop */
	for (i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	return (0);
}
