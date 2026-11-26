# Singly Linked Lists

## Description
This project introduces singly linked lists in C. It implements a function that traverses and prints every element of a linked list.

## Data Structure

Each node contains:
- `str`: A pointer to a string.
- `len`: The length of the string.
- `next`: A pointer to the next node.

## Function

### `print_list`

Prints all elements of a linked list.

**Prototype:**
```c
size_t print_list(const list_t *h);
```

**Parameters:**
- `h`: Pointer to the first node of the list.

**Return:**
- The number of nodes in the list.

**Output format:**
```text
[5] Hello
[5] World
```

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o lists
```

##