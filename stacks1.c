#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize(int *space, int size, int **sp1, int **sp2, int **sp3)
{
    memset(space, 0, size * sizeof(int));
    *sp1 = space;
    *sp2 = space + (size / 3);
    *sp3 = space + (2 * (size / 3));
}

void push(int **sp, int val)
{
    **sp = val;
    *sp = *sp + 1;
}

int pop(int **sp)
{
    int temp = **sp;
    *sp = *sp -1;
    return temp;
}


void test(int *space, int size, int **sp1, int **sp2, int **sp3)
{
    push(sp1, 6);
    push(sp1, 7);
    push(sp1, 8);
    push(sp2, 5);
    push(sp3, 1);
    push(sp3, 2);
    pop(sp3);
    push(sp3, 3);
    int j = 0;
    for (int *i = space; i < space + size; i++) {
        if (j % 5 == 0) {
            printf("| ");
        }
        printf("%d ", *i);
        j++;
    }
}

int main(void)
{
    // initialize stacks
    int size = 15;
    int space[size];
    int *sp1, *sp2, *sp3;
    initialize(space, size, &sp1, &sp2, &sp3);

    // run test routine
    test(space, size, &sp1, &sp2, &sp3);
}
