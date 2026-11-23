## Aliasing and Use-After-Free

### 1. Before `free(a)`

The program allocates one heap array containing **5 integers**.

- The pointers `a` and `b` are local variables stored on the **stack**.
- The allocated array is stored on the **heap**.
- Both `a` and `b` point to the same heap block.
- This means `b` is an alias of `a`'s heap block.
- The heap block is valid, so both pointers can safely access the array.

**Memory map:**

```text
STACK                         HEAP
+----------------+            +----------------------+
| a = address H  |----------->|                      |
|                |            |  Array of 5 integers |
| b = address H  |----------->|                      |
+----------------+            +----------------------+

       a and b point to the same heap block
```

### 2. When `free(a)` is called

When the program calls `free(a)`, the allocated heap block is released.

- `free(a)` ends the lifetime of the allocated array.
- The memory block is no longer valid to access.
- The pointer `a` is not automatically set to `NULL`.
- The pointer `b` is also unchanged because it still contains the same address.

The important idea is that freeing the memory through `a` ends the lifetime of the heap object for **both pointers**.

**Memory map:**

```text
STACK                         HEAP
+----------------+            +----------------------+
| a = address H  |----------->|   FREED MEMORY       |
|                |            |                      |
| b = address H  |----------->|   NO LONGER VALID    |
+----------------+            +----------------------+

       Both pointers still hold the old address
```

### 3. After `free(a)`

After the memory is freed:

- Both `a` and `b` are dangling pointers.
- They still contain the old address, but it no longer refers to valid allocated memory.
- Reading `b[2]` is a **use-after-free**.
- Writing `b[3] = 1234` is also a **use-after-free**.
- Printing the value of `b` still displays its stored address, but that does not mean the memory is valid.

These later accesses are unsafe because the program is trying to use memory after its lifetime has ended.

### 4. Conclusion

This example demonstrates **aliasing and use-after-free**.

Even though `a` and `b` are two separate pointer variables, they refer to the same heap allocation. The program is responsible for releasing that allocation, and calling `free(a)` releases it for both pointers.

Before `free(a)`, the heap block is valid and accessible through both pointers. After `free(a)`, the block's lifetime ends, and both pointers become dangling.

Any later attempt to read or write through `b` accesses memory that has already been freed, resulting in a use-after-free bug.