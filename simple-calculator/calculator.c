else if (choice == 4)
{
    printf("A: ");
    scanf("%d", &A);

    printf("B: ");
    scanf("%d", &B);

    if (B == 0)
    {
        printf("Error: Division by zero is not allowed.\n");
    }
    else
    {
        result = A / B;
        printf("Result: %d\n", result);
    }
}