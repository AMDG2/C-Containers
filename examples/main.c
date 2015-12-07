/**
 * @file main.c
 * @brief Main example file
 * @author Baudouin FEILDEL
 */
#include <stdio.h>

#include "../src/list.h"
#include "../src/map.h"
#include "../src/pile.h"
#include "../src/queue.h"

#include "../src/helpers.h"

NEW_MAP_DEFINITION(AgeMap, int, char *);
NEW_LIST_DEFINITION(ScoreList, int);
NEW_PILE_DEFINITION(MonTypePile, int);
NEW_QUEUE_DEFINITION(MonTypeQueue, int);

int main(int argc, char ** argv)
{
	// **Always** initialize your pointers to NULL
	AgeMap       * ages   = NULL;
	ScoreList    * scores = NULL;
    MonTypePile  * pile = NULL;
    MonTypeQueue * file = NULL;

	AgeMap_elem_t    * agesIt  = NULL;
	ScoreList_elem_t * scoresIt = NULL;

    int   sum = 0, i = 0, tmp = 0;
    float avg = 0;

    /*
    printf("--- Ages ---\n");
	ages  = AgeMap_new();

    AgeMap_add(ages, "Paul", 12);
    AgeMap_add(ages, "Mary", 15);
    AgeMap_add(ages, "John", 8);
    AgeMap_add(ages, "Yo", 16);
    AgeMap_add(ages, "Georges", 18);
    AgeMap_add(ages, "Harrison", 6);
    AgeMap_add(ages, "Erwan", 11);

    for(agesIt = ages->begin ; agesIt != NULL ; agesIt = agesIt->next)
    {
        printf("%s is %d years old\n", agesIt->index, agesIt->value);
        sum += agesIt->value;
    }

    avg = sum/ages->size;
    printf("Average age: %.2f\n", avg);

    AgeMap_free(ages);
    // */

    //*
    printf("--- Scores ---\n");
	scores = ScoreList_new();

	ScoreList_add(scores, 0, 50);
	ScoreList_add(scores, 1, 20);
	ScoreList_add(scores, 2, 75);
	ScoreList_add(scores, 3, 35);
	ScoreList_add(scores, 4, 12);
	ScoreList_add(scores, 5, 97);

    sum = 0;
    avg = 0;

    printf("Score list: ");
    for(scoresIt = scores->begin ; scoresIt != NULL ; scoresIt = scoresIt->next)
    {
        printf("%d ", scoresIt->value);
        sum += scoresIt->value;
    }
    printf("\n");

    avg = sum/scores->size;
    printf("Average score: %.2f\n", avg);

    ScoreList_free(scores);
    // */

    //*
    printf("\n--- Pile (LIFO) ---\n");
    pile = MonTypePile_new();

    printf("Empiler: ");
    for(i = 0 ; i < 5 ; i++)
    {
        printf("%d, ", i);
        MonTypePile_push(pile, i);
    }

    printf("Dépiler: ");
    while(pile->size > 0)
    {
        tmp = MonTypePile_pop(pile);
        printf("%d, ", tmp);
    }
    printf("\n");
    // */

    //*
    printf("\n--- File (FIFO) ---\n");
    file = MonTypeQueue_new();

    printf("Enfiler: ");
    for(i = 0 ; i < 5 ; i++)
    {
        printf("%d, ", i);
        MonTypeQueue_enqueue(file, i);
    }

    printf("Défiler: ");
    while(file->size > 0)
    {
        tmp = MonTypeQueue_dequeue(file);
        printf("%d, ", tmp);
    }
    printf("\n");
    // */

	return 0;
}

IMPLEMENT_MAP(AgeMap, int, char *, Int_copy, Str_copy, Int_cmp, Str_cmp, Int_free, Str_free);
IMPLEMENT_LIST(ScoreList, int, Int_copy, Int_cmp, Int_free);
IMPLEMENT_PILE(MonTypePile, int, Int_copy, Int_cmp, Int_free, 0);
IMPLEMENT_QUEUE(MonTypeQueue, int, Int_copy, Int_cmp, Int_free, 0);
