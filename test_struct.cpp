//
// Created by vsevolod on 17.04.17.
//

#include "test_struct.h"
#include "mem_mgr.h"

A *A::create () {
    MemoryManager& memoryManager = MemoryManager::instance();
    return memoryManager.allocate<A>();
}

void A::remove (A* ptr) {
    MemoryManager& memoryManager = MemoryManager::instance();
    memoryManager.deallocate(ptr);
}
