# My-little-Malloc
Amani Islam - ai326
Madhur Nut - mn

mymalloc():
-

myfree(): 

strategy for coalescing - Eager Coalesing - Any time we free a chunk, we coalesce with any free neighbors there are never adjacent free chunks. 

How did we test to see if our eager coalesing works? ...

Tests:
    - test1(): For a total of 120 times, allocates a 1 byte chunk and immeadiately after frees said chunk
    - test2(): Allocates 1 byte memory chunk for 120 times, stores the addresses of the allocated memory blocks in an array of pointers, then frees the memory blocks in the same order
    - test3(): Randomly chooses between allocating or deallocating memory blocks 120 times, with a maximum of 120 allocations. Moves the last allocated memory block into the empty memory block slot upon deallocation then frees all remaining allocated memory blocks
    - test4(): Allocates 64 chunks of memory, each of size 64 bytes, then frees the chunks with even indices and the chunks with odd indices. Allocates a new chunk of size 4072 bytes and checks if it is adjacent to chunk 0 and prints an error message if it is not.
    - test5(): 

Average Times (seconds):
    1: 
    2: 
    3: 
    4: 
    5: 
