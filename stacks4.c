#include <stdio.h>
#include "liblists.h"

struct queue_from_stacks {
    struct node *stack_A;
    struct node *stack_B;
    int items;
};

void print_q(struct queue_from_stacks *q)
{
    if (q->stack_A->next != NULL) {
        print_list(q->stack_A);
    } else if (q->stack_B->next != NULL) {
        while (q->stack_B->next != NULL) {
            prepend(q->stack_A, pop(q->stack_B));
        }
        print_list(q->stack_A);
    } else {
        printf("queue is empty");
    }
    printf("\n");
}

void q_push(struct queue_from_stacks *q, int value)
{
    // the queue is empty or the last operation was q_push(),
    // or print_q(), so just push the value onto stack_A
    if (q->items == 0 || q->stack_A->next != NULL) {
        prepend(q->stack_A, value);
    // the queue is not empty and the last operation was q_pop()
    // so transfer everything to stack_A before pushing the value
    } else if (q->items > 0 && q->stack_A->next == NULL) {
        while (q->stack_B->next != NULL) {
            prepend(q->stack_A, pop(q->stack_B));
        }
        prepend(q->stack_A, value);
    }
    q->items++;
}

int q_pop(struct queue_from_stacks *q)
{
    // the queue is not empty and the last operation was q_pop(),
    // so just pop from stack_B
    if (q->items > 0 && q->stack_B->next != NULL) {
        q->items--;
        return pop(q->stack_B);
    // the queue is not empty and the last operation was q_push()
    // so transfer everything to stack_B before popping the value
    } else if (q->items > 0 && q->stack_A->next != NULL) {
        while (q->stack_A->next != NULL) {
            prepend(q->stack_B, pop(q->stack_A));
        }
        q->items--;
        return pop(q->stack_B);
    } else if (q->items == 0) {
        printf("queue is empty");
    }
    return 2^32;
}

void test_q(struct queue_from_stacks *q)
{
    q_push(q, 1);
    q_push(q, 2);
    q_push(q, 3);
    print_q(q);
    q_pop(q);
    q_pop(q);
    print_q(q);
    q_push(q, 4);
    q_push(q, 5);
    print_q(q);
    q_pop(q);
    print_q(q);
}

int main()
{
    // initialize queue of stacks
    struct queue_from_stacks q;
    q.stack_A = malloc(sizeof(struct node));
    q.stack_A->next = NULL;
    q.stack_B = malloc(sizeof(struct node));
    q.stack_B->next = NULL;
    q.items = 0;

    // run test
    test_q(&q);

    return 0;
}
