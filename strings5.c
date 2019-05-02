#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_if_one_away(char *a, char *b)
{
    // set this if we find a discrepancy, and check if it's already set when
    // we find a discrepancy to see that strings are off by more than one
    int flagged = 0;

    int len_a = strlen(a);
    int len_b = strlen(b);

    // only proceed if the lengths of the strings are within one character
    // of each other
    if (len_a > len_b + 1 || len_a < len_b - 1) {
        return 0;
    } else {
        int i = 0;
        int j = 0;
        while (i < len_a && i < len_b) {
            if (a[i] == b[j]) {
                i++;
                j++;
                continue;
            } else if (!flagged) {
                if (len_a == len_b) {
                    flagged = 1;
                } else if (len_a > len_b) {
                    flagged = 1;
                    j++;
                } else if (len_a < len_b) {
                    flagged = 1;
                    i++;
                }
                i++;
                j++;
            } else if (flagged) {
                // one discrepancy already found
                return 0;
            }
        }
        // successfully went through both strings finding no more
        // than one discrepancy
        return 1;
    }
}

int main(void)
{
    printf("enter strings (max 32 characters) to see if they are \"one away\"\n");
    printf("exit with ctrl-c\n\n");
    char *string1 = malloc(33);
    char *string2 = malloc(33);
    int result = 0;

    while (1) {
        printf("string 1: ");
        fgets(string1, 32, stdin);
        // clear the stdin buffer past 32 characters up to the newline character
        if (!strchr(string1, '\n')) {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        printf("string 2: ");
        fgets(string2, 32, stdin);
        // clear the stdin buffer past 32 characters up to the newline character
        if (!strchr(string2, '\n')) {
            scanf("%*[^\n]");scanf("%*c");
        }
        string1[strcspn(string1, "\n")] = 0;
        string2[strcspn(string2, "\n")] = 0;

        result = check_if_one_away(string1, string2);
        if (result) {
            printf("yes\n\n");
        } else {
            printf("no\n\n");
        }
    }

    free(string1);
    free(string2);
    return 0;
}
