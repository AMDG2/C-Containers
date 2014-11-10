CArray
======

CArray is a little library that helps you play with indexed array in C.

Let me play !
=============

Example
-------

### header.h

```cpp
#include "array.h"

NEW_ARRAY_DEFINITION(IntArray, int, int);
```

### main.c

```cpp
#include "header.h"

int main(int argc, char ** argv)
{
	IntArray * array = IntArray_new();
	IntArray_elem_t * it = NULL;
	int   sum  = 0;
	float avg = 0;

	IntArray_add(array, 0, 12);
	IntArray_add(array, 1, 15);
	IntArray_add(array, 2, 8);
	IntArray_add(array, 3, 16);
	IntArray_add(array, 4, 18);
	IntArray_add(array, 5, 6);
	IntArray_add(array, 6, 11);

	for(it = array->array ; it != NULL ; it = it->next)
		sum += it->value;

	avg = sum/array->size;

	printf("Average note : %.2f\n", avg);

	return 0;
}
```

Boring stuff (explications)
---------------------------
To create a new array you first need to create an array definition calling the MACRO `NEW_ARRAY_DEFINITION`
This macro takes 3 parameters :

1. Your array type name
2. The type of the value of array elements
3. The type of the index of array elements

Then you need to implement your definitions using the `IMPLEMENT_ARRAY` macro.
This macro takes a lot of parameters. The third first are the same as the definitions. Then you need to pass 6 pointer to functions :

1. Function to copy a value, prototype: `void _copy(VALUETYPE * dest, VALUETYPE * src)`
2. The same as 1. but for indexes
3. Function to compare two values, prototype: `int _cmp(VALUETYPE val1, VALUETYPE val2)`
4. The same as 3. but for indexes
5. Function to free a value, prototype: `void _free(VALUETYPE value)`
6. The same as 5. but for indexes

License
=======
This library is under GPLv3+ license.
