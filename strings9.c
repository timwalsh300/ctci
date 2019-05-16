#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s1 = malloc(32);
    char *s2 = malloc(32);
    printf("enter s1: ");
    fgets(s1, 32, stdin);
    s1[strcspn(s1, "\n")] = 0;
    printf("enter s2: ");
    fgets(s2, 32, stdin);
    s2[strcspn(s2, "\n")] = 0;

    if (strlen(s1) != strlen(s2)) {
        printf("strings are different lengths; can't be a rotation");
        exit(0);
    }

    char *temp = malloc(2 * strlen(s1) + 1);
    sprintf(temp, "%s%s", s1, s1);
    printf("checking for %s in %s\n", s2, temp);
    char *result = strstr(temp, s2);
    if (strncmp(result, s2, strlen(s2)) == 0) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}
