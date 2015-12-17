/**
 * @file main.c
 * @brief Main example file
 * @author Baudouin FEILDEL
 */
#include <stdio.h>

#include "../../src/list.h"
#include "../../src/helpers.h"

NEW_LIST_DEFINITION(MyList, int);

#define RANDOM_MAX 10000

int main(int argc, char ** argv)
{
	MyList * list = NULL;
	MyList_elem_t * it = NULL;

    int   sum = 0;
    float avg = 0;

    printf("--- List ---\n");
	list = MyList_new();

	MyList_add(list, 0, rand() % RANDOM_MAX);
	MyList_add(list, 1, rand() % RANDOM_MAX);
	MyList_add(list, 2, rand() % RANDOM_MAX);
	MyList_add(list, 3, rand() % RANDOM_MAX);
	MyList_add(list, 4, rand() % RANDOM_MAX);
	MyList_add(list, 5, rand() % RANDOM_MAX);

    sum = 0;
    avg = 0;

    printf("List: ");
    MyList_print(list);
    
    for(it = list->begin ; it != NULL ; it = it->next)
        sum += it->value;

    avg = sum/list->size;
    printf("Average value: %.2f\n", avg);

    MyList_free(list);

	return 0;
}

IMPLEMENT_LIST(MyList, int, Int_copy, Int_cmp, Int_free, Int_print);