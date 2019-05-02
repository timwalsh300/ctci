#include <stdio.h>

void f(char **x)
{
    *x = "zoo";
}

int main(void)
{
    char *a;
    f(&a);
    printf("%s", a);
}
