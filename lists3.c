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

void remove_middle(struct node *target)
{
    struct node *copy_next = target->next;
    target->value = target->next->value;
    target->next = target->next->next;
    free(copy_next);
}

void print_list(struct node *list)
{
    struct node *current = list;
    while (current->next != NULL) {
        current = current->next;
        printf("%d->", current->value);
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
    printf("random list:\t");
    print_list(listp);
    printf("\n");

    struct node *current = listp;
    for (int i = 0; i < 10; i++) {
        current = current->next;
    }
    remove_middle(current);
    printf("removed middle:\t");
    print_list(listp);
    printf("\n");
}
