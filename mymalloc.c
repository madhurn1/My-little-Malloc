#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include"mymalloc.h"

#define MEMSIZE 4096
static char memory[4096];

header * first_header = (header *) &memory[0];

//linked list to have all information of each chunk of data. 
struct mallocLL{
    size_t size;
    bool isFreed;//t/f based on wther free or not
    struct mallocLL *next; //linked list data structure. 
};
//mymalloc call status
bool checkMalloc= false; 

//coalences when we free.

int main(){
    return 0; 
}
/*malloc(size_t size) is a system library function that returns a pointer to a block of 
memory of at least the requested size. This memory comes from a main memory resource managed
by the operating system.
malloc() function will return pointers to this large array
*/
void *mymalloc(size_t size, char *file, int line){
    //if it hasn't been initialized. 
    if (!checkMalloc){

    }
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
        return; 
    }
	header * init_ptr = (header *) (ptr - sizeof(header));
}