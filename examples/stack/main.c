/**
 * @file main.c
 * @brief Main example file
 * @author Baudouin FEILDEL
 */
#include <stdio.h>

#include "../../src/stack.h"
#include "../../src/helpers.h"

NEW_STACK_DEFINITION(MyStack, int);

int main(int argc, char ** argv)
{
    MyStack   * stack  = NULL;
    int i, tmp;

    printf("\n--- Stack (LIFO) ---\n");
    stack = MyStack_new();

    printf("Push: ");
    for(i = 0 ; i < 5 ; i++)
    {
        printf("%d, ", i);
        MyStack_push(stack, i);
    }

    printf("Pop:  ");
    while(stack->size > 0)
    {
        tmp = MyStack_pop(stack);
        printf("%d, ", tmp);
    }
    printf("\n");

    MyStack_free(stack);

	return 0;
}

IMPLEMENT_STACK(MyStack, int, Int_copy, Int_cmp, Int_free, 0);
