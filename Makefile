CC = gcc -Wall -Werror -fsanitize=address
RM = rm -f
MEMGRIND = err
OBJECTS = err.o mymalloc.o


$(MEMGRIND): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(MEMGRIND)

memgrind.o: err.c mymalloc.h
	$(CC) -c err.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) -c mymalloc.c

clean:
	$(RM) $(MEMGRIND) $(OBJECTS)
