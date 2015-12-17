/**
 * @file map.h
 * @brief Map container definition
 * @author Baudouin FEILDEL
 */
#ifndef __MAP_H__
#define __MAP_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// =============
//  Definitions
// =============
#define NEW_MAP_ELEM(MAP, ElemTypename, Valuetype, Indextype) \
/**
 Iterator to an element of a MAP object
 */ \
typedef struct _ ## ElemTypename \
{ \
	Valuetype value; /**< Value of the element */\
	Indextype index; /**< Index of the element */\
	struct _ ## ElemTypename * next; /**< Pointer to the next element in the map */\
	struct _ ## ElemTypename * prev; /**< Pointer to the previous element in the map */\
} ElemTypename

#define NEW_MAP_TYPE(MAP, Valuetype, Indextype) \
NEW_MAP_ELEM(MAP, MAP ## _elem_t, Valuetype, Indextype); \
typedef struct MAP \
{ \
	MAP ## _elem_t * begin; /**< Beginning of the map */\
	MAP ## _elem_t * end;   /**< End of the map */\
	int    size; /**< Map size */\
	size_t elemSize; /**< Size of one element in the map */\
	int    freeValue; /**< Flag:<br>1: Automatically free the value<br>0: Do not automatically free the value */\
	int    freeIndex; /**< Flag:<br>1: Automatically free the index<br>0: Do not automatically free the index */\
	void (*_copyValue)(Valuetype * dest, Valuetype * src); /**< Pointer to a function used to copy a value */\
	void (*_copyIndex)(Indextype * dest, Indextype * src); /**< Pointer to a function used to copy an index */\
	int (*_cmpValue)(Valuetype val1, Valuetype val2); /**< Pointer to a function used to compare two values */\
	int (*_cmpIndex)(Indextype val1, Indextype val2); /**< Pointer to a function used to compare two indexes */\
	void (*_freeValue)(Valuetype value); /**< Pointer to a function used to free a value */\
	void (*_freeIndex)(Indextype index); /**< Pointer to a function used to free an index */\
} MAP

#define MAP_FN_NEW(MAP) \
/**
 @brief Create a new MAP object
 @return A pointer to an allocated and initialized
 MAP object in memory
 */ \
MAP * MAP ## _new()

#define MAP_FN_FREE(MAP) \
/**
 Destroy a MAP object
 @param map A pointer to a MAP object
 */ \
void MAP ## _free(MAP * map)

#define MAP_FN_ADD_STRUCT(MAP, Valuetype, Indextype) \
/**
 Add an element to the map
 @details If an element already have this index
 its value will be updated.
 
 @param map   The map to use
 @param index The index of the element to add
 @param value The value to set
 @return      Return an iterator to the added element
 */ \
MAP ## _elem_t * MAP ## _add(MAP * map, Indextype index, Valuetype value)

#define MAP_FN_REMOVE_STRUCT(MAP, Indextype) \
/**
 Remove an element from the map
 @param map   A pointer to a valid MAP object
 @param index The index of the element to remove
 @return      The pointer to the MAP object
 */ \
MAP * MAP ## _remove(MAP * map, Indextype index)

#define MAP_FN_GET_STRUCT(MAP, Indextype) \
/**
 Get an iterator to an element from a MAP
 @param map   A pointer to a valid MAP object
 @param index The index of the element to get
 @return      Iterator to the element if present. NULL otherwise
 */ \
MAP ## _elem_t * MAP ## _get(MAP * map, Indextype index)

#define MAP_FN_SEARCH_STRUCT(MAP, Valuetype) \
/**
 Search for an element in map
 @param map    A pointer to a valid MAP object
 @param search The element to search in the map. Must be a valid ValueType object
 @return       Iterator to the element if found. NULL otherwise
 */ \
MAP ## _elem_t * MAP ## _search(MAP * map, Valuetype search)

/*
#define MAP_FN_GET_PREVIOUS(MAP, Indextype) \
MAP ## _elem_t MAP ## _find_previous(MAP * map, Indextype index)
 */

// =================
//  Implementations
// =================
#define IMPLEMENT_MAP_FN_NEW(MAP, Valuetype, Indextype, FN_CPY_VAL, FN_CPY_IDX, FN_CMP_VAL, FN_CMP_IDX, FN_FREE_VAL, FN_FREE_IDX) \
MAP * MAP ## _new() \
{ \
	MAP * map = malloc(sizeof(MAP)); \
	map->size  = 0; \
	map->begin = NULL; \
	map->end   = NULL; \
	map->elemSize   = sizeof(MAP ## _elem_t); \
	map->freeValue  = 1; \
	map->freeIndex  = 1; \
	map->_copyValue = FN_CPY_VAL; \
	map->_copyIndex = FN_CPY_IDX; \
	map->_cmpValue  = FN_CMP_VAL; \
	map->_cmpIndex  = FN_CMP_IDX; \
	map->_freeValue = FN_FREE_VAL; \
	map->_freeIndex = FN_FREE_IDX; \
	return map; \
}

#define IMPLEMENT_MAP_FN_FREE(MAP) \
void MAP ## _free(MAP * map) \
{ \
	MAP ## _elem_t * it; \
	if(map == NULL) return; \
	for(it = map->begin ; it != NULL ; it = it->next) \
	{ \
		if(it->prev) free(it->prev); \
		if(map->freeValue) map->_freeValue(it->value); \
		if(map->freeIndex) map->_freeIndex(it->index); \
	} \
	free(map); \
}

#define IMPLEMENT_MAP_FN_ADD_STRUCT(MAP, Valuetype, Indextype) \
MAP ## _elem_t * MAP ## _add(MAP * map, Indextype index, Valuetype value) \
{ \
	MAP ## _elem_t * elem = NULL; \
	/* Test if map is NULL */\
	if(map == NULL) \
		return NULL; \
	/* Test if index exists */\
	elem = MAP ## _get(map, index);\
	if(elem != NULL) \
		return elem; \
	/* Create the element */\
	elem = malloc(map->elemSize); \
	elem->prev = NULL; \
	elem->next = NULL; \
	map->_copyIndex(&(elem->index), &(index)); \
	map->_copyValue(&(elem->value), &(value)); \
	/* Insert the element */\
	map->size++; \
	if(map->begin == NULL) \
	{ \
		map->begin = elem; \
		map->end   = elem; \
	} \
	else \
	{ \
		map->end->next = elem; \
		elem->prev = map->end; \
		map->end = elem; \
	} \
	return elem; \
}


#define IMPLEMENT_MAP_FN_REMOVE_STRUCT(MAP, Indextype) \
MAP * MAP ## _remove(MAP * map, Indextype index) \
{ \
	MAP ## _elem_t * elem = MAP ## _get(map, index); \
	if(elem != NULL) \
	{ \
		if(map->freeValue) map->_freeValue(elem->value); \
		if(map->freeIndex) map->_freeIndex(elem->index); \
		elem->prev->next = elem->next; \
		elem->next->prev = elem->prev; \
		free(elem); \
	} \
	map->size--; \
	return map; \
}


#define IMPLEMENT_MAP_FN_GET_STRUCT(MAP, Indextype) \
MAP ## _elem_t * MAP ## _get(MAP * map, Indextype index) \
{ \
	MAP ## _elem_t * out = NULL; \
	MAP ## _elem_t * it = NULL; \
	/* Check empty map */ \
	if(map == NULL)        return NULL; \
	if(map->begin == NULL) return NULL; \
	/* Start search */ \
	it = map->begin; \
	while(it != NULL) \
	{ \
		if(map->_cmpIndex(it->index, index) == 0) \
		{ \
			out = it; \
			it  = NULL; \
		} \
		else \
			it = it->next; \
	} \
	return out; \
}


#define IMPLEMENT_MAP_FN_SEARCH_STRUCT(MAP, Valuetype) \
MAP ## _elem_t * MAP ## _search(MAP * map, Valuetype search) \
{ \
	MAP ## _elem_t * out = NULL; \
	MAP ## _elem_t * it = NULL; \
	/* Check empty map */ \
	if(map == NULL)        return NULL; \
	if(map->begin == NULL) return NULL; \
	/* Start search */ \
	it = map->begin; \
	while(it != NULL) \
	{ \
		if(map->_cmpValue(it->value, search) == 0) \
		{ \
			out = it; \
			it = NULL; \
		} \
		else \
			it = it->next; \
	} \
	return out; \
}

// MACRO HELPERS (One line definitions && implementations)
#define NEW_MAP_DEFINITION(MAP, VALUETYPE, INDEXTYPE) \
NEW_MAP_TYPE(MAP, VALUETYPE, INDEXTYPE); \
MAP_FN_NEW(MAP); \
MAP_FN_FREE(MAP); \
MAP_FN_ADD_STRUCT(MAP, VALUETYPE, INDEXTYPE); \
MAP_FN_REMOVE_STRUCT(MAP, INDEXTYPE); \
MAP_FN_GET_STRUCT(MAP, INDEXTYPE); \
MAP_FN_SEARCH_STRUCT(MAP, VALUETYPE)

#define IMPLEMENT_MAP(MAP, VALUETYPE, INDEXTYPE, FN_CPY_VAL, FN_CPY_IDX, FN_CMP_VAL, FN_CMP_IDX, FN_FREE_VAL, FN_FREE_IDX) \
IMPLEMENT_MAP_FN_NEW(MAP, VALUETYPE, INDEXTYPE, FN_CPY_VAL, FN_CPY_IDX, FN_CMP_VAL, FN_CMP_IDX, FN_FREE_VAL, FN_FREE_IDX); \
IMPLEMENT_MAP_FN_FREE(MAP); \
IMPLEMENT_MAP_FN_ADD_STRUCT(MAP, VALUETYPE, INDEXTYPE); \
IMPLEMENT_MAP_FN_REMOVE_STRUCT(MAP, INDEXTYPE); \
IMPLEMENT_MAP_FN_GET_STRUCT(MAP, INDEXTYPE); \
IMPLEMENT_MAP_FN_SEARCH_STRUCT(MAP, VALUETYPE) \

#ifdef __cplusplus
}
#endif

#endif // __MAP_H__
