/**
 * @file stack.h
 * @brief Stack container definition
 * @author Baudouin FEILDEL
 */
#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// =============
//  Definitions
// =============
#define NEW_STACK_ELEM(STACK, ElemTypename, Valuetype) \
/**
 Iterator to an element of a STACK object
 */ \
typedef struct _ ## ElemTypename \
{ \
	Valuetype    value; /**< Value of the element */\
	unsigned int index; /**< Index of the element */\
	struct _ ## ElemTypename * next; /**< Pointer to the next element in the stack */\
} ElemTypename

#define NEW_STACK_TYPE(STACK, Valuetype) \
NEW_STACK_ELEM(STACK, STACK ## _elem_t, Valuetype); \
typedef struct STACK \
{ \
	STACK ## _elem_t * top; /**< Top of the stack */\
	int    size;            /**< Stack size */\
	size_t elemSize;        /**< Size of one element in the stack */\
	int    freeValue;       /**< Flag:<br>1: Automatically free the value<br>0: Do not automatically free the value */\
	void (*_copyValue) (Valuetype * dest, Valuetype * src); /**< Pointer to a function used to copy a value */\
	int  (*_cmpValue)  (Valuetype val1, Valuetype val2);    /**< Pointer to a function used to compare two values */\
	void (*_freeValue) (Valuetype value);                   /**< Pointer to a function used to free a value */\
} STACK

#define STACK_FN_NEW(STACK) \
/**
 @brief Create a new STACK object
 @return A pointer to an allocated and initialized STACK object in memory
 */ \
STACK * STACK ## _new()

#define STACK_FN_FREE(STACK) \
/**
 Destroy a STACK object
 @param stack A pointer to a STACK object
 */ \
void STACK ## _free(STACK * stack)

#define STACK_FN_PUSH_STRUCT(STACK, ValueType) \
/**
 Push an element to the stack
 @param stack  The stack to use
 @param value The value to set
 */ \
void STACK ## _push(STACK * stack, ValueType value)

#define STACK_FN_POP_STRUCT(STACK, ValueType) \
/**
 Remove an element from the stack
 @param stack  A pointer to a valid STACK object
 @return       The pointer to the STACK object
 */ \
ValueType STACK ## _pop(STACK * stack)

#define STACK_FN_PEEK_STRUCT(STACK, ValueType) \
/**
 Get the value on top of the stack
 @param stack  A pointer to a valid STACK object
 @return       Iterator to the element if present. NULL otherwise
 */ \
ValueType STACK ## _peek(STACK * stack)

#define STACK_FN_CLEAR_STRUCT(STACK) \
/**
 Clear the stack
 @param stack A pointer to a valid STACK object
 */ \
void STACK ## _clear(STACK * stack)

// =================
//  Implementations
// =================
#define IMPLEMENT_STACK_FN_NEW(STACK, Valuetype, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL) \
STACK * STACK ## _new() \
{ \
	STACK * stack = malloc(sizeof(STACK)); \
	stack->size  = 0; \
	stack->top   = NULL; \
	stack->elemSize   = sizeof(STACK ## _elem_t); \
	stack->freeValue  = 1; \
	stack->_copyValue = FN_CPY_VAL; \
	stack->_cmpValue  = FN_CMP_VAL; \
	stack->_freeValue = FN_FREE_VAL; \
	return stack; \
}

#define IMPLEMENT_STACK_FN_FREE(STACK) \
void STACK ## _free(STACK * stack) \
{ \
	STACK ## _elem_t * it = NULL; \
	if(stack == NULL) return; \
	while(stack->top != NULL) \
	{ \
		it = stack->top; \
		if(stack->freeValue) \
			stack->_freeValue(it->value); \
		stack->top = it->next; \
		free(it); \
	} \
}

#define IMPLEMENT_STACK_FN_PUSH_STRUCT(STACK, Valuetype) \
void STACK ## _push(STACK * stack, Valuetype value) \
{ \
	STACK ## _elem_t * elem = NULL; \
	/* Test if stack is NULL */\
	if(stack == NULL) \
		return; \
	/* Create the element */\
	elem = malloc(stack->elemSize); \
	elem->next = stack->top; \
	stack->_copyValue(&(elem->value), &(value)); \
	/* Insert the element */\
	stack->size++; \
	stack->top = elem; \
}


#define IMPLEMENT_STACK_FN_POP_STRUCT(STACK, ValueType, DEFAULT_VALUE) \
ValueType STACK ## _pop(STACK * stack) \
{ \
	STACK ## _elem_t * elem = NULL; \
	ValueType value = DEFAULT_VALUE; \
	/* Check Empty stack */\
	if(stack == NULL) \
		return DEFAULT_VALUE; \
	elem = stack->top; \
	if(elem != NULL) \
	{ \
		stack->top = elem->next; \
		stack->size--; \
		stack->_copyValue(&(value), &(elem->value)); \
		free(elem); \
	} \
	return value; \
}


#define IMPLEMENT_STACK_FN_PEEK_STRUCT(STACK, ValueType, DEFAULT_VALUE) \
ValueType STACK ## _PEEK(STACK * stack) \
{ \
	if(stack == NULL) return DEFAULT_VALUE; \
	if(stack->top != NULL) \
		return stack->top->value; \
	return DEFAULT_VALUE; \
}

// MACRO HELPERS (One line definitions && implementations)
#define NEW_STACK_DEFINITION(STACK, VALUETYPE) \
NEW_STACK_TYPE(STACK, VALUETYPE); \
STACK_FN_NEW(STACK); \
STACK_FN_FREE(STACK); \
STACK_FN_PUSH_STRUCT(STACK, VALUETYPE); \
STACK_FN_POP_STRUCT(STACK, VALUETYPE); \
STACK_FN_PEEK_STRUCT(STACK, VALUETYPE)

#define IMPLEMENT_STACK(STACK, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, DEFAULT_VALUE) \
IMPLEMENT_STACK_FN_NEW(STACK, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL); \
IMPLEMENT_STACK_FN_FREE(STACK); \
IMPLEMENT_STACK_FN_PUSH_STRUCT(STACK, VALUETYPE); \
IMPLEMENT_STACK_FN_POP_STRUCT(STACK, VALUETYPE, DEFAULT_VALUE); \
IMPLEMENT_STACK_FN_PEEK_STRUCT(STACK, VALUETYPE, DEFAULT_VALUE)

#ifdef __cplusplus
}
#endif

#endif // __STACK_H__
