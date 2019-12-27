#include <stdio.h>
#include "liblists.h"

void min_stack_push(struct node *primary_stack, struct node *min_stack, int *current_min, int value)
{
    if (value > *current_min){
        prepend(primary_stack, value);
    } else if (value <= *current_min) {
        prepend(primary_stack, value);
        prepend(min_stack, value);
        *current_min = value;
    }
}

int min_stack_pop(struct node *primary_stack, struct node *min_stack, int *current_min)
{
    int value = -1;
    // discard any value that has been "removed" by a previous call to min_stack_min()
    // NOT DONE: handle the case of multiple entries of the same value... getting one with
    // min() should not cause all others to get discarded... they should become the new min
    while (value < *current_min){
        value = pop(primary_stack);
    }
    if (value > *current_min){
        return value;
    } else if (value == *current_min) {
        // remove old min
        pop(min_stack);
        // get new min, update min, push it back on
        int temp = pop(min_stack);
        *current_min = temp;
        prepend(min_stack, temp);
        return value;
    }
    return -1;
}

int min_stack_min(struct node *primary_stack, struct node *min_stack, int *current_min)
{
    if (min_stack->next == NULL) {
        return -1;
    } else {
        int value = pop(min_stack);
        // get new min, update min, push it back on
        if (min_stack->next == NULL) {
            *current_min = 2^32;
        } else {
            int temp = pop(min_stack);
            *current_min = temp;
            prepend(min_stack, temp);
        }
            return value;
    }
}

void test_min_stack(struct node *primary_stack, struct node *min_stack, int *current_min)
{
    min_stack_push(primary_stack, min_stack, current_min, 5);
    min_stack_push(primary_stack, min_stack, current_min, 2);
    min_stack_push(primary_stack, min_stack, current_min, 8);
    printf("%d\n", min_stack_min(primary_stack, min_stack, current_min));
    printf("%d\n", min_stack_min(primary_stack, min_stack, current_min));
    print_list(primary_stack);
}

int main(void)
{
    // initialize stack
    struct node primary_stack;
    primary_stack.next = NULL;
    struct node min_stack;
    min_stack.next = NULL;
    int current_min = 2^32;

    // run test routine
    test_min_stack(&primary_stack, &min_stack, &current_min);
}
