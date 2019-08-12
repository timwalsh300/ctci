#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblists.h"

struct node *find_nth_from_tail(struct node *list, int n)
{
    struct node *current = list;
    int count = 0;
    while (current->next != NULL) {
        count++;
        current = current->next;
    }

    current = list;
    for (int i = 0; i < count - n; i++) {
        current = current->next;
    }
    return current;
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

    fgets(buffer, 4, fp);
    fclose(fp);
    int n = ((int) *buffer) % 20;
    struct node *nth = find_nth_from_tail(listp, n);
    if (n == 1) {
        printf("1st node from the tail has the value %d\n", nth->value);
    } else if (n == 2) {
        printf("2nd node from the tail has the value %d\n", nth->value);
    } else if (n == 3) {
        printf("3rd node from the tail has the value %d\n", nth->value);
    } else {
        printf("%dth node from the tail has the value %d\n", n, nth->value);
    }
}
