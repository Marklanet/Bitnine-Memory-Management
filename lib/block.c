/* malloc_block.c: Block Structure */

#include "memory/block.h"
#include "memory/counters.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// #include <unistd.h>

/* Functions */

/**
 * Allocate a new block on the heap using sbrk:
 *
 *  1. Determined aligned amount of memory to allocate.
 *  2. Allocate memory on the heap.
 *  3. Set allocage block properties.
 *
 * @param   size    Number of bytes to allocate.
 * @return  Pointer to data portion of newly allocate block.
 **/
Block *block_allocate(size_t size)
{
    intptr_t capacity = ALIGN(size + sizeof(Block));
    Block *block = sbrk(capacity);
    if (block == SBRK_FAILURE)
    {
        return NULL;
    }

    block->size = size;
    block->prev = block;
    block->next = block;

    Counters[HEAP_SIZE] += capacity;
    Counters[BLOCKS]++;
    Counters[GROWS]++;
    return block;
}

/**
 * Attempt to release memory used by block to heap:
 *
 *  1. If the block is at the end of the heap.
 *  2. The block size meets the trim threshold.
 *
 * @param   block   Pointer to block to release.
 * @return  Whether or not the release completed successfully.
 **/
bool block_release(Block *block)
{
    // TODO: Implement block release
    // size_t allocated = 0;
    // Counters[BLOCKS]--;
    // Counters[SHRINKS]++;
    // Counters[HEAP_SIZE] -= allocated;
    return false;
}

/**
 * Detach specified block from its neighbors.
 *
 * @param   block   Pointer to block to detach.
 * @return  Pointer to detached block.
 **/
Block *block_detach(Block *block)
{
    // TODO: Detach block from neighbors by updating previous and next block
    return block;
}

/**
 * Attempt to merge source block into destination.
 *
 *  1. Compute end of destination and start of source.
 *
 *  2. If they both match, then merge source into destionation by giving the
 *  destination all of the memory allocated to source.
 *
 * @param   dst     Destination block we are merging into.
 * @param   src     Source block we are merging from.
 * @return  Whether or not the merge completed successfully.
 **/
bool block_merge(Block *dst, Block *src)
{
    // TODO: Implement block merge
    // Counters[MERGES]++;
    // Counters[BLOCKS]--;
    return false;
}

/**
 * Attempt to split block with the specified size:
 *
 *  1. Check if aligned block size is sufficient for requested size and header
 *  Block.
 *  2. Split specified block into two blocks.
 *
 * @param   block   Pointer to block to split into two separate blocks.
 * @param   size    Desired size of the first block after split.
 * @return  Pointer to original block if the split was successfully or NULL if a
 * split was not possible.
 **/
Block *block_split(Block *block, size_t size)
{
    // TODO: Implement block split
    // Counters[SPLITS]++;
    // Counters[BLOCKS]++;
    return NULL;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
