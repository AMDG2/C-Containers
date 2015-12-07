/**
 * @file pile.h
 * @brief List container definition
 * @author Baudouin FEILDEL
 */
#ifndef __PILE_H__
#define __PILE_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// =============
//  Definitions
// =============
#define NEW_PILE_ELEM(PILE, ElemTypename, Valuetype) \
/**
 Iterator to an element of a PILE object
 */ \
typedef struct _ ## ElemTypename \
{ \
	Valuetype    value; /**< Value of the element */\
	unsigned int index; /**< Index of the element */\
	struct _ ## ElemTypename * next; /**< Pointer to the next element in the pile */\
} ElemTypename

#define NEW_PILE_TYPE(PILE, Valuetype) \
NEW_PILE_ELEM(PILE, PILE ## _elem_t, Valuetype); \
typedef struct PILE \
{ \
	PILE ## _elem_t * top; /**< top of the pile */\
	int    size; /**< List size */\
	size_t elemSize; /**< Size of one element in the pile */\
	int    freeValue; /**< Flag:<br>1: Automatically free the value<br>0: Do not automatically free the value */\
	void (*_copyValue) (Valuetype * dest, Valuetype * src); /**< Pointer to a function used to copy a value */\
	int  (*_cmpValue)  (Valuetype val1, Valuetype val2); /**< Pointer to a function used to compare two values */\
	void (*_freeValue) (Valuetype value); /**< Pointer to a function used to free a value */\
} PILE

#define PILE_FN_NEW(PILE) \
/**
 @brief Create a new PILE object
 @return A pointer to an allocated and initialized
 PILE object in memory
 */ \
PILE * PILE ## _new()

#define PILE_FN_FREE(PILE) \
/**
 Destroy a PILE object
 @param pile A pointer to a PILE object
 */ \
void PILE ## _free(PILE * pile)

#define PILE_FN_PUSH_STRUCT(PILE, ValueType) \
/**
 Add an element to the pile
 @details If an element already have this index
 its value will be updated.

 @param pile  The pile to use
 @param value The value to set
 @return      Return an iterator to the added element
 */ \
PILE ## _elem_t * PILE ## _push(PILE * pile, ValueType value)

#define PILE_FN_POP_STRUCT(PILE, ValueType) \
/**
 Remove an element from the pile
 @param pile  A pointer to a valid PILE object
 @param index The index of the element to remove
 @return      The pointer to the PILE object
 */ \
ValueType PILE ## _pop(PILE * pile)

#define PILE_FN_PEEK_STRUCT(PILE, ValueType) \
/**
 Get an iterator to an element from a pile
 @param pile  A pointer to a valid PILE object
 @param index The index of the element to get
 @return      Iterator to the element if present. NULL otherwise
 */ \
ValueType PILE ## _peek(PILE * pile)

// =================
//  Implementations
// =================
#define IMPLEMENT_PILE_FN_NEW(PILE, Valuetype, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL) \
PILE * PILE ## _new() \
{ \
	PILE * pile = malloc(sizeof(PILE)); \
	pile->size  = 0; \
	pile->top   = NULL; \
	pile->elemSize   = sizeof(PILE ## _elem_t); \
	pile->freeValue  = 1; \
	pile->_copyValue = FN_CPY_VAL; \
	pile->_cmpValue  = FN_CMP_VAL; \
	pile->_freeValue = FN_FREE_VAL; \
	return pile; \
}

#define IMPLEMENT_PILE_FN_FREE(PILE) \
void PILE ## _free(PILE * pile) \
{ \
	PILE ## _elem_t * it = NULL; \
	if(pile == NULL) return; \
	while(pile->top != NULL) \
	{ \
		it = pile->top; \
		if(pile->freeValue) \
			pile->_freeValue(it->value); \
		pile->top = it->next; \
		free(it); \
	} \
}

#define IMPLEMENT_PILE_FN_PUSH_STRUCT(PILE, Valuetype) \
PILE ## _elem_t * PILE ## _push(PILE * pile, Valuetype value) \
{ \
	PILE ## _elem_t * elem = NULL; \
	/* Test if pile is NULL */\
	if(pile == NULL) \
		return NULL; \
	/* Create the element */\
	elem = malloc(pile->elemSize); \
	elem->next = pile->top; \
	pile->_copyValue(&(elem->value), &(value)); \
	/* Insert the element */\
	pile->size++; \
	pile->top = elem; \
	return elem; \
}


#define IMPLEMENT_PILE_FN_POP_STRUCT(PILE, ValueType, DEFAULT_VALUE) \
ValueType PILE ## _pop(PILE * pile) \
{ \
	PILE ## _elem_t * elem = NULL; \
	ValueType value = DEFAULT_VALUE; \
	/* Check Empty pile */\
	if(pile == NULL) \
		return DEFAULT_VALUE; \
	elem = pile->top; \
	if(elem != NULL) \
	{ \
		pile->top = elem->next; \
		pile->size--; \
		pile->_copyValue(&(value), &(elem->value)); \
		free(elem); \
	} \
	return value; \
}


#define IMPLEMENT_PILE_FN_PEEK_STRUCT(PILE, ValueType, DEFAULT_VALUE) \
ValueType PILE ## _PEEK(PILE * pile) \
{ \
	if(pile == NULL) return DEFAULT_VALUE; \
	if(pile->top != NULL) \
		return pile->top->value; \
	return DEFAULT_VALUE; \
}

// MACRO HELPERS (One line definitions && implementations)
#define NEW_PILE_DEFINITION(PILE, VALUETYPE) \
NEW_PILE_TYPE(PILE, VALUETYPE); \
PILE_FN_NEW(PILE); \
PILE_FN_FREE(PILE); \
PILE_FN_PUSH_STRUCT(PILE, VALUETYPE); \
PILE_FN_POP_STRUCT(PILE, VALUETYPE); \
PILE_FN_PEEK_STRUCT(PILE, VALUETYPE)

#define IMPLEMENT_PILE(PILE, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, DEFAULT_VALUE) \
IMPLEMENT_PILE_FN_NEW(PILE, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL); \
IMPLEMENT_PILE_FN_FREE(PILE); \
IMPLEMENT_PILE_FN_PUSH_STRUCT(PILE, VALUETYPE); \
IMPLEMENT_PILE_FN_POP_STRUCT(PILE, VALUETYPE, DEFAULT_VALUE); \
IMPLEMENT_PILE_FN_PEEK_STRUCT(PILE, VALUETYPE, DEFAULT_VALUE)

#ifdef __cplusplus
}
#endif

#endif // __PILE_H__
