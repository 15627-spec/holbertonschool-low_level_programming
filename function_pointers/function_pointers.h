#ifndef FUNCTION_POINTERS_h
#define FUNCTION_POIONTERS_h

#include <stddef.h>

void array_iterator(int *array, size_t size, void(*action)(int));

#endif