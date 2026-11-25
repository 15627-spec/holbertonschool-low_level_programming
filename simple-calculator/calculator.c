#include <stdio.h>

int main(void)
{
    int choice;

    /* Declare your calculation variables here */

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
            /* Addition */
        }
        else if (choice == 2)
        {
            /* Subtraction */
        }
        else if (choice == 3)
        {
            /* Multiplication */
        }

    } while (choice != 0);

    return (0);
}