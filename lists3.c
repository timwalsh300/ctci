#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblists.h"

void remove_middle(struct node *target)
{
    struct node *copy_next = target->next;
    target->value = target->next->value;
    target->next = target->next->next;
    free(copy_next);
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
