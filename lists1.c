#include <stdio.h>
#include <stdlib.h>

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

int remove_duplicates(struct node *list)
{
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
    return length;
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
    struct node *list = malloc(sizeof(struct node));
    list->next = NULL;

    unsigned char buffer[4];
    FILE *fp = fopen("/dev/urandom", "r");
    for (int i = 0; i < 20; i++) {
        fgets(buffer, 4, fp);
        prepend(list, ((int) *buffer) % 100);
    }
    fclose(fp);
    printf("random list: ");
    print_list(list);
    printf("\n");

    remove_duplicates(list);
}
