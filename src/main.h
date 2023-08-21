

#ifndef MAIN_H
#define MAIN_H

void *memory_pool;
void *my_malloc(size_t size);
void my_free(void *ptr);
void display_memory();

#endif
