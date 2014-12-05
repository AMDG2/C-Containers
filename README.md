C-Containers
============

C-Containers is a little library that helps you play with containers in C.

Let me play !
=============

Example
-------

Play with the example : http://runnable.com/VIDc4pRLEWI-scta/c-containers-example-for-c%2B%2B

### header.h

```C
#include "list.h"

NEW_LIST_DEFINITION(AgeList, int, char *);
```

### main.c

```C
#include <stdio.h>
#include "header.h"

IMPLEMENT_LIST(AgeList, int, char *, Int_copy, Str_copy, Int_cmp, Str_cmp, Int_free, Str_free);

int main(int argc, char ** argv)
{
	AgeList * list = AgeList_new();
	AgeList_elem_t * it = NULL;
	int   sum  = 0;
	float avg = 0;

	AgeList_add(list, "Paul", 12);
	AgeList_add(list, "Mary", 15);
	AgeList_add(list, "John", 8);
	AgeList_add(list, "Yo", 16);
	AgeList_add(list, "Georges", 18);
	AgeList_add(list, "Harrison", 6);
	AgeList_add(list, "Erwan", 11);

	for(it = list->array ; it != NULL ; it = it->next)
	{
		printf("%s is %d years old\n", it->index, it->value);
		sum += it->value;
	}

	avg = sum/array->size;

	printf("Average age : %.2f\n", avg);

	return 0;
}
```

Boring stuff (explications)
---------------------------
To create a new array you first need to create an array definition calling the MACRO [`NEW_LIST_DEFINITION`](https://github.com/AMDG2/C-Containers/blob/master/list.h#L215)
This macro takes 3 parameters :

1. Your array type name
2. The type of the value of array elements
3. The type of the index of array elements

Then you need to implement your definitions using the [`IMPLEMENT_LIST`](https://github.com/AMDG2/C-Containers/blob/master/list.h#L224) macro.
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
