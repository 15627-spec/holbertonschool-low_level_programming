cat > main.h << 'EOF'
#ifndef MAIN_H
#define MAIN_H

void reset_to_98(int *n);

#endif /* MAIN_H */
EOF
cat > 0-reset_to_98.c << 'EOF'
#include "main.h"

/**
 * reset_to_98 - updates the value pointed to by n to 98
 * @n: pointer to the integer to update
 *
 * Return: nothing.
 */
void reset_to_98(int *n)
{
    *n = 98;
}
EOF
sed -i 's/^    /\t/' 0-reset_to_98.c
cat > 0-main.c << 'EOF'
#include "main.h"
#include <stdio.h>

/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main(void)
{
    int n;

    n = 402;
    printf("n=%d\n", n);
    reset_to_98(&n);
    printf("n=%d\n", n);
    return (0);
}
EOF
