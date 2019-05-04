#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s1 = "waterbottle";
    char *s2 = "tlewaterbot";
    char *temp = malloc(2 * strlen(s2) + 1);
    sprintf(temp, "%s%s", s2, s2);
    printf("checking for %s in %s\n", s1, temp);
    char *result = strstr(temp, s1);
    if (strncmp(result, s1, strlen(s1)) == 0) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}
