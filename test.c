
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/main.c"


#define MEMORY_SIZE 1024 // Total size of memory in bytes

int main()
{
    initialize_memory_pool(MEMORY_SIZE);

    void *ptr1 = my_malloc(100);
    void *ptr2 = my_malloc(200);
    void *ptr3 = my_malloc(300);

    display_memory();

    my_free(ptr2);

    display_memory();

    my_free(ptr1);
    my_free(ptr3);

    display_memory();

    free(memory_pool);

    return 0;
}