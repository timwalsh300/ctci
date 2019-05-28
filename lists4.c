#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int value;
    struct node *next;
};

void append(struct node *list, int v)
{
    struct node *addition = malloc(sizeof(struct node));
    addition->value = v;
    addition->next = NULL;
    struct node *current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = addition;
}

void prepend(struct node *list, int v)
{
    struct node *addition = malloc(sizeof(struct node));
    addition->value = v;
    addition->next = list->next;
    list->next = addition;
}

void print_list(struct node *list)
{
    struct node *current = list;
    while (current->next != NULL) {
        current = current->next;
        printf("%d->", current->value);
    }
}

void partition_list(struct node *list, struct node *new_list, int pivot)
{
    struct node *current = list;
    while (current->next != NULL) {
        current = current->next;
        if (current->value < pivot) {
            prepend(new_list, current->value);
        } else {
            append(new_list, current->value);
        }
    }
}

int main(void)
{
    struct node list;
    list.next = NULL;
    struct node *listp = &list;

    unsigned char buffer[4];
    FILE *fp = fopen("/dev/urandom", "r");
    for (int i = 0; i < 20; i++) {
        fgets(buffer, 4, fp);
        prepend(listp, ((int) *buffer) % 100);
    }
    printf("random list:\t\t");
    print_list(listp);
    printf("\n");

    fgets(buffer, 4, fp);
    int pivot = ((int) *buffer) % 100;

    struct node new_list;
    new_list.next = NULL;
    struct node *new_listp = &new_list;

    partition_list(listp, new_listp, pivot);
    printf("partitioned around %d:\t", pivot);
    print_list(new_listp);
    printf("\n");
}
