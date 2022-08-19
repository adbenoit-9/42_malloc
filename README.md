# MALLOC (@42paris)
*A dynamic allocation memory management library.*

## Usage
```
$ git clone https://github.com/adbenoit-9/42_malloc.git
$ cd 42_malloc
$ make
```

### Tests
```
$ make run
$ ./run.sh ./tests_malloc [function to test]
```

## About

### malloc()
The malloc() function allocates “size” bytes of memory and returns a pointer to the
allocated memory.\
If there is an error, return a NULL pointer.

### realloc()
The realloc() function tries to change the size of the allocation pointed to by “ptr”
to “size”, and returns “ptr”. If there is not enough room to enlarge the memory
allocation pointed to by ptr, realloc() creates a new allocation, copies as much of
the old data pointed to by “ptr” as will fit to the new allocation, frees the old
allocation, and returns a pointer to the allocated memory.\
If there is an error, return a NULL pointer.

### free()
The free() function deallocates the memory allocation pointed to by “ptr”. If “ptr”is
a NULL pointer, no operation is performed.

### show_alloc_mem()
The show_alloc_mem() function is a visual on the state of the allocated memory zones.

### show_alloc_mem_ex()
The show_alloc_mem() function is an hexa dump of the allocated zones.

## Links
- https://heap-exploitation.dhavalkapil.com/diving_into_glibc_heap/malloc_chunk
- https://gee.cs.oswego.edu/dl/html/malloc.html
- https://azeria-labs.com/heap-exploitation-part-1-understanding-the-glibc-heap-implementation/
