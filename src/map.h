/**
 * @file map.h
 * @brief Map container definition
 * @author Baudouin FEILDEL
 */
#ifndef __MAP_H__
#define __MAP_H__

#include <stdlib.h>

// =============
//  Definitions
// =============
#define NEW_MAP_ELEM(ElemTypename, Valuetype, Indextype) \
typedef struct _ ## ElemTypename \
{ \
	Valuetype value; \
	Indextype index; \
	struct _ ## ElemTypename * next; \
	struct _ ## ElemTypename * prev; \
} ElemTypename

#define NEW_MAP_TYPE(MAP, Valuetype, Indextype) \
NEW_MAP_ELEM(MAP ## _elem_t, Valuetype, Indextype); \
typedef struct MAP \
{ \
	MAP ## _elem_t * begin; \
	MAP ## _elem_t * end; \
	int    size; \
	size_t elemSize; \
	int    freeValue; \
	int    freeIndex; \
	void (*_copyValue)(Valuetype * dest, Valuetype * src); \
	void (*_copyIndex)(Indextype * dest, Indextype * src); \
	int (*_cmpValue)(Valuetype val1, Valuetype val2); \
	int (*_cmpIndex)(Indextype val1, Indextype val2); \
	void (*_freeValue)(Valuetype value); \
	void (*_freeIndex)(Indextype index); \
} MAP

#define MAP_FN_NEW(MAP) \
MAP * MAP ## _new()

#define MAP_FN_FREE(MAP) \
void MAP ## _free(MAP * map)

#define MAP_FN_ADD_STRUCT(MAP, Valuetype, Indextype) \
MAP ## _elem_t * MAP ## _add(MAP * map, Indextype index, Valuetype value)

#define MAP_FN_REMOVE_STRUCT(MAP, Indextype) \
MAP * MAP ## _remove(MAP * map, Indextype index)

#define MAP_FN_GET_STRUCT(MAP, Indextype) \
MAP ## _elem_t * MAP ## _get(MAP * map, Indextype index)

#define MAP_FN_SEARCH_STRUCT(MAP, Valuetype) \
MAP ## _elem_t * MAP ## _search(MAP * map, Valuetype search)

//#define MAP_FN_GET_PREVIOUS(MAP, Indextype) \
//MAP ## _elem_t MAP ## _find_previous(MAP * map, Indextype index)

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
			out == it; \
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

#endif // __MAP_H__
