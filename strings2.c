#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap(char v[], int i, int j)
{
        char temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

void myqsort(char v[], int left, int right)
{
	int i, last;

	if (left >= right) {
		return;
	}
	swap(v, left, ((left + right) / 2));
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (v[i] < v[left]) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	myqsort(v, left, last - 1);
	myqsort(v, last + 1, right);
}

int check_anagrams(char *a, char *b)
{
    // compare length
    if (strlen(a) == strlen(b)) {
        // sort each string
        myqsort(a, 0, strlen(a));
        myqsort(b, 0, strlen(b));
        // compare sorted stings
        if (strcmp(a, b) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    printf("enter strings (max 32 characters) to see if they are anagrams\n");
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

        result = check_anagrams(string1, string2);
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
