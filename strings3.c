#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *urlify(char *s)
{
    // iterate through the string to count spaces in order to
    // allocate the correct of amount of room to insert the %20 place-holders
    int spaces = 0;
    int original_length = strlen(s);
    for (int i = 0; i < original_length; i++) {
        if (s[i] == ' ' || s[i] == '\t') {
            spaces++;
        }
    }
    // k initially points to the new end of the string that will contain the URL,
    // allowing room for each %20 that will replace a space or tab
    int k = original_length + (spaces * 2) - 1;
    // iterate backwards through the original string, placing characters starting
    // at k and working backwards
    for (int j = original_length - 1; j >= 0; j--) {
        if (s[j] == ' ' || s[j] == '\t') {
            s[k--] = '0';
            s[k--] = '2';
            s[k--] = '%';
        } else {
            s[k--] = s[j];
        }
    }
    return s;
}

int main(void)
{
    printf("enter a string (max 128 characters) to turn it into a URL with %20 replacing spaces\n");
    printf("exit with ctrl-c\n\n");
    char *string_to_urlify = malloc(384);

    while (1) {
        printf("string: ");
        fgets(string_to_urlify, 128, stdin);
        // clear the stdin buffer past 128 characters up to the newline character
        if (!strchr(string_to_urlify, '\n')) {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        string_to_urlify[strcspn(string_to_urlify, "\n")] = 0;
        printf("%s\n", urlify(string_to_urlify));
    }

    free(string_to_urlify);
    return 0;
}
