#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include "mymalloc.h"

// Allocates 1 byte 120 times
void test1()
{
    void *arr[4096];
    for (int i = 0; i < 120; i++)
    {
        arr[i] = malloc(1);
        free(arr[i]);
    }
}

// Allocates 4096 bytes 1 time
void test2()
{
    void *arr = malloc(4000);
    if (arr == NULL)
        printf("malloc failed\n");
    free(arr);
}

// Allocates objects with distinct byte patterns
void test3()
{
    // Allocate memory for the objects
    void *arr[4];
    for (int i = 0; i < 4; i++)
    {
        arr[i] = malloc(1000);
        if (arr[i] == NULL)
        {
            printf("malloc failed\n");
            return;
        }
    }

    // Fill each object with a distinct byte pattern
    for (int i = 0; i < 4; i++)
    {
        char size = i + 1;
        memset(arr[i], size, 1000);
    }

    // Check if each object still contains the written pattern
    for (int i = 0; i < 4; i++)
    {
        char size = i + 1;
        for (int j = 0; j < 4; j++)
        {
            if (*((char *)(arr[i] + j)) != size)
            {
                printf("error: object %d was overwritten\n", i);
                return;
            }
        }
    }

    printf("all objects have the right pattern\n");

    // Free memory for the objects
    for (int i = 0; i < 4; i++)
        free(arr[i]);
}

// Coelesces adjacent free blocks
void test4()
{
    printf("hey\n");
    void *arr[4];
    for (int i = 0; i < 4; i++)
    {
        arr[i] = malloc(16);
        if (arr[i] == NULL)
        {
            printf("malloc failed\n");
            return;
        }
    }

    // Free every other block
    for (int i = 0; i < 4; i += 2)
        free(arr[i]);

    // Allocate a new block to try to fill the hole left by the freed blocks
    void *new = malloc(16);
    if (new == NULL)
        printf("malloc failed\n");

    if (new != arr[0])
        printf("Coalescing failed: expected %p, got %p\n", arr[0], new);

    free(new);

    // Free the remaining blocks
    for (int i = 1; i < 4; i += 2)
    {
        free(arr[i]);
    }
}

int main()
{
    srand(time(NULL));
    clock_t start, end;
    double avgtime;

    for (int i = 0; i < 1; i++)
    {
        start = clock();
        test1();
        end = clock();
        avgtime += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    printf("Test 1: %f secs\n", avgtime / 50);
    avgtime = 0;

    for (int i = 0; i < 1; i++)
    {
        start = clock();
        test2();
        end = clock();
        avgtime += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    printf("Test 2: %f secs\n", avgtime / 50);
    avgtime = 0;

    for (int i = 0; i < 1; i++)
    {
        start = clock();
        test3();
        end = clock();
        avgtime += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    printf("Test 3: %f secs\n", avgtime / 50);
    avgtime = 0;

    for (int i = 0; i < 1; i++)
    {
        start = clock();
        test4();
        end = clock();
        avgtime += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    printf("Test 4: %f secs\n", avgtime / 50);

    return 0;
}