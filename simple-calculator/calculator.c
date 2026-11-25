#include <stdio.h>

/*
 * Ce calculateur utilise des nombres decimaux (double) pour toutes
 * les operations, afin de gerer les divisions non entieres (10 / 4 = 2.5).
 */

/**
 * calculate - lit A et B puis effectue l'operation demandee
 * @choice: operation choisie (1 a 4)
 */
void calculate(int choice)
{
	double a, b;

	printf("A: ");
	scanf("%lf", &a);
	printf("B: ");
	scanf("%lf", &b);

	if (choice == 1)
		printf("Result: %g\n", a + b);
	else if (choice == 2)
		printf("Result: %g\n", a - b);
	else if (choice == 3)
		printf("Result: %g\n", a * b);
	else if (choice == 4)
	{
		if (b == 0)
			printf("Error: division by zero\n");
		else
			printf("Result: %g\n", a / b);
	}
}

/**
 * main - point d'entree du calculateur
 *
 * Return: 0 en cas de succes
 */
int main(void)
{
	int choice;

	do {
		printf("Simple Calculator\n");
		printf("1) Add\n");
		printf("2) Subtract\n");
		printf("3) Multiply\n");
		printf("4) Divide\n");
		printf("0) Quit\n");

		printf("what should we calculate today ?\n");
		scanf("%d", &choice);

		if (choice == 0)
			printf("Bye!\n");
		else if (choice < 0 || choice > 4)
			printf("Invalid choice\n");
		else
			calculate(choice);

	} while (choice != 0);

	return (0);
}