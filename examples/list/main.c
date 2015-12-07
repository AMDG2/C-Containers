/**
 * @file main.c
 * @brief Main example file
 * @author Baudouin FEILDEL
 */
#include <stdio.h>

#include "../../src/list.h"
#include "../../src/helpers.h"

NEW_LIST_DEFINITION(ScoreList, int);

int main(int argc, char ** argv)
{
	ScoreList * scores = NULL;
	ScoreList_elem_t * scoresIt = NULL;

    int   sum = 0;
    float avg = 0;

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

	return 0;
}

IMPLEMENT_LIST(ScoreList, int, Int_copy, Int_cmp, Int_free);