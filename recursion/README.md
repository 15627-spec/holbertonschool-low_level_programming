# Recursion

This project is about recursion in C: functions that call themselves to
solve a problem by breaking it into smaller ones.

## Requirements

- Compiled on Ubuntu with `gcc`
- Flags: `-Wall -Wextra -Werror -pedantic -std=gnu89`
- Code follows the Betty style
- No global variables, no loops (`for`, `while`, `goto`) in the recursive functions

## Compilation

```bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 0-main.c 0-puts_recursion.c _putchar.c -o recursion
./recursion
```

## Files

| File | Description |
|------|-------------|
| `main.h` | Header file with all prototypes |
| `_putchar.c` | Writes a character to stdout |
| `0-puts_recursion.c` | `_puts_recursion`: prints a string followed by a new line |
| `1-print_rev_recursion.c` | `_print_rev_recursion`: prints a string in reverse |
| `2-strlen_recursion.c` | `_strlen_recursion`: returns the length of a string |
| `3-factorial.c` | `factorial`: returns the factorial of a number (-1 if negative) |
| `4-pow_recursion.c` | `_pow_recursion`: returns x raised to the power y (-1 if y is negative) |
| `5-sqrt_recursion.c` | `_sqrt_recursion`: returns the natural square root of a number (-1 if none) |
| `6-is_prime_number.c` | `is_prime_number`: returns 1 if the number is prime, 0 otherwise |

## How recursion works here

Each function has a base case that stops the calls and a recursive
case