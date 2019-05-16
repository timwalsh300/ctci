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

int table_member(int t[], int min, int v)
{
    if (t[v - min]) {
        return 1;
    } else {
        return 0;
    }
}

void mark_table(int t[], int min, int v)
{
    t[v - min] = 1;
}

int remove_duplicates(struct node *list)
{
    // start by scanning the list once to learn its properties
    int length = 0;
    int min = 100;
    int max = 0;
    struct node *current = list;
    while (current->next != NULL) {
        current = current->next;
        if (current->value < min) {
            min = current->value;
        }
        if (current->value > max) {
            max = current->value;
        }
        length++;
    }
    printf("length: %d min: %d max: %d\n", length, min, max);

    // now start removing duplicates
    int range = max - min + 1;
    int table[range];
    memset(table, 0, (range * 4));
    int removals = 0;
    current = list;
    struct node *last;
    while (current->next != NULL) {
        current = current->next;
        if (table_member(table, min, current->value)) {
            last->next = current->next;
            removals++;
        } else {
            mark_table(table, min, current->value);
            last = current;
        }
    }

    return removals;
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
    fclose(fp);
    printf("random list:\t");
    print_list(listp);
    printf("\n");

    printf("%d duplicates removed\n", remove_duplicates(listp));
    printf("resulting list:\t");
    print_list(listp);
    printf("\n");
}
