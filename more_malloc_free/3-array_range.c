#include "main.h"
#include <stdlib.h>

/**
 * array_range - creates an array of integers from min to max
 * @min: first value (included)
 * @max: last value (included)
 *
 * Return: pointer to the new array, or NULL on failure
 */
int *array_range(int min, int max)
{
	int *arr;
	unsigned int i, size;

	if (min > max)
		return (NULL);
	size = (unsigned int)max - (unsigned int)min + 1;
	arr = malloc(sizeof(int) * size);
	if (arr == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
		arr[i] = min + (int)i;
	return (arr);
}
