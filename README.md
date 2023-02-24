Amani Islam - ai326 Madhur Nutulapati - mn712

Overall Strategy + Logic: We used a linked list implementation to provide similar functionality as the standard library functions malloc() and free(). We used this implementation because we can keep track of the allocated and free chunks of memory where each node of the data structure represents a chunk of memory and contains metadata(size of chunk & flag giving information on whether it's been freed or not). Our structure for the linked list has 3 main functions size, isFreed flag, and a next function, which allows us to move through each chunk of memory.

mymalloc(): First, we declare a pointer called "headBlock" that points to the beginning of the memory array, ensuring that metadata is stored at the beginning of the memory region. The advantage of this pointer is that we can easily keep track of the metadata for each chunk being allocated. Next, we check to ensure the "headBlock" hasn't been initalized before and split the memory into two chunks. One chunk is the number of bytes being requested by the client, and the other chunk is the remaining bytes in the heap. While this is happening, it will create a new header for the other chunk that is not being used, updates the isFreed property, and, most importantly, returns the pointer to the beginning of the memory block(excluding the header).

Correctness Testing for Malloc - To ensure that the client's mallocing processing is working we implemented a series of tests that not only tracking the total bytes being allocated and deallocated but also viewed the heap array for information. This way we were able to view all the byte patterns to perform our personal correctness testings. 
<!-- for(int i =0; i<HOW MANY BITES WE WISH TO VIEW AT ONCE;i++){
    printf("Index : %d, Value: %c", i, memory[i]);
}
    printf("\n"); -->

myfree(): After retrieving the pointer to the block of memory that needs to be freed for the client, we run a few error conditions to eliminate freeing issues.

IMPORTANT MESSAGE ABOUT OUR FREE() function: There is one small defect/error with our free() function where we are only able to coalesce once at a time and only frees at the last iteration of the test cases that run numerous times. Aside from this, I gaurantee and have personally tested free in all conditions and atmospheres and it perfectly works. The implementation is correct and the logic is also correct its just a small bug that prevents this working 50 or 120 times. Because of this error it is triggering all other issues and touching the edge cases which it shouldn't do. 

The error more specifically : 

<!-- if(headerB->next != NULL && headerB->next->isFreed==1){
        headerB->size += sizeof(struct mallocLL) + headerB->next->size; 
        // printf("%ld\n",headerB->next->size);
        headerB->next = headerB->next->next; 

        printf("colesce one %ld\n", headBlock->size);
} -->

Explanation - in this if condition the headerB's next blook is currently in use when it should be freed/available for use. I have personally tried using GDB to step through each line and see what each block's values etc. But can't seem to find the solution. 

    
Edge cases: (ERR.C conditions)

First checks if ptr equals to NULL which is essentially frees unitialized memory. if our headerblook is already freed and is trying to be freed again will throw an error. Because a pointer can't be freed twice.
Strategy for coalescing - Eager coalescing- Any time we free a chunk, we merge with any free neighbors, so there are never adjacent free chunks. First, we check if the next block after the current block is being freed considering it, we merge both blocks two adjacent blocks into a single block.

Correctness Testing for Coalescing & Freeing: To ensure that the client's freeing processing is working we implemented a series of tests that not only tracking the total bytes being allocated and deallocated but also viewed the heap array for information. This way we were able to view all the byte patterns to perform our personal correctness testings. Seeing the indices values helped us understand the correctness of the deallocation. 
<!-- for(int i =0; i<HOW MANY BITES WE WISH TO VIEW AT ONCE;i++){
    printf("Index : %d, Value: %c", i, memory[i]);
}
    printf("\n"); -->

Tests: - test1(): For a total of 120 times, allocates a 1 byte chunk and immeadiately after frees said chunk - test2(): Allocates 1 byte memory chunk for 120 times, stores the addresses of the allocated memory blocks in an array of pointers, then frees the memory blocks in the same order - test3(): Randomly chooses between allocating or deallocating memory blocks 120 times, with a maximum of 120 allocations. Moves the last allocated memory block into the empty memory block slot upon deallocation then frees all remaining allocated memory blocks - test4(): Allocates 64 chunks of memory, each of size 64 bytes, then frees the chunks with even indices and the chunks with odd indices. Allocates a new chunk of size 4072 bytes and checks if it is adjacent to chunk 0 and prints an error message if it is not. - test5(): Allocates and frees memory repeatedly in a loop to test the performance of the allocation and deallocation process. The loop allocates blocks of memory of size 64 bytes and cycles between allocating up to 10 blocks and freeing them.

Average Test Times (seconds): 
1: 0.001059 secs 
2: 0.001279 secs 
3: 0.002579 secs
4: 0.000314 secs
5: 0.000799 secs