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

struct node *add_lists(struct node *a, struct node *b, struct node *c)
{
    int carry = 0;
    int end_a = 0;
    int end_b = 0;
    int val_a, val_b;

    while (!end_a || !end_b) {
        if (a->next != NULL) {
            a = a->next;
        } else {
            end_a = 1;
        }
        if (b->next != NULL) {
            b = b->next;
        } else {
            end_b = 1;
        }
        if (end_a && end_b) {
            break;
        }
        c->next = malloc(sizeof(struct node));
        c = c->next;
        val_a = end_a ? 0 : a->value;
        val_b = end_b ? 0 : b->value;
        c->value = (val_a + val_b + carry) % 10;
        if ((val_a + val_b + carry) >= 10) {
            carry = 1;
        } else {
            carry = 0;
        }
    }

    return c;
}

int main(void)
{
    struct node a;
    a.next = NULL;
    struct node *ap = &a;

    struct node b;
    b.next = NULL;
    struct node *bp = &b;

    unsigned char buffer[4];
    FILE *fp = fopen("/dev/urandom", "r");

    fgets(buffer, 4, fp);
    int len_a = ((int) *buffer) % 5;
    for (int i = 0; i < len_a; i++) {
        fgets(buffer, 4, fp);
        if (i == 0) {
            prepend(ap, (((int) *buffer) % 9) + 1);
        } else {
            prepend(ap, ((int) *buffer) % 10);
        }
    }

    fgets(buffer, 4, fp);
    int len_b = ((int) *buffer) % 5;
    for (int i = 0; i < len_b; i++) {
        fgets(buffer, 4, fp);
        if (i == 0) {
            prepend(bp, (((int) *buffer) % 9) + 1);
        } else {
            prepend(bp, ((int) *buffer) % 10);
        }
    }

    print_list(ap);
    printf(" + ");
    print_list(bp);
    printf(" = ");

    struct node c;
    c.next = NULL;
    struct node *cp = &c;

    add_lists(ap, bp, cp);
    print_list(cp);
    printf("\n");
}
