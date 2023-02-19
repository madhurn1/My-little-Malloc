#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

void test1()
{
    for (int i = 0; i < 120; i++)
    {
        void *ptr = malloc(1);
        free(ptr);
    }
}

int main()
{
    srand(time(NULL));
    clock_t start, end;
    double avgtime;

    for (int i = 0; i < 50; i++)
    {
        start = clock();
        test1();
        end = clock();
        avgtime += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    printf("Test Case 1: %f seconds\n", avgtime / 50);

    return 0;
}