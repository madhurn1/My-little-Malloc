#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
//remove it later... 
#include "mymalloc.c"

/********************************************************************************************************************/

#include <stdio.h>

/********************************************************************************************************************/

#include <sys/time.h> // Defines the timeval structure to perform various functions.
#include <time.h>

/********************************************************************************************************************/

#include "mymalloc.h" // Contains the functions and Macros as described in p1.pdf.

/********************************************************************************************************************/

#define TASKSIZE 50 // Defined to run each task 50 times everytime any task is called.
#define NUMTIMES 120 // To operate malloc and free functions 120 times on given task.

/********************************************************************************************************************/

double TaskCount1() { // To malloc() and immediately free() a 1-byte chunk, 120 times, repeated for 50 cycles.
    void *ptr; struct timeval start, end; double TotalTime = 0.0;
    
    for (int i = 0; i < 1; i++) {
        gettimeofday(&start, NULL);

        for (int j = 0; j < 1; j++) { 
            ptr = malloc(1); 
            free(ptr); 
        }

        gettimeofday(&end, NULL); // Now, calculating the total time taken do perform the task in seconds.
        TotalTime += (double)(end.tv_sec - start.tv_sec) + ((double)(end.tv_usec - start.tv_usec) / 1000000.0);
    
    } 

    // for(int i =0; i<30;i++){
    // printf("Index : %d, Value: %c", i, memory[i]);
    // }
    // printf("\n");
        
    return TotalTime;
}

/********************************************************************************************************************/

double TaskCount2() { /* To use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() 
                       to deallocate the chunks. */
    void *ptr[NUMTIMES]; struct timeval start, end; double TotalTime = 0.0;

    for (int i = 0; i < TASKSIZE; i++) {
        gettimeofday(&start, NULL);

        for (int j = 0; j < NUMTIMES; j++) { ptr[j] = malloc(1); }
        for (int j = 0; j < NUMTIMES; j++) { free(ptr[j]); }

        gettimeofday(&end, NULL); // Now, calculating the total time taken do perform the task in seconds.
        TotalTime += (double)(end.tv_sec - start.tv_sec) + ((double)(end.tv_usec - start.tv_usec) / 1000000.0);
    
    } return TotalTime;
}

/********************************************************************************************************************/

double TaskCount3() { /* Randomly choose between one of the following tasks to be performed : 
                        • Allocating a 1-byte chunk and storing the pointer in an array.
                        • Deallocating one of the chunks in the array (if any). 
    Repeat until you have called malloc() 120 times, then free all of the remaining allocated chunks in the array. */
    void *ptr[NUMTIMES]; int ChunksAllocated = 0; struct timeval start, end; double TotalTime = 0.0;

    for (int i = 0; i < TASKSIZE; i++) {
        gettimeofday(&start, NULL);

        for (int j = 0; j < NUMTIMES; j++) {

            if (ChunksAllocated == 0 || (rand() % 2 == 0 && ChunksAllocated < NUMTIMES)) {
                ptr[ChunksAllocated] = malloc(1); ChunksAllocated++;
            } else {
                int idx = rand() % ChunksAllocated; // Randomly selecting a previously allocated chunk.
                free(ptr[idx]); ChunksAllocated--; // Deallocating the randomly chosen chunk.
                ptr[idx] = ptr[ChunksAllocated]; // Updating pointer to this index w/last pointer in 'ptr' array.
            }
        }

        for (int j = 0; j < ChunksAllocated; j++) { free(ptr[j]); } // To free any remaining allocated chunks.

        gettimeofday(&end, NULL); // Now, calculating the total time taken do perform the task in seconds.
        TotalTime += (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;
    
    } return TotalTime;
}

/********************************************************************************************************************/

double TaskCount4() { /* Instead of allocating 1-byte chunks, this stress test creates 16-byte chunks and deallocates 
them in a sequence that releases even-numbered pieces first and odd-numbered chunks afterwards. This pattern can be 
used to put the allocator's abilities to control memory unit fragmentation and coalescence under stress. */
    void *ptr[NUMTIMES]; struct timeval start, end; double TotalTime = 0.0;

    for (int i = 0; i < TASKSIZE; i++) {
        gettimeofday(&start, NULL);

        for (int j = 0; j < NUMTIMES; j++) { ptr[j] = malloc(16); }

        for (int j = 0; j < NUMTIMES; j += 2) { free(ptr[j]); } // Freeing chunks at even places in 'ptr' array.
        for (int j = 1; j < NUMTIMES; j += 2) { free(ptr[j]); } // Freeing chunks at odd places in 'ptr' array.

        gettimeofday(&end, NULL); // Now, calculating the total time taken do perform the task in seconds.
        TotalTime += (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;
    
    } return TotalTime;
}

/********************************************************************************************************************/

double TaskCount5() { /* The allocation and deallocation of 16-byte chunks during this stress test alternates until 10 
chunks are allocated, at which point all allocated chunks are freed. This pattern can be used to stress-test the 
allocator's capability to manage repetitive allocations and deallocations of various sizes as well as test how it 
responds to irregular variations in memory space. */
    void *ptr[NUMTIMES]; int ChunksAllocated = 0; struct timeval start, end; double TotalTime = 0.0;

    for (int i = 0; i < TASKSIZE; i++) {
        gettimeofday(&start, NULL);

        for (int j = 0; j < NUMTIMES; j++) { 
            if (ChunksAllocated < 10) { ptr[ChunksAllocated] = malloc(16); ChunksAllocated++; } 
            
            else { // This condition checks whether 10 chunks are allocated yet or not. If yes, it frees them.
                for (int k = 0; k < ChunksAllocated; k++) { free(ptr[k]); }
                ChunksAllocated = 0; // Reinitializing variable to zero once we have freed all allocated chunks.
            }
        }

        for (int j = 0; j < ChunksAllocated; j++) { free(ptr[j]); } // To free any remaining allocated chunks.

        gettimeofday(&end, NULL); // Now, calculating the total time taken do perform the task in seconds.
        TotalTime += (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;
    
    } return TotalTime;
}

/********************************************************************************************************************/

int main() { srand(time(NULL)); // To initialize random number generator for Task3.

    double T1 = TaskCount1(); 
    double T2 = TaskCount2(); double T3 = TaskCount3(); 
    double T4 = TaskCount4(); double T5 = TaskCount5();

    printf("Task 1: Average time taken = %f seconds\n", T1 / TASKSIZE);
    printf("Task 2: Average time taken = %f seconds\n", T2 / TASKSIZE);
    printf("Task 3: Average time taken = %f seconds\n", T3 / TASKSIZE);
    printf("Task 4: Average time taken = %f seconds\n", T4 / TASKSIZE);
    printf("Task 5: Average time taken = %f seconds\n", T5 / TASKSIZE);
}
