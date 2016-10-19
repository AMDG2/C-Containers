/**
 * @file set.h
 * @brief Set container definition
 * @author Baudouin FEILDEL
 */
#ifndef __SET_H__
#define __SET_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// =============
//  Definitions
// =============
#define NEW_SET_ELEM(SET, ElemTypename, Valuetype) \
/**
 Iterator to an element of a SET object
 */ \
typedef struct _ ## ElemTypename \
{ \
	Valuetype    value; /**< Value of the element */\
	struct _ ## ElemTypename * next; /**< Pointer to the next element in the set */\
	struct _ ## ElemTypename * prev; /**< Pointer to the previous element in the set */\
} ElemTypename

#define NEW_SET_TYPE(SET, ValueType) \
NEW_SET_ELEM(SET, SET ## _elem_t, ValueType); \
typedef struct SET \
{ \
	SET ## _elem_t * begin; /**< Beginning of the set */\
	SET ## _elem_t * end; /**< End of the set */\
	int    size; /**< Set size */\
	size_t elemSize; /**< Size of one element in the set */\
	int    freeValue; /**< Flag:<br>1: Automatically free the value<br>0: Do not automatically free the value */\
	void (*_copyValue) (ValueType * dest, ValueType * src); /**< Pointer to a function used to copy a value */\
	int  (*_cmpValue)  (ValueType val1, ValueType val2); /**< Pointer to a function used to compare two values */\
	void (*_freeValue) (ValueType value); /**< Pointer to a function used to free a value */\
	void (*_print)     (ValueType value); /**< Pointer to a function used to print a value */\
} SET

#define SET_FN_NEW(SET) \
/**
 @brief Create a new SET object
 @return A pointer to an allocated and initialized
 SET object in memory
 */ \
SET * SET ## _new()

#define SET_FN_FREE(SET) \
/**
 Destroy a SET object
 @param set A pointer to a SET object
 */ \
void SET ## _free(SET * set)

#define SET_FN_ADD_STRUCT(SET, Valuetype) \
/**
 Add an element to the set
 @details If an element already have this index
 its value will be updated.

 @param set  The set to use
 @param index The index of the element to add
 @param value The value to set
 @return      Return an iterator to the added element
 */ \
SET ## _elem_t * SET ## _add(SET * set, Valuetype value)

#define SET_FN_REMOVE_STRUCT(SET, ValueType) \
/**
 Remove an element from the set
 @param set  A pointer to a valid SET object
 @param index The value to remove from SET object
 @return      The pointer to the SET object
 */ \
SET * SET ## _remove(SET * set, ValueType index)

#define SET_FN_GET_STRUCT(SET, ValueType) \
/**
 Get an iterator to an element from a set
 @param set  A pointer to a valid SET object
 @param index The value to get
 @return      Iterator to the element if present. NULL otherwise
 */ \
SET ## _elem_t * SET ## _get(SET * set, ValueType index)

#define SET_FN_SEARCH_STRUCT(SET, Valuetype) \
/**
 Search for an element in set
 @param set   A pointer to a valid SET object
 @param search The element to search in the set. Must be a valid ValueType object
 @return       Iterator to the element if found. NULL otherwise
 */ \
SET ## _elem_t * SET ## _search(SET * set, Valuetype search)

#define SET_FN_PRINT_STRUCT(SET) \
/**
 Print a set
 @param set A pointer to a valid SET object
 */ \
void SET ## _print(SET * set)

// =================
//  Implementations
// =================
#define IMPLEMENT_SET_FN_NEW(SET, Valuetype, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, FN_PRINT_VAL) \
SET * SET ## _new() \
{ \
	SET * set = malloc(sizeof(SET)); \
	set->size  = 0; \
	set->begin = NULL; \
	set->end   = NULL; \
	set->elemSize   = sizeof(SET ## _elem_t); \
	set->freeValue  = 1; \
	set->_copyValue = FN_CPY_VAL; \
	set->_cmpValue  = FN_CMP_VAL; \
	set->_freeValue = FN_FREE_VAL; \
	set->_print     = FN_PRINT_VAL; \
	return set; \
}

#define IMPLEMENT_SET_FN_FREE(SET) \
void SET ## _free(SET * set) \
{ \
	SET ## _elem_t * it = NULL; \
	if(set == NULL) return; \
	for(it = set->begin ; it != NULL ; it = it->next) \
	{ \
		if(it->prev) free(it->prev); \
		if(set->freeValue) set->_freeValue(it->value); \
	} \
	free(set); \
}

#define IMPLEMENT_SET_FN_ADD_STRUCT(SET, Valuetype) \
SET ## _elem_t * SET ## _add(SET * set, Valuetype value) \
{ \
	SET ## _elem_t * elem = NULL; \
	/* Test if set is NULL */\
	if(set == NULL) \
		return NULL; \
	/* Test if value exists */\
	elem = SET ## _get(set, value);\
	if(elem != NULL) \
	{ \
		if(set->freeValue) set->_freeValue(elem->value); \
		set->_copyValue(&(elem->value), &(value)); \
		return elem; \
	} \
	/* Create the element */\
	elem = malloc(set->elemSize); \
	elem->prev = NULL; \
	elem->next = NULL; \
	set->_copyValue(&(elem->value), &(value)); \
	/* Insert the element */\
	set->size++; \
	if(set->begin == NULL) \
	{ \
		set->begin = elem; \
	} \
	else if(set->end != NULL) \
	{ \
		set->end->next = elem; \
		elem->prev = set->end; \
	} \
	set->end = elem; \
	return elem; \
}


#define IMPLEMENT_SET_FN_REMOVE_STRUCT(SET, ValueType) \
SET * SET ## _remove(SET * set, ValueType value) \
{ \
	SET ## _elem_t * elem = SET ## _get(set, value); \
	/* Check Empty set */\
	if(set == NULL) return NULL; \
	if(elem != NULL) \
	{ \
		if(set->freeValue) set->_freeValue(elem->value); \
		elem->prev->next = elem->next; \
		elem->next->prev = elem->prev; \
		free(elem); \
		set->size--; \
	} \
	return set; \
}


#define IMPLEMENT_SET_FN_GET_STRUCT(SET, ValueType) \
SET ## _elem_t * SET ## _get(SET * set, ValueType value) \
{ \
	SET ## _elem_t * out = NULL; \
	SET ## _elem_t * it = NULL;  \
	/* Check empty set */ \
	if(set == NULL)        return NULL; \
	if(set->begin == NULL) return NULL; \
	/* Start search */ \
	it = set->begin; \
	while(it != NULL) \
	{ \
		if(set->_cmpValue(it->value, value) == 0) \
		{ \
			out = it; \
			it  = NULL; \
		} \
		else \
			it = it->next; \
	} \
	return out; \
}


#define IMPLEMENT_SET_FN_SEARCH_STRUCT(SET, Valuetype) \
SET ## _elem_t * SET ## _search(SET * set, Valuetype search) \
{ \
	SET ## _elem_t * out = NULL; \
	SET ## _elem_t * it = NULL; \
	/* Check empty set */ \
	if(set == NULL)        return NULL; \
	if(set->begin == NULL) return NULL; \
	/* Start search */ \
	it = set->begin; \
	while(it != NULL) \
	{ \
		if(set->_cmpValue(it->value, search) == 0) \
		{ \
			out = it; \
			it = NULL; \
		} \
		else \
			it = it->next; \
	} \
	return out; \
}

#ifdef CCONTAINERS_DISABLE_PRINT
#define IMPLEMENT_SET_FN_PRINT(SET) \
void SET ## _print(SET * set) \
{ \
	(void)(list); \
}
#else
#define IMPLEMENT_SET_FN_PRINT(SET) \
void SET ## _print(SET * set) \
{ \
	SET ## _elem_t * it = NULL; \
	printf("["); \
	it = set->begin; \
	for(it = set->begin ; it != NULL ; it = it->next) \
	{ \
		set->_print(it->value); \
		if(it->next != NULL) \
			printf(", "); \
	} \
	printf("]\n"); \
}
#endif

// MACRO HELPERS (One line definitions && implementations)
#define NEW_SET_DEFINITION(SET, VALUETYPE) \
NEW_SET_TYPE(SET, VALUETYPE); \
SET_FN_NEW(SET); \
SET_FN_FREE(SET); \
SET_FN_ADD_STRUCT(SET, VALUETYPE); \
SET_FN_REMOVE_STRUCT(SET, VALUETYPE); \
SET_FN_GET_STRUCT(SET, VALUETYPE); \
SET_FN_SEARCH_STRUCT(SET, VALUETYPE); \
SET_FN_PRINT_STRUCT(SET)

#define IMPLEMENT_SET(SET, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, FN_PRINT_VAL) \
IMPLEMENT_SET_FN_NEW(SET, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, FN_PRINT_VAL); \
IMPLEMENT_SET_FN_FREE(SET); \
IMPLEMENT_SET_FN_ADD_STRUCT(SET, VALUETYPE); \
IMPLEMENT_SET_FN_REMOVE_STRUCT(SET, VALUETYPE); \
IMPLEMENT_SET_FN_GET_STRUCT(SET, VALUETYPE); \
IMPLEMENT_SET_FN_SEARCH_STRUCT(SET, VALUETYPE); \
IMPLEMENT_SET_FN_PRINT(SET)


#ifdef __cplusplus
}
#endif

#endif // __SET_H__
