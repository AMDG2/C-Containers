/**
 * @file list.h
 * @brief List container definition
 * @author Baudouin FEILDEL
 */
#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// =============
//  Definitions
// =============
#define NEW_LIST_ELEM(LIST, ElemTypename, ValueType) \
/**
 Iterator to an element of a LIST object
 */ \
typedef struct _ ## ElemTypename \
{ \
	ValueType    value; /**< Value of the element */\
	unsigned int index; /**< Index of the element */\
	struct _ ## ElemTypename * next; /**< Pointer to the next element in the list */\
	struct _ ## ElemTypename * prev; /**< Pointer to the previous element in the list */\
} ElemTypename

#define NEW_LIST_TYPE(LIST, ValueType) \
NEW_LIST_ELEM(LIST, LIST ## _elem_t, ValueType); \
typedef struct LIST \
{ \
	LIST ## _elem_t * begin; /**< Beginning of the list */\
	LIST ## _elem_t * end; /**< End of the list */\
	int    size; /**< List size */\
	size_t elemSize; /**< Size of one element in the list */\
	int    freeValue; /**< Flag:<br>1: Automatically free the value<br>0: Do not automatically free the value */\
	void (*_copyValue) (ValueType * dest, ValueType * src); /**< Pointer to a function used to copy a value */\
	int  (*_cmpValue)  (ValueType val1, ValueType val2); /**< Pointer to a function used to compare two values */\
	void (*_freeValue) (ValueType value); /**< Pointer to a function used to free a value */\
	void (*_print)     (ValueType value); /**< Pointer to a function used to print a value */\
} LIST

#define LIST_FN_NEW(LIST) \
/**
 @brief Create a new LIST object
 @return A pointer to an allocated and initialized
 LIST object in memory
 */ \
LIST * LIST ## _new()

#define LIST_FN_FREE(LIST) \
/**
 Destroy a LIST object
 @param list A pointer to a LIST object
 */ \
void LIST ## _free(LIST * list)

#define LIST_FN_ADD_STRUCT(LIST, Valuetype) \
/**
 Add an element to the list
 @details If an element already have this index
 its value will be updated.

 @param list  The list to use
 @param index The index of the element to add
 @param value The value to set
 @return      Return an iterator to the added element
 */ \
LIST ## _elem_t * LIST ## _add(LIST * list, unsigned int index, Valuetype value)

#define LIST_FN_REMOVE_STRUCT(LIST) \
/**
 Remove an element from the list
 @param list  A pointer to a valid LIST object
 @param index The index of the element to remove
 @return      The pointer to the LIST object
 */ \
LIST * LIST ## _remove(LIST * list, unsigned int index)

#define LIST_FN_GET_STRUCT(LIST) \
/**
 Get an iterator to an element from a list
 @param list  A pointer to a valid LIST object
 @param index The index of the element to get
 @return      Iterator to the element if present. NULL otherwise
 */ \
LIST ## _elem_t * LIST ## _get(LIST * list, unsigned int index)

#define LIST_FN_SEARCH_STRUCT(LIST, Valuetype) \
/**
 Search for an element in list
 @param list   A pointer to a valid LIST object
 @param search The element to search in the list. Must be a valid ValueType object
 @return       Iterator to the element if found. NULL otherwise
 */ \
LIST ## _elem_t * LIST ## _search(LIST * list, Valuetype search)

#define LIST_FN_UPDATE_IDX(LIST) \
/**
 Update index of elements in \c list
 @details This function will re-index all the elements in the \c list

 @param list A pointer to a valid LIST object
 */ \
LIST * LIST ## _updateIndex(LIST * list)

/*
#define LIST_FN_GET_PREVIOUS(LIST, Indextype) \
LIST ## _elem_t LIST ## _find_previous(LIST * list, Indextype index)
 */

#define LIST_FN_PRINT_STRUCT(LIST) \
/**
 Print a list
 @param list A pointer to a valid LIST object
 */ \
void LIST ## _print(LIST * list)

// =================
//  Implementations
// =================
#define IMPLEMENT_LIST_FN_NEW(LIST, Valuetype, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, FN_PRINT_VAL) \
LIST * LIST ## _new() \
{ \
	LIST * list = malloc(sizeof(LIST)); \
	list->size  = 0; \
	list->begin = NULL; \
	list->end   = NULL; \
	list->elemSize   = sizeof(LIST ## _elem_t); \
	list->freeValue  = 1; \
	list->_copyValue = FN_CPY_VAL; \
	list->_cmpValue  = FN_CMP_VAL; \
	list->_freeValue = FN_FREE_VAL; \
	list->_print     = FN_PRINT_VAL; \
	return list; \
}

#define IMPLEMENT_LIST_FN_FREE(LIST) \
void LIST ## _free(LIST * list) \
{ \
	LIST ## _elem_t * it = NULL; \
	if(list == NULL) return; \
	for(it = list->begin ; it != NULL ; it = it->next) \
	{ \
		if(it->prev) free(it->prev); \
		if(list->freeValue) list->_freeValue(it->value); \
	} \
	free(list); \
}

#define IMPLEMENT_LIST_FN_ADD_STRUCT(LIST, Valuetype) \
LIST ## _elem_t * LIST ## _add(LIST * list, unsigned int index, Valuetype value) \
{ \
	LIST ## _elem_t * elem = NULL; \
	/* Test if list is NULL */\
	if(list == NULL) \
		return NULL; \
	/* Test if index exists */\
	elem = LIST ## _get(list, index);\
	if(elem != NULL) \
	{ \
		if(list->freeValue) list->_freeValue(elem->value); \
		list->_copyValue(&(elem->value), &(value)); \
		return elem; \
	} \
	/* Create the element */\
	elem = malloc(list->elemSize); \
	elem->prev = NULL; \
	elem->next = NULL; \
	elem->index = index; \
	list->_copyValue(&(elem->value), &(value)); \
	/* Insert the element */\
	list->size++; \
	if(list->begin == NULL) \
	{ \
		list->begin = elem; \
		list->end   = elem; \
	} \
	else \
	{ \
		list->end->next = elem; \
		elem->prev = list->end; \
		list->end = elem; \
	} \
	return elem; \
}


#define IMPLEMENT_LIST_FN_REMOVE_STRUCT(LIST) \
LIST * LIST ## _remove(LIST * list, unsigned int index) \
{ \
	LIST ## _elem_t * elem = LIST ## _get(list, index); \
	/* Check Empty list */\
	if(list == NULL) return NULL; \
	if(elem != NULL) \
	{ \
		if(list->freeValue) list->_freeValue(elem->value); \
		elem->prev->next = elem->next; \
		elem->next->prev = elem->prev; \
		free(elem); \
		list->size--; \
	} \
	return list; \
}


#define IMPLEMENT_LIST_FN_GET_STRUCT(LIST) \
LIST ## _elem_t * LIST ## _get(LIST * list, unsigned int index) \
{ \
	LIST ## _elem_t * out = NULL; \
	LIST ## _elem_t * it = NULL; \
	/* Check empty list */ \
	if(list == NULL)        return NULL; \
	if(list->begin == NULL) return NULL; \
	/* Start search */ \
	it = list->begin; \
	while(it != NULL) \
	{ \
		if(it->index == index) \
		{ \
			out = it; \
			it  = NULL; \
		} \
		else \
			it = it->next; \
	} \
	return out; \
}


#define IMPLEMENT_LIST_FN_SEARCH_STRUCT(LIST, Valuetype) \
LIST ## _elem_t * LIST ## _search(LIST * list, Valuetype search) \
{ \
	LIST ## _elem_t * out = NULL; \
	LIST ## _elem_t * it = NULL; \
	/* Check empty list */ \
	if(list == NULL)        return NULL; \
	if(list->begin == NULL) return NULL; \
	/* Start search */ \
	it = list->begin; \
	while(it != NULL) \
	{ \
		if(list->_cmpValue(it->value, search) == 0) \
		{ \
			out = it; \
			it = NULL; \
		} \
		else \
			it = it->next; \
	} \
	return out; \
}

#define IMPLEMENT_LIST_FN_UPDATE_IDX(LIST) \
LIST * LIST ## _updateIndex(LIST * list) \
{ \
	LIST ## _elem_t * it = NULL; \
	unsigned int index = 0; \
	/* Check empty list */\
	if(list == NULL) return NULL; \
	/* Start update */\
	it = list->begin; \
	while(it != NULL) \
	{ \
		it->index = index++;\
		it = it->next;\
	} \
	return list; \
}

#define IMPLEMENT_LIST_FN_PRINT(LIST) \
void LIST ## _print(LIST * list) \
{ \
	LIST ## _elem_t * it = NULL; \
	printf("["); \
	it = list->begin; \
	for(it = list->begin ; it != NULL ; it = it->next) \
	{ \
		list->_print(it->value); \
		if(it->next != NULL) \
			printf(", "); \
	} \
	printf("]\n"); \
}

// MACRO HELPERS (One line definitions && implementations)
#define NEW_LIST_DEFINITION(LIST, VALUETYPE) \
NEW_LIST_TYPE(LIST, VALUETYPE); \
LIST_FN_NEW(LIST); \
LIST_FN_FREE(LIST); \
LIST_FN_ADD_STRUCT(LIST, VALUETYPE); \
LIST_FN_REMOVE_STRUCT(LIST); \
LIST_FN_GET_STRUCT(LIST); \
LIST_FN_SEARCH_STRUCT(LIST, VALUETYPE); \
LIST_FN_UPDATE_IDX(LIST); \
LIST_FN_PRINT_STRUCT(LIST)

#define IMPLEMENT_LIST(LIST, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, FN_PRINT_VAL) \
IMPLEMENT_LIST_FN_NEW(LIST, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, FN_PRINT_VAL); \
IMPLEMENT_LIST_FN_FREE(LIST); \
IMPLEMENT_LIST_FN_ADD_STRUCT(LIST, VALUETYPE); \
IMPLEMENT_LIST_FN_REMOVE_STRUCT(LIST); \
IMPLEMENT_LIST_FN_GET_STRUCT(LIST); \
IMPLEMENT_LIST_FN_SEARCH_STRUCT(LIST, VALUETYPE); \
IMPLEMENT_LIST_FN_UPDATE_IDX(LIST); \
IMPLEMENT_LIST_FN_PRINT(LIST)


#ifdef __cplusplus
}
#endif

#endif // __LIST_H__
