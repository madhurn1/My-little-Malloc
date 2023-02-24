# My-little-Malloc
Amani Islam - ai326
Madhur Nutulapati - mn712

Overall Strategy + Logic: 
We used a linked list implementation to provide similar functionality as the standard library functions malloc() and free(). We used this implementation because we can keep track of the allocated and free chunks of memory where each node of the data structure represents a chunk of memory and contains metadata(size of chunk & flag giving information on whether it's been freed or not). Our structure for the linked list has 3 main functions size, isFreed flag, and a next function, which allows us to move through each chunk of memory.   
 
mymalloc():
First,  we declare a pointer called "headBlock" that points to the beginning of the memory array, ensuring that metadata is stored at the beginning of the memory region. The advantage of this pointer is that we can easily keep track of the metadata for each chunk being allocated. Next, we check to ensure the "headBlock" hasn't been initalized before and split the memory into two chunks. One chunk is the number of bytes being requested by the client, and the other chunk is the remaining bytes in the heap. While this is happening, it will create a new header for the other chunk that is not being used, updates the isFreed property, and, most importantly, returns the pointer to the beginning of the memory block(excluding the header). 

myfree(): 
After retrieving the pointer to the block of memory that needs to be freed for the client, we run a few error conditions to eliminate freeing issues.

Edge cases: 
1. First checks if ptr equals to NULL which is essentially frees unitialized memory. 
2. if our headerblook is already freed and is trying to be freed again will throw an error. Because a pointer can't be freed twice. 


Strategy for coalescing - Eager coalescing- Any time we free a chunk, we merge with any free neighbors, so there are never adjacent free chunks. First, we check if the next block after the current block is being freed considering it, we merge both blocks two adjacent blocks into a single block. 

Correctness Testing for Coalescing - 

Corectness Testing for Free - 

Tests:
    - test1(): For a total of 120 times, allocates a 1 byte chunk and immeadiately after frees said chunk
    - test2(): Allocates 1 byte memory chunk for 120 times, stores the addresses of the allocated memory blocks in an array of pointers, then frees the memory blocks in the same order
    - test3(): Randomly chooses between allocating or deallocating memory blocks 120 times, with a maximum of 120 allocations. Moves the last allocated memory block into the empty memory block slot upon deallocation then frees all remaining allocated memory blocks
    - test4(): Allocates 64 chunks of memory, each of size 64 bytes, then frees the chunks with even indices and the chunks with odd indices. Allocates a new chunk of size 4072 bytes and checks if it is adjacent to chunk 0 and prints an error message if it is not.
    - test5(): Allocates and frees memory repeatedly in a loop to test the performance of the allocation and deallocation process. The loop allocates blocks of memory of size 64 bytes and cycles between allocating up to 10 blocks and freeing them.

Average Test Times (seconds):
    1: 
    2: 
    3: 
    4: 
    5: 
