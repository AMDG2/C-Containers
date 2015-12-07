C-Containers
============

C-Containers is a little library that helps you play with containers in C.

Documentation
=============

You can generate a documentation using `make documentation`

Examples
========

You also have examples in the [examples](examples/) folder.

You can run the example with `make` then `./examples/example`

Overview
========
This library use macro to create new types, and associated functions to play with.

Actually there are two available containers :
- List
- Map
- Stack
- Queue

List container
--------------
A list container is a doubly chained list. Each element have a value, and an index.
The index is an `unsigned int` and the value type depends on what you define.

To create a list container you must call two macros:
- `NEW_LIST_DEFINITION`
	- generally called in a header file (could be a source file)
	- it creates needed structures and functions prototypes
- `IMPLEMENT_LIST`
	- called in a source file (can't be called in header)
	- it creates functions implementation

To see an example open the `examples/main.c` file.

Map container
--------------
A Map container is a doubly chained list. Each element have a value, and an index.
The index and the value types depends on what you define.

To create a list container you must call two macros:
- `NEW_MAP_DEFINITION`
	- generally called in a header file (could be a source file)
	- it creates needed structures and functions prototypes
- `IMPLEMENT_MAP`
	- called in a source file (can't be called in header)
	- it creates functions implementation

To see an example open the `examples/main.c` file.


License
=======
This library is under GPLv3+ license.
