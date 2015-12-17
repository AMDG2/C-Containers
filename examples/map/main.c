/**
 * @file main.c
 * @brief Main example file
 * @author Baudouin FEILDEL
 */
#include <stdio.h>

#include "../../src/map.h"
#include "../../src/helpers.h"

NEW_MAP_DEFINITION(AgeMap, int, char *);

#define AGE_MAX 80

int main(int argc, char ** argv)
{
	// **Always** initialize your pointers to NULL
	AgeMap    * ages   = NULL;
	AgeMap_elem_t    * agesIt   = NULL;

    int   sum = 0;
    float avg = 0;

    printf("--- Map (ages) ---\n");
	ages  = AgeMap_new();

    AgeMap_add(ages, "Paul", rand() % AGE_MAX);
    AgeMap_add(ages, "Mary", rand() % AGE_MAX);
    AgeMap_add(ages, "John", rand() % AGE_MAX);
    AgeMap_add(ages, "Yo", rand() % AGE_MAX);
    AgeMap_add(ages, "Georges", rand() % AGE_MAX);
    AgeMap_add(ages, "Harrison", rand() % AGE_MAX);
    AgeMap_add(ages, "Erwan", rand() % AGE_MAX);

    for(agesIt = ages->begin ; agesIt != NULL ; agesIt = agesIt->next)
    {
        printf("%s is %d years old\n", agesIt->index, agesIt->value);
        sum += agesIt->value;
    }

    avg = sum/ages->size;
    printf("Average age: %.2f\n", avg);

    AgeMap_free(ages);

	return 0;
}

IMPLEMENT_MAP(AgeMap, int, char *, Int_copy, Str_copy, Int_cmp, Str_cmp, Int_free, Str_free);
