#include "main.h"

/**
 * print_word - prints a string using _putchar
 * @s: the string to print
 *
 * Return: void
 */
static void print_word(char *s)
{
	while (*s)
		_putchar(*s++);
}

/**
 * fizz_buzz - prints the numbers from 1 to 100 with Fizz, Buzz and FizzBuzz
 *
 * Return: void
 */
void fizz_buzz(void)
{
	int i;

	for (i = 1; i <= 100; i++)
	{
		if (i != 1)
			_putchar(' ');
		if (i % 15 == 0)
			print_word("FizzBuzz");
		else if (i % 3 == 0)
			print_word("Fizz");
		else if (i % 5 == 0)
			print_word("Buzz");
		else
		{
			if (i > 99)
				_putchar('1');
			if (i > 9)
				_putchar((i / 10) % 10 + '0');
			_putchar(i % 10 + '0');
		}
	}
	_putchar('\n');
}
