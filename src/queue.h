/**
 * @file queue.h
 * @brief List container definition
 * @author Baudouin FEILDEL
 */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// =============
//  Definitions
// =============
#define NEW_QUEUE_ELEM(QUEUE, ElemTypename, Valuetype) \
/**
 Iterator to an element of a QUEUE object
 */ \
typedef struct _ ## ElemTypename \
{ \
	Valuetype    value; /**< Value of the element */\
	unsigned int index; /**< Index of the element */\
	struct _ ## ElemTypename * previous; /**< Pointer to the previous element in the queue */\
} ElemTypename

#define NEW_QUEUE_TYPE(QUEUE, Valuetype) \
NEW_QUEUE_ELEM(QUEUE, QUEUE ## _elem_t, Valuetype); \
typedef struct QUEUE \
{ \
	QUEUE ## _elem_t * head;  /**< head of the queue */\
	QUEUE ## _elem_t * queue; /**< queue of the queue */\
	int    size;              /**< List size */\
	size_t elemSize;          /**< Size of one element in the queue */\
	int    freeValue;         /**< Flag:<br>1: Automatically free the value<br>0: Do not automatically free the value */\
	void (*_copyValue) (Valuetype * dest, Valuetype * src); /**< Pointer to a function used to copy a value */\
	int  (*_cmpValue)  (Valuetype val1, Valuetype val2);    /**< Pointer to a function used to compare two values */\
	void (*_freeValue) (Valuetype value);                   /**< Pointer to a function used to free a value */\
} QUEUE

#define QUEUE_FN_NEW(QUEUE) \
/**
 @brief Create a new QUEUE object
 @return A pointer to an allocated and initialized
 QUEUE object in memory
 */ \
QUEUE * QUEUE ## _new()

#define QUEUE_FN_FREE(QUEUE) \
/**
 Destroy a QUEUE object
 @param queue A pointer to a QUEUE object
 */ \
void QUEUE ## _free(QUEUE * queue)

#define QUEUE_FN_ENQUEUE_STRUCT(QUEUE, ValueType) \
/**
 Add an element to the queue
 @details If an element already have this index
 its value will be updated.

 @param queue  The queue to use
 @param value The value to set
 @return      Return an iterator to the added element
 */ \
QUEUE ## _elem_t * QUEUE ## _enqueue(QUEUE * queue, ValueType value)

#define QUEUE_FN_DEQUEUE_STRUCT(QUEUE, ValueType) \
/**
 Remove an element from the queue
 @param queue  A pointer to a valid QUEUE object
 @param index The index of the element to remove
 @return      The pointer to the QUEUE object
 */ \
ValueType QUEUE ## _DEQUEUE(QUEUE * queue)

#define QUEUE_FN_HEAD_STRUCT(QUEUE, ValueType) \
/**
 Get an iterator to an element from a queue
 @param queue  A pointer to a valid QUEUE object
 @param index The index of the element to get
 @return      Iterator to the element if present. NULL otherwise
 */ \
ValueType QUEUE ## _head(QUEUE * queue)

// =================
//  Implementations
// =================
#define IMPLEMENT_QUEUE_FN_NEW(QUEUE, Valuetype, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL) \
QUEUE * QUEUE ## _new() \
{ \
	QUEUE * queue = malloc(sizeof(QUEUE)); \
	queue->size  = 0; \
	queue->head  = NULL; \
	queue->queue = NULL; \
	queue->elemSize   = sizeof(QUEUE ## _elem_t); \
	queue->freeValue  = 1; \
	queue->_copyValue = FN_CPY_VAL; \
	queue->_cmpValue  = FN_CMP_VAL; \
	queue->_freeValue = FN_FREE_VAL; \
	return queue; \
}

#define IMPLEMENT_QUEUE_FN_FREE(QUEUE) \
void QUEUE ## _free(QUEUE * queue) \
{ \
	QUEUE ## _elem_t * it = NULL; \
	if(queue == NULL) return; \
	while(queue->head != NULL) \
	{ \
		it = queue->head; \
		if(queue->freeValue) \
			queue->_freeValue(it->value); \
		queue->head = it->previous; \
		free(it); \
	} \
}

#define IMPLEMENT_QUEUE_FN_ENQUEUE_STRUCT(QUEUE, Valuetype) \
QUEUE ## _elem_t * QUEUE ## _enqueue(QUEUE * queue, Valuetype value) \
{ \
	QUEUE ## _elem_t * elem = NULL; \
	/* Test if queue is NULL */\
	if(queue == NULL) \
		return NULL; \
	/* Create the element */\
	elem = malloc(queue->elemSize); \
	elem->previous = NULL; \
	queue->_copyValue(&(elem->value), &(value)); \
	/* Insert the element */\
	queue->size++; \
	if(queue->queue != NULL) \
		queue->queue->previous = elem; \
	if(queue->head == NULL) \
		queue->head = elem; \
	queue->queue = elem; \
	return elem; \
}


#define IMPLEMENT_QUEUE_FN_DEQUEUE_STRUCT(QUEUE, ValueType, DEFAULT_VALUE) \
ValueType QUEUE ## _dequeue(QUEUE * queue) \
{ \
	QUEUE ## _elem_t * elem = NULL; \
	ValueType value = DEFAULT_VALUE; \
	/* Check Empty queue */\
	if(queue == NULL) \
		return DEFAULT_VALUE; \
	elem = queue->head; \
	if(elem != NULL) \
	{ \
		queue->head = elem->previous; \
		queue->size--; \
		queue->_copyValue(&(value), &(elem->value)); \
		free(elem); \
	} \
	return value; \
}


#define IMPLEMENT_QUEUE_FN_HEAD_STRUCT(QUEUE, ValueType, DEFAULT_VALUE) \
ValueType QUEUE ## _head(QUEUE * queue) \
{ \
	if(queue == NULL) return DEFAULT_VALUE; \
	if(queue->head != NULL) \
		return queue->head->value; \
	return DEFAULT_VALUE; \
}

// MACRO HELPERS (One line definitions && implementations)
#define NEW_QUEUE_DEFINITION(QUEUE, VALUETYPE) \
NEW_QUEUE_TYPE(QUEUE, VALUETYPE); \
QUEUE_FN_NEW(QUEUE); \
QUEUE_FN_FREE(QUEUE); \
QUEUE_FN_ENQUEUE_STRUCT(QUEUE, VALUETYPE); \
QUEUE_FN_DEQUEUE_STRUCT(QUEUE, VALUETYPE); \
QUEUE_FN_HEAD_STRUCT(QUEUE, VALUETYPE)

#define IMPLEMENT_QUEUE(QUEUE, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL, DEFAULT_VALUE) \
IMPLEMENT_QUEUE_FN_NEW(QUEUE, VALUETYPE, FN_CPY_VAL, FN_CMP_VAL, FN_FREE_VAL); \
IMPLEMENT_QUEUE_FN_FREE(QUEUE); \
IMPLEMENT_QUEUE_FN_ENQUEUE_STRUCT(QUEUE, VALUETYPE); \
IMPLEMENT_QUEUE_FN_DEQUEUE_STRUCT(QUEUE, VALUETYPE, DEFAULT_VALUE); \
IMPLEMENT_QUEUE_FN_HEAD_STRUCT(QUEUE, VALUETYPE, DEFAULT_VALUE)

#ifdef __cplusplus
}
#endif

#endif // __QUEUE_H__
