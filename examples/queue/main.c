/**
 * @file main.c
 * @brief Main example file
 * @author Baudouin FEILDEL
 */
#include <stdio.h>

#include "../../src/queue.h"
#include "../../src/helpers.h"

NEW_QUEUE_DEFINITION(MyQueue, int);

int main(int argc, char ** argv)
{
    MyQueue   * queue  = NULL;
    int i = 0, tmp = 0;

    printf("--- Queue (FIFO) ---\n");
    queue = MyQueue_new();

    printf("Enqueue: ");
    for(i = 0 ; i < 5 ; i++)
    {
        printf("%d, ", i);
        MyQueue_enqueue(queue, i);
    }

    printf("Dequeue: ");
    while(queue->size > 0)
    {
        tmp = MyQueue_dequeue(queue);
        printf("%d, ", tmp);
    }
    printf("\n");

    MyQueue_free(queue);

	return 0;
}

IMPLEMENT_QUEUE(MyQueue, int, Int_copy, Int_cmp, Int_free, 0);
