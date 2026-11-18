#include <stdio.h>

/**
 * main - prints the name of the program, followed by a new line
 * @argc: number of arguments passed to the program
 * @argv: array of the arguments, where argv[0] is the program name
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	(void)argc;
	printf("%s\n", argv[0]);
	return (0);
}