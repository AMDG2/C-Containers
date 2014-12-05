C-Containers
============

C-Containers is a little library that helps you play with containers in C.

Documentation
=============

You can generate a documentation using `make documentation`

Examples
========

Play with an example : http://runnable.com/VIDc4pRLEWI-scta/c-containers-example-for-c%2B%2B

You also have examples in the [examples](https://github.com/AMDG2/C-Containers/blob/master/examples/) folder.

You can run the example with `make` then `./examples/example`

Explications
============
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
