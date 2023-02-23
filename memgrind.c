#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"
#include <string.h>

double test1()
{
    void *ptr;
    double time = 0;
    clock_t start, end;
    for (int i = 0; i < 50; i++)
    {
        start = clock();
        for (int j = 0; j < 120; j++)
        {
            ptr = malloc(1);
            free(ptr);
        }
        end = clock();
        time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    return time;
}

double test2()
{
    void *ptr[120];
    double time = 0;
    clock_t start, end;

    for (int i = 0; i < 50; i++)
    {
        start = clock();
        for (int j = 0; j < 120; j++)
            ptr[j] = malloc(1);

        for (int j = 0; j < 120; j++)
            free(ptr[j]);

        end = clock();
        time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    return time;
}

double test3()
{
    srand(time(NULL));
    void *ptrs[120];
    int mallocs = 0;
    double time = 0;
    clock_t start, end;

    for (int i = 0; i < 50; i++)
    {
        start = clock();
        for (int j = 0; j < 120; j++)
        {
            int op = rand() % 2;

            if (op == 0 && mallocs < 120)
            {
                void *chunk = malloc(1);
                ptrs[mallocs] = chunk;
                mallocs++;
            }
            else if (mallocs > 0)
            {
                int index = rand() % mallocs;
                free(ptrs[index]);
                ptrs[index] = ptrs[mallocs - 1];
                mallocs--;
            }
        }
        for (int j = 0; j < mallocs; j++)
            free(ptrs[j]);

        end = clock();
        time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    return time;
}

double test4()
{
    void *ptr[64];
    double time = 0;
    clock_t start, end;
    int j;

    for (int i = 0; i < 50; i++)
    {
        start = clock();
        for (j = 0; j < 64; j++)
            ptr[j] = malloc(64);

        for (j = 0; j < 64; j += 2)
            free(ptr[j]);

        for (j = 1; j < 64; j += 2)
            free(ptr[j]);

        void *comp = malloc(4072);
        if (comp != ptr[0])
            printf("ERROR\n");

        end = clock();
        time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    return time;
}

double test5()
{
    return 0;
}

int main()
{
    printf("Test 1 Avg Time: %f secs\n", test1() / 50);
    printf("Test 2 Avg Time: %f secs\n", test2() / 50);
    printf("Test 3 Avg Time: %f secs\n", test3() / 50);
    printf("Test 4 Avg Time: %f secs\n", test4() / 50);
    printf("Test 5 Avg Time: %f secs\n", test5() / 50);
<<<<<<< HEAD
}
=======
}
>>>>>>> 04491968ccc69015d5482da7b2f06df3ab618c13
