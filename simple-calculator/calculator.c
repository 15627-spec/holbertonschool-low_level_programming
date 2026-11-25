#include <stdio.h>

int main(void)
{
    int choice;

    /* Declare your addition variables here */

    do
    {
        printf("Simple Calculator\n");
        printf("1) Add\n");
        printf("2) Subtract\n");
        printf("3) Multiply\n");
        printf("4) Divide\n");
        printf("0) Quit\n");

        printf("what should we calculate today ?\n");
        scanf("%d", &choice);

        if (choice == 0)
        {
            printf("Bye!\n");
        }
        else if (choice < 0 || choice > 4)
        {
            printf("Invalid choice\n");
        }
        else if (choice == 1)
        {
            /* Ask for the first number */

            /* Read the first number */

            /* Ask for the second number */

            /* Read the second number */

            /* Calculate the sum */

            /* Display the result */
        }

    } while (choice != 0);

    return (0);
}