#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblists.h"

char *check_palindrome(struct node *list)
{
    struct node *current = list;
    struct node *stack = malloc(sizeof(struct node));
    int count = 0;
    while (current->next != NULL) {
        current = current->next;
        count++;
    }
    current = list;
    for (int i = 0; i < count / 2; i++) {
        current = current->next;
        prepend(stack, current->value);
    }
    if (count % 2 == 1) {
        current = current->next;
    }
    for (int i = 0; i < count / 2; i++) {
        current = current->next;
        if (current->value != pop(stack)) {
            return "no";
        }
    }
    return "yes";
}

int main(void)
{
    char *input = malloc(33);
    struct node input_list;
    input_list.next = NULL;
    printf("enter a string to see if it's a palindrome\n");
    fgets(input, 32, stdin);
    input[strcspn(input, "\n")] = 0;
    for (int i = 0; i < strlen(input); i++) {
        append(&input_list, (int) input[i]);
    }
    printf("%s\n", check_palindrome(&input_list));
}
