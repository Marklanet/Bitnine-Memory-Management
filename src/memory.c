/* malloc.c: POSIX API Implementation */

#include "memory/counters.h"
#include "memory/freelist.h"

#include <assert.h>
#include <string.h>

/* Functions */
/**
 * Allocate specified amount memory.
 * @param   size    Amount of bytes to allocate.
 * @return  Pointer to the requested amount of memory.
 **/
void *my_malloc(size_t size)
{
    /* Initialize counters */
    init_counters();

    /* Handle empty size */
    if (!size)
    {
        return NULL;
    }

    // TODO: Search free list for any available block with matching size
    Block *block = block_allocate(size);

    /* Could not find free block or allocate a block, so just return NULL */
    if (!block)
    {
        return NULL;
    }

    assert(block->size == size);
    assert(block->next == block);
    assert(block->prev == block);

    /* Update counters */
    Counters[MALLOCS]++;
    Counters[REQUESTED] += size;

    /* Return data address associated with block */
    return block->data;
}

/**
 * Release previously allocated memory.
 * @param   ptr     Pointer to previously allocated memory.
 **/
void my_free(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    /* Update counters */
    Counters[FREES]++;

    // TODO: Try to release block, otherwise insert it into the free list
}

/**
 * Allocate memory with specified number of elements and with each element set
 * to 0.
 * @param   nmemb   Number of elements.
 * @param   size    Size of each element.
 * @return  Pointer to requested amount of memory.
 **/
void *my_calloc(size_t nmemb, size_t size)
{
    // TODO: Implement calloc
    // Counters[CALLOCS]++;
    return NULL;
}

/**
 * Reallocate memory with specified size.
 * @param   ptr     Pointer to previously allocated memory.
 * @param   size    Amount of bytes to allocate.
 * @return  Pointer to requested amount of memory.
 **/
void *my_realloc(void *ptr, size_t size)
{
    // TODO: Implement realloc
    // Counters[REALLOCS]++;
    return NULL;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
