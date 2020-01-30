#include <stdio.h>
#include "liblists.h"

struct stack_list_node {
    struct node *stack;
    int stack_items;
    int stack_max;
    struct stack_list_node *next;
};

void print_stack_list(struct stack_list_node *list)
{
    struct stack_list_node *listp = list;
    while (listp->stack != NULL) {
        print_list(listp->stack);
        printf("\n");
        if (listp->next != NULL) {
            listp = listp->next;
        } else {
            printf("\n");
            break;
        }
    }
}

void stack_list_push(struct stack_list_node *list, int value)
{
    struct stack_list_node *listp = list;
    while (listp->stack_items == listp->stack_max) {
        listp = listp->next;
    }
    prepend(listp->stack, value);
    listp->stack_items++;
    if (listp->stack_items == listp->stack_max) {
        listp->next = malloc(sizeof(struct stack_list_node));
        listp->next->stack = malloc(sizeof(struct node));
        listp->next->stack->next = NULL;
        listp->next->stack_items = 0;
        listp->next->stack_max = listp->stack_max;
        listp->next->next = NULL;
    }
}

int stack_list_pop(struct stack_list_node *list)
{
    struct stack_list_node *listp = list;
    while (listp->stack_items == listp->stack_max &&
           listp->next->stack_items > 0) {
        listp = listp->next;
    }
    listp->stack_items--;
    return pop(listp->stack);
}

int stack_list_pop_at(struct stack_list_node *list, int index)
{
    struct stack_list_node *listp = list;
    int i = 1;
    while (listp->stack_items == listp->stack_max &&
           listp->next->stack_items > 0 &&
           i < index) {
        listp = listp->next;
        i++;
    }
    listp->stack_items--;
    return pop(listp->stack);
}

void test_stack_list(struct stack_list_node *list)
{
    stack_list_push(list, 1);
    stack_list_push(list, 2);
    stack_list_push(list, 3);
    stack_list_push(list, 4);
    stack_list_push(list, 5);
    stack_list_push(list, 6);
    stack_list_push(list, 7);
    print_stack_list(list);
    stack_list_pop_at(list, 2);
    stack_list_pop_at(list, 2);
    print_stack_list(list);
    stack_list_push(list, 8);
    print_stack_list(list);
}

int main()
{
    // initialize list of stacks
    struct stack_list_node list;
    list.stack = malloc(sizeof(struct node));
    list.stack->next = NULL;
    list.stack_items = 0;
    list.stack_max = 3;
    list.next = NULL;

    // run test
    test_stack_list(&list);

    return 0;
}
