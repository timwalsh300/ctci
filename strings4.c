#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_palindrome_perm(char *s)
{
    // create a table to mark each ASCII character
    int table[128];
    for(int i = 0; i < 128; i++) {
        table[i] = 0;
    }

    // this counter keeps track of how many characters we've found
    // that aren't yet members of a pair... palindromes can only have
    // one odd character
    int odds = 0;

    for (int i = 0; i < strlen(s); i++) {
        // check if the character is already marked in the table
        if (table[(int) s[i]]) {
            table[(int) s[i]] = 0;
            odds--;
        } else {
            table[(int) s[i]] = 1;
            odds++;
        }
    }
    if (odds > 1) {
        return 0;
    } else {
        return 1;
    }
}

int main(void)
{
    printf("enter a string (max 32 characters) to see if it's a permutation of a palindrome\n");
    printf("exit with ctrl-c\n\n");
    char *string_to_check = malloc(33);
    int result = 0;

    while (1) {
        printf("string: ");
        fgets(string_to_check, 32, stdin);
        // clear the stdin buffer past 32 characters up to the newline character
        if (!strchr(string_to_check, '\n')) {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        string_to_check[strcspn(string_to_check, "\n")] = 0;
        result = is_palindrome_perm(string_to_check);
        if (result) {
            printf("yes\n\n");
        } else {
            printf("no\n\n");
        }
    }

    free(string_to_check);
    return 0;
}
