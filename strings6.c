#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *compress(char *s)
{
    char *compressed = malloc(129);
    for (int i = 0; i < 129; i++) {
        compressed[i] = '\0';
    }
    int j = 0;
    int in_series = 0;
    int counter = 1;
    char *count = malloc(4);
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] != s[i + 1] && !in_series) {
            compressed[j++] = s[i];
        } else if (s[i] != s[i + 1] && in_series) {
            sprintf(count, "%d", counter);
            strcat(compressed, count);
            j = j + strlen(count);
            counter = 1;
            in_series = 0;
        } else if (s[i] == s[i + 1] && !in_series) {
            compressed[j++] = s[i];
            counter++;
            in_series = 1;
        } else if (s[i] == s[i + 1] && in_series) {
            counter++;
        }
    }

    if (strlen(compressed) < strlen(s)) {
        return compressed;
    } else {
        return s;
    }
}

int main(void)
{
    printf("enter a string (max 128 characters) to get the compressed version\n");
    printf("exit with ctrl-c\n\n");
    char *string_to_compress = malloc(129);
    int result = 0;

    while (1) {
        printf("string: ");
        fgets(string_to_compress, 128, stdin);
        // clear the stdin buffer past 32 characters up to the newline character
        if (!strchr(string_to_compress, '\n')) {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        string_to_compress[strcspn(string_to_compress, "\n")] = 0;
        printf("%s\n", compress(string_to_compress));
    }

    free(string_to_compress);
    return 0;
}
