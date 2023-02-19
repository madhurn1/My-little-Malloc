#include<stdio.h>
#include<stdlib.h>
#include"mymalloc.h"

#define MEMSIZE 4096
static char memory[4096];

//linked list to have all information of each chunk of data. 
struct mallocLL{
    size_t size;
    int isFreed;// wther free or not
    struct mallocLL *next; //linked list data structure. 
};

//first value ? Not sure
//struct mallocLL *headBlock = (struct mallocLL*) & memory[0];
struct mallocLL *headBlock = (void*) memory;

//mymalloc call status
static int checkMalloc= 1; 

//coalences when we free.

int main(){
    return 0; 
}
//test

/*malloc(size_t size) is a system library function that returns a pointer to a block of 
memory of at least the requested size. This memory comes from a main memory resource managed
by the operating system.
malloc() function will return pointers to this large array
*/
void *mymalloc(size_t size, char *file, int line){
    //if it hasn't been initialized before
    if (checkMalloc){
        headBlock = (struct mallocLL *)(MEMSIZE - sizeof(struct mallocLL));
        headBlock -> isFreed = 1;
        //set next block equal to NULL
        headBlock->next = NULL;
        checkMalloc = 0;
    }
    //set equal to the head block
    struct mallocLL *temp = headBlock;
    //holds the prev value as we traverse through the LL 
    //struct mallocLL *prev = NULL;
    
    // If the block of memory is bigger than what we need, split it into two blocks.
    while(temp!=NULL){
        if(temp->size >=size && temp->isFreed){
            if (temp->size >= size + sizeof(struct mallocLL)) {
                struct mallocLL *newChunk = (void*)((void*)temp + sizeof(struct mallocLL) + size);
                //initalize the characteristics
                newChunk ->isFreed=1;
                //point to the next linklist element
                newChunk->next = temp->next;

                temp->size = size;
                
                temp->next = newChunk; 
            }
                temp->isFreed= 0;
                
                return (void*)(temp + 1);
        }
            temp = temp->next;
    }
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
    if (ptr==NULL){
        //error statement unitialized memory
        fprintf(stderr,"Error - %s:%d#: free uninitialized memory\n", file, line);
        return; 
    }

    //header block to be freed in which we can find by subtracting 1. 
    struct mallocLL *headerB= (struct mallocLL*) ptr-1;
    //checking if already freed or not
    if(headerB->isFreed){
        //error -Calling free() a second time on the same pointer. 
        fprintf(stderr, "Error - %s:%d#: Trying to free a second time on the same pointer\n", file, line);
        return;
    }
    headerB -> isFreed = 1;
    
    //merging adjacent blocks
    //first blocks that come after...
    if(headerB->next && headerB->next->isFreed){
        headerB->size += sizeof(struct mallocLL) + headerB->next->size; 
        headerB->next = headerB->next->next; 
    }

    //previous block is free, merge both blocks...

    /*This condition checks if the block of memory that was just freed, curr, is immediately 
    before the head block in memory and if both blocks are currently free. 
    If both conditions are true, it merges the two free blocks into one larger block.
    calculates the distance between the end of the head block (which is the beginning of the memory array) 
    and the beginning of the block that was just freed. If this distance is equal to the size of the head 
    block, it means that the two blocks are contiguous in memory and can be merged.
    */
    if(headerB!=headBlock && headerB->isFreed && ((char*)headerB-sizeof(struct mallocLL)-(char*)headBlock == headBlock->size)){
        headBlock->size +=sizeof(struct mallocLL)+headerB->size;
        headBlock = (struct mallocLL*)((char*)headerB-sizeof(struct mallocLL));
    }
}

//memory leak error catch
// void memeoryLeakage(){
//     struct mallocLL *tempNode = headBlock;
//     while(tempNode){
        
//     }
// }


//need a get size method


