# Memory maps and execution analysis

## Method and build results

The programs analysed are the four C files in `programs/`: `stack_example.c`, `heap_example.c`, `aliasing_example.c`, and `crash_example.c`.

The supplied Makefile uses `gcc -Wall -Wextra -Werror -pedantic -std=gnu89 -g`. Running `make` with those exact flags compiles `stack_example` and `heap_example`, then stops at `aliasing_example.c`: GCC diagnoses the accesses through `b` after `free(a)` as `-Wuse-after-free`, and `-Werror` makes those warnings fatal. Consequently, the unmodified `make` does not build all four programs.

To execute all programs without changing the source or Makefile, I rebuilt with:

```sh
make clean
make CFLAGS='-Wall -Wextra -Werror -Wno-error=use-after-free -pedantic -std=gnu89 -g'
```

This allows the intentional use-after-free diagnostics to remain warnings while treating other warnings as errors. All four executables were produced. They were then run normally, without Valgrind:

- `stack_example`: exits normally (status 0).
- `heap_example`: exits normally (status 0).
- `aliasing_example`: exits normally in this run (status 0), despite undefined behaviour.
- `crash_example`: terminates with a segmentation fault (status 139).

Addresses printed by these programs are process-specific examples, not fixed addresses. The diagrams below use symbolic addresses. Stack-frame placement and register use are implementation details; the important distinction is automatic local objects versus dynamically allocated objects.

## 1. `stack_example.c` — recursion and automatic storage

### Execution

`main` calls `walk_stack(0, 3)`. Each invocation of `walk_stack` creates its own automatic local `marker`, with value `depth * 10`, and calls `dump_frame`. `dump_frame` creates its own automatic `local_int`, `local_buf[16]`, and pointer `p_local`, which is initialized to `&local_int`.

The recursive calls are `walk_stack(0)`, `walk_stack(1)`, `walk_stack(2)`, and `walk_stack(3)`. All four `walk_stack` invocations are active simultaneously when depth 3 is reached. Their `marker` values are respectively 0, 10, 20, and 30. Each call to `dump_frame` is a separate, shorter-lived function activation; its locals cease to exist when that call returns. `dump_frame` is called once on entry and once after the recursive call returns, so each `walk_stack` activation creates two separate `dump_frame` activations over its lifetime.

### Simplified stack map at deepest recursion

```text
ACTIVE STACK FRAMES (conceptual; newest call shown first)
+----------------------------------------------+
| dump_frame("enter", 3)                       |
| local_int = 103                              |
| p_local = &local_int (same frame)             |
| local_buf[16], begins with 'D', '\0'          |
+----------------------------------------------+
| walk_stack(depth=3, max_depth=3)              |
| marker = 30                                  |
+----------------------------------------------+
| walk_stack(depth=2, max_depth=3)              |
| marker = 20                                  |
+----------------------------------------------+
| walk_stack(depth=1, max_depth=3)              |
| marker = 10                                  |
+----------------------------------------------+
| walk_stack(depth=0, max_depth=3)              |
| marker = 0                                   |
+----------------------------------------------+
| main()                                       |
+----------------------------------------------+

HEAP: no allocations made by this program
```

The `dump_frame` frame for depth 3 returns before `walk_stack(3)` executes its exit-side `dump_frame`. Then `walk_stack(3)` returns, followed by depth 2, depth 1, and depth 0. Frames are therefore unwound in reverse call order. The `marker` belonging to a `walk_stack` invocation remains alive while its recursive child runs, and is still printed after that child returns.

### Pointer relationship and lifetimes

Within each `dump_frame` call, `p_local` aliases `local_int`: `p_local == &local_int`, and `*p_local` would access that integer. Both are automatic objects in that `dump_frame` activation. When `dump_frame` returns, both objects' lifetimes end. No pointer to `local_int` is returned or retained by this program. `local_buf` is also an automatic local array and has the same lifetime as that `dump_frame` activation. There is no heap memory in this example.

## 2. `heap_example.c` — allocations, frees, and a leak

### Allocation map after both constructor calls

`person_new` first allocates one `Person` structure with `malloc(sizeof(Person))`, then allocates a separate character array of `len + 1` bytes for the copied name. On the usual ABI used for this run, `Person` contains a `char *` and an `int` (with possible structure padding); do not assume a universal structure size. The `name` allocation includes the terminating null byte.

```text
main stack                              heap
+----------------------+                +------------------------------+
| alice --------------+|--------------->| Person object for Alice      |
| bob ----------------+|----------+     | .name -------------------+   |
+----------------------+          |     | .age = 30                 |   |
                                  |     +---------------------------|---+
                                  |                                 |
                                  |     +---------------------------v---+
                                  |     | character allocation:         |
                                  |     | 'A' 'l' 'i' 'c' 'e' '\0'       |
                                  |     +-------------------------------+
                                  |
                                  |     +-------------------------------+
                                  +---->| Person object for Bob         |
                                        | .name -------------------+     |
                                        | .age = 41                 |     |
                                        +---------------------------|-----+
                                                                    |
                                        +---------------------------v-----+
                                        | 'B' 'o' 'b' '\0'               |
                                        +---------------------------------+
```

The arrows represent pointer values; actual addresses vary. The `alice` and `bob` pointer variables are automatic locals in `main`. The two `Person` objects and two name buffers are separate heap allocations. `person_new`'s locals (`i`, `len`, and `p`) exist only during that call. The returned pointer is copied into `alice` or `bob`; the constructor's local pointer `p` then ceases to exist, but the allocated object remains alive.

### Deallocation sequence

1. `free(bob->name)` releases Bob's character buffer.
2. `free(bob)` releases Bob's `Person` object. The local pointer variable `bob` itself remains in `main`, but it is not used afterward; it is not automatically set to `NULL`.
3. `person_free_partial(alice)` calls `free(p)` and therefore releases Alice's `Person` structure only.
4. Alice's separately allocated `alice->name` buffer is **not freed**. It becomes unreachable when the `Person` structure containing its only program-held pointer is freed. This is the deliberate memory leak.
5. `main` returns; its local pointer variables' lifetimes end. Returning from `main` does not turn the leaked allocation into a correctly freed allocation; the allocation was not explicitly released by the program.

`person_free_partial` is deliberately incomplete: it frees the structure but not the nested `name` allocation. Its failure-path use has the same issue if a name allocation succeeded before a later constructor failure is handled.

## 3. `aliasing_example.c` — aliasing and use-after-free

### Before `free(a)`

`make_numbers(5)` allocates `5 * sizeof(int)` bytes on the heap (20 bytes when `sizeof(int) == 4`, as on the tested platform) and fills the five elements with 0, 11, 22, 33, and 44. It returns the allocation's address to `main`.

```text
main stack                              heap
+----------------------+                +------------------------------+
| a = H ---------------+--------------->| int array H:                  |
| b = H ---------------+---- alias ---->| [0] [11] [22] [33] [44]      |
| n = 5                |                +------------------------------+
+----------------------+
```

`a` and `b` are two distinct stack pointer variables containing the same heap address `H`. They are aliases for the same allocation, not two allocations. `make_numbers`'s local variables `i` and `arr` belong to its stack frame; that frame ends when the function returns. The heap array remains allocated and is now reachable through both `a` and `b`.

### After `free(a)`

`free(a)` releases the one heap allocation. It does not search for or clear other pointer variables containing the same address. Therefore `b` still contains the numerical address `H`, but the allocation's lifetime has ended. `a` also retains its old value; neither pointer is automatically set to `NULL`.

```text
main stack                              heap
+----------------------+                +------------------------------+
| a = H (dangling)     |                | allocation H: FREED           |
| b = H (dangling)     |                | no live int array exists here |
| n = 5                |                +------------------------------+
+----------------------+
```

The subsequent `printf` that reads `b[2]` and the assignment `b[3] = 1234` both access the released allocation. These are use-after-free operations and have undefined behaviour. The printed integer may look like a random or stale value, the process may crash, or other effects may occur; no particular contents or outcome are guaranteed. The program does not perform a second `free`, so this example is not a double-free example. At function exit, `a` and `b` local variables cease to exist; that does not repair the earlier invalid accesses.

## 4. `crash_example.c` — NULL dereference

`main` initializes `n` to 0 and calls `allocate_numbers(0)`. The function checks `if (n <= 0)` and immediately returns `NULL`; it does not call `malloc`. Back in `main`, `nums` therefore receives `NULL`.

```text
main stack                         heap
+----------------------+           +---------------------------+
| nums = NULL          |           | no allocation was made    |
| n = 0                |           +---------------------------+
+----------------------+
```

The next statement, `nums[0] = 42`, attempts to write through a null pointer. This is undefined behaviour and caused the observed segmentation fault (status 139) on the test run. Execution does not reach the later `printf`, `free(nums)`, or `return 0`. There is no heap allocation to free. The local variables `nums` and `n` are automatic objects in `main` and their lifetimes end when the process terminates.

## AI-generated explanation review and correction

A potentially misleading AI explanation for `aliasing_example.c` would be: **"After `free(a)`, `b` points to invalid memory, and the garbage value printed from `b[2]` is the new contents of the freed block."** This is inaccurate and too vague.

Correction:

- Before the free, `a` and `b` both contain the same address `H`; they alias one 20-byte allocation (assuming 4-byte `int`).
- `free(a)` ends the lifetime of that allocation. It does not change the value stored in `b`; `b` still contains `H` and is a dangling pointer.
- Reading `b[2]` is an invalid access to an object whose lifetime has ended. The displayed integer is an observed consequence of undefined behaviour, not a defined new value or reliable evidence of what the allocator stored.
- Writing `b[3]` is also invalid. The source contains no second `free`, so calling this a double free would be another error.

A second important correction concerns `heap_example.c`: freeing Alice's `Person` object does **not** also free the separately allocated `alice->name` buffer. The nested allocation remains allocated and is leaked because the program loses the only pointer to it when it frees the structure.

## Summary table

| Program | Stack objects | Heap objects | Lifetime issue / result |
|---|---|---|---|
| `stack_example` | `main`, recursive `walk_stack` locals, `dump_frame` locals | None | Each activation's automatic locals end when that function returns; recursion creates distinct simultaneous frames. |
| `heap_example` | `alice`, `bob`, constructor locals, `i`/`len` | Two `Person` objects and two name buffers | Bob's structure and name are freed; Alice's structure is freed but Alice's name buffer leaks. |
| `aliasing_example` | `a`, `b`, `n`, `make_numbers` locals | One five-element integer array | `a` and `b` alias one allocation; freeing through `a` leaves `b` dangling; later read/write are use-after-free. |
| `crash_example` | `nums`, `n`, allocator locals if entered | None for `n == 0` | `allocate_numbers` returns `NULL`; `nums[0]` dereference causes the observed segmentation fault. |

## Notes on interpretation

- Stack diagrams are conceptual. The C language specifies object storage duration and lifetime, not a universal physical stack layout or exact addresses.
- Heap block sizes and addresses depend on the platform and allocator. The requested sizes are determined by the expressions passed to `malloc`; allocator metadata is not part of the requested C object size.
- Once an allocation is freed, do not describe its old bytes as having a predictable value. The program may no longer access the object through any alias.
- A program that happens to exit normally after undefined behaviour is still incorrect; the absence of a crash does not make the access valid.
