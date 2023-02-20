#ifndef _MYMALLOC_H
#define _MYMALLOC_H

#define malloc(s)   mymalloc(s, __FILE__, __LINE__)
#define free(p)     myfree(p, __FILE__, __LINE__)


void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);
//void getSize();
void memoryLeakage();

#endif


/*
The mymalloc() function takes three arguments: the amount of memory to allocate (size), the name 
of the file in which the function is called (file), and the line number at which the function is called (line). 
The function returns a pointer to the allocated memory, or NULL if allocation fails.
*/

/*
The myfree() function takes three arguments: a pointer to the memory to be freed (ptr), 
the name of the file in which the function is called (file), and the line number at which the 
function is called (line). The function does not return a value.
*/

/*
The __FILE__ and __LINE__ macros are predefined macros in C that expand to the name of the current source 
file and the current line number, respectively. 
They are used in the malloc() and free() macros to provide debugging information when memory is allocated or freed.
*/