/* malloc_freelist.c: Free List Implementation
 *
 * The FreeList is an unordered doubly-linked circular list containing all the
 * available memory allocations (memory that has been previous allocated and
 * can be re-used).
 **/

#include "memory/counters.h"
#include "memory/freelist.h"

/* Global Variables */

Block FreeList = {-1, &FreeList, &FreeList};

/* Functions */

/**
 * Search for an existing block in free list with at least the specified size
 * using the first fit algorithm.
 * @param   size    Amount of memory required.
 * @return  Pointer to existing block (otherwise NULL if none are available).
 **/
Block *free_list_search_ff(size_t size)
{
    // TODO: Implement first fit algorithm
    return NULL;
}

/**
 * Search for an existing block in free list with at least the specified size
 * using the best fit algorithm.
 * @param   size    Amount of memory required.
 * @return  Pointer to existing block (otherwise NULL if none are available).
 **/
Block *free_list_search_bf(size_t size)
{
    // TODO: Implement best fit algorithm
    return NULL;
}

/**
 * Search for an existing block in free list with at least the specified size
 * using the worst fit algorithm.
 * @param   size    Amount of memory required.
 * @return  Pointer to existing block (otherwise NULL if none are available).
 **/
Block *free_list_search_wf(size_t size)
{
    // TODO: Implement wost fit algorithm
    return NULL;
}

/**
 * Search for an existing block in free list with at least the specified size.
 *
 * Note, this is a wrapper function that calls one of the three algorithms
 * above based on the compile-time setting.
 *
 * @param   size    Amount of memory required.
 * @return  Pointer to existing block (otherwise NULL if none are available).
 **/
Block *free_list_search(size_t size)
{
    Block *block = NULL;
#if defined FIT && FIT == 0
    block = free_list_search_ff(size);
#elif defined FIT && FIT == 1
    block = free_list_search_bf(size);
#elif defined FIT && FIT == 2
    block = free_list_search_wf(size);
#endif

    if (block)
    {
        Counters[REUSES]++;
    }
    return block;
}

/**
 * Insert specified block into free list.
 *
 * Scan the free list and attempt to merge specified block into an existing
 * block (or a current block into the specified block, updating the pointers
 * appropriately).
 *
 * If a merge is not possible, then simply add the block to the end of the free
 * list.
 * @param   block   Pointer to block to insert into free list.
 **/
void free_list_insert(Block *block)
{
    // TODO: Implement free list insertion
}

/**
 * Return length of free list.
 * @return  Length of the free list.
 **/
size_t free_list_length()
{
    // TODO: Implement free list length
    return 0;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
