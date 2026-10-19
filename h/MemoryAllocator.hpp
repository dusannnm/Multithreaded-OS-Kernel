//
// Created by os on 8/12/25.
//

#ifndef PROJECT_BASE_MEMORYALLOCATOR_HPP
#define PROJECT_BASE_MEMORYALLOCATOR_HPP

#include "../lib/hw.h"


class MemoryAllocator
{
public:
    static void* mem_alloc(size_t size);
    static uint32 mem_free(void* ptr);
<<<<<<< HEAD
    static size_t mem_get_free_space();
    static size_t mem_get_largest_free_block();
=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

private:
    struct dataBlock
    {
        size_t size;
        dataBlock *next;
        dataBlock *prev;
    };

    static dataBlock* free;
    static dataBlock* used;
    static uint32 init;
    static void connectBlocks(dataBlock* current);
};


#endif //PROJECT_BASE_MEMORYALLOCATOR_HPP