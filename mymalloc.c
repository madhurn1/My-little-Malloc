#include<stdio.h>
#include<stdlib.h>
#include <stddef.h>
#include "mymalloc.h"

#define MEMSIZE 4096
static char memory[MEMSIZE];

//linked list to have all information of each chunk of data. 
struct mallocLL{
    size_t size;
    int isFreed;// indicated whether the block has been freed or not. 
    struct mallocLL *next; //linked list data structure. 
};

//to point to the beginning of the memory array.
struct mallocLL *headBlock = (struct mallocLL*) memory;

//mymalloc call status
//static int checkMalloc= 1; 
// int main(){
//     return 0; 
// }
//test

/*malloc(size_t size) is a system library function that returns a pointer to a block of 
memory of at least the requested size. This memory comes from a main memory resource managed
by the operating system.
malloc() function will return pointers to this large array
*/
void *mymalloc(size_t size, char *file, int line){
    //int checkMalloc= 1; 
    // check_heap(headBlock);
    //if it hasn't been initialized before
    if (memory[0]==0 && (memory[1]==0)){
        headBlock ->size = MEMSIZE - sizeof(struct mallocLL);
        headBlock -> isFreed = 0;//check this
        headBlock->next = NULL;
        //checkMalloc = 0;
    }

    //set equal to the head block
    struct mallocLL *temp = headBlock;
    //struct mallocLL *prev = NULL;
    // If the block of memory is bigger than what we need, split it into two blocks.
    while(temp!=NULL){
        if(temp->size >=size && temp->isFreed==0){
            if (temp->size >= size + sizeof(struct mallocLL)) {
                /*This line of code is creating a new header for the free chunk that remains after 
                the requested memory has been allocated
                which allows us to properly track this chunk and use it in future allocations.
                */
                struct mallocLL *newChunk = (struct mallocLL*)((char*)temp + sizeof(struct mallocLL) + size);
                /*calculate the size of the new free chunk is simply the size of the current chunk, minus the size of the payload being allocated, 
                minus the size of the header that will be used for the new allocated chunk.
                */
                newChunk -> size = temp->size - sizeof(struct mallocLL) - size;

                //initalize the characteristics
                newChunk ->isFreed=1;
                
                //point to the next linklist element
                newChunk->next = temp->next;

                temp->isFreed = 0; 

                temp->size = size;
                
                temp->next = newChunk; 
            }   
                temp->isFreed= 0;
                
                return (void*)((char*)temp + sizeof(struct mallocLL)); //valid
        }
            // prev = temp;    
            temp = temp->next;
    }
    //fprintf(stderr,"Error - %s:%d#: Not enough Memory\n", file, line);
    return NULL;
}

/*The free(void *ptr) function informs the operating system that you are 
done with a given block of dynamically-allocated memory, and that it can 
reclaim it for other uses.
free function will let your code know that a previously-allocated region 
can be reclaimed and used for other purposes.
*/
void myfree(void *ptr, char *file, int line){
    //preliminary check the pointer's value... 
    printf("Test1");
    if (ptr==NULL){
        //error statement unitialized memory
        fprintf(stderr,"Error - %s:%d#: free uninitialized memory\n", file, line);
        return; 
    }
        printf("test");

    //header block to be freed in which we can found by subtracting 1. 
    struct mallocLL *headerB= (struct mallocLL*) ptr-1;
    //checking if already freed or not
    if(headerB->isFreed==0){
        //error -Calling free() a second time on the same pointer. 0
        fprintf(stderr, "Error - %s:%d#: Trying to free a second time on the same pointer\n", file, line);
        return;
    }
    headerB -> isFreed = 1;//check
    
    //merging adjacent blocks
    //first blocks that come after...
    if(headerB->next && headerB->next->isFreed){
        headerB->size += sizeof(struct mallocLL) + headerB->next->size; 
        headerB->next = headerB->next->next; 
    }

    //previous block is free, merge both blocks...

/*The second code snippet handles coalescing of adjacent free blocks in the 
backward direction. It checks if the previous block before the current block is 
 free and coalesces it with the current block if it is. This is useful for when a 
 block is freed in the middle of the memory pool, as it allows the freed block to be 
combined with the adjacent free blocks on either side of it.
*/
    if(headerB!=headBlock && headerB->isFreed && ((char*)headerB-sizeof(struct mallocLL)-(char*)headBlock == headBlock->size)){
        
        headBlock->size +=sizeof(struct mallocLL)+headerB->size;

        headBlock = (struct mallocLL*)((char*)headerB-sizeof(struct mallocLL));
    }
}

//memory leak error catch

void memoryLeakage(){
    struct mallocLL *tempNode = headBlock;
    while(tempNode!=NULL){
        //if 
        if(!tempNode->isFreed){
        fprintf(stderr, "Error at address %p and  size of %zu\n: Memory Leakage \n",(void*)(tempNode + 1),tempNode->size );
        }
        tempNode = tempNode ->next; 
    }
}

// void check_heap(struct mallocLL *headBlock) {
//     struct mallocLL *current = headBlock;
//     int total_blocks = 0;
//     int total_allocated = 0;
    
//     while (current != NULL) {
//         total_blocks++;
//         if (!current->isFreed) {
//             total_allocated += current->size;
//             printf("Block at %p of size %lu is allocated\n", (void *)current, current->size);
//         } else {
//             printf("Block at %p of size %lu is freed\n", (void *)current, current->size);
//         }
//         current = current->next;
//     }
    
//     printf("Total number of blocks: %d\n", total_blocks);
//     printf("Total memory allocated: %d\n", total_allocated);
// }