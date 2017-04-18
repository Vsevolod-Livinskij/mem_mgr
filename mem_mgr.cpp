//
// Created by vsevolod on 17.04.17.
//

#include "mem_mgr.h"

#define POOL_DEFAULT_SIZE 2

std::vector<std::pair<uint32_t, Pool>>::iterator MemoryManager::find_pool(uint32_t debug_typeid) {
    auto pool_cmp_function = [debug_typeid] (auto pool) {
        return pool.first == debug_typeid;
    };
    return std::find_if(pools.begin(), pools.end(), pool_cmp_function);
}

Pool::Pool(size_t _elem_size) : elem_num (POOL_DEFAULT_SIZE), elem_size(_elem_size) {
    extend_pool(elem_num);
}

void *Pool::add_element() {
    std::cout << "Add| Free: " << free_mem.size() << " Occupied: " << occupied_mem.size() << std::endl;
    if (free_mem.size() == 0)
        extend_pool(occupied_mem.size() * 2);
    PoolElement& free_chunk = free_mem.front();
    free_chunk.is_occupied = true;
    occupied_mem.push_back(free_chunk);
    free_mem.erase(free_mem.begin());
    std::cout << "After| Free: " << free_mem.size() << " Occupied: " << occupied_mem.size() << std::endl;
    std::cout << occupied_mem.front().is_occupied << std::endl;
    return free_chunk.mem_addr;
}

void Pool::extend_pool(uint32_t new_elem_num) {
    std::cout << "Start extend| Free: " << free_mem.size() << " Occupied: " << occupied_mem.size() << std::endl;
    char* memory = (char*) malloc(elem_size * new_elem_num);
    if (memory == NULL) {
        std::cerr << "Not enough memory!" << std::endl;
        exit(-1);
    }
    chunks_start.push_back(memory);
    std::cout << "Ext. chunk: " << (void*) memory << std::endl;
    for (int i = 0; i < new_elem_num; ++i) {
        char* mem_chunk_start = memory + i * elem_size;
        std::cout << "Chunk: " << (void*) mem_chunk_start << std::endl;
        PoolElement new_elem = {mem_chunk_start, false};
        free_mem.push_front(new_elem);
    }
    std::cout << "After extend| Free: " << free_mem.size() << " Occupied: " << occupied_mem.size() << std::endl;
}

void Pool::delete_element(void *ptr) {
    std::cout << "Start delete| Free: " << free_mem.size() << " Occupied: " << occupied_mem.size() << std::endl;
    auto ptr_find = [ptr] (PoolElement& poolElement) {
        return poolElement.mem_addr == ptr;
    };
    auto existing_element = std::find_if(occupied_mem.begin(), occupied_mem.end(), ptr_find);
    if (existing_element == occupied_mem.end()) {
        std::cerr << "Can't find and delete PoolElement" << std::endl;
        return;
    }
    existing_element->is_occupied = false;
    auto next_after_existing_element = existing_element;
    std::advance(next_after_existing_element, 1);
    free_mem.splice(free_mem.begin(), occupied_mem, existing_element, next_after_existing_element);
    std::cout << "After delete| Free: " << free_mem.size() << " Occupied: " << occupied_mem.size() << std::endl;
}

void Pool::free_pool() {
    if (occupied_mem.size() != 0) {
        std::cerr << "You have occupied memory at free_pool!" << std::endl;
        for (auto &&mem : occupied_mem)
            std::cerr << mem.mem_addr << std::endl;
    }
    for (auto &&chunk_start : chunks_start)
        free(chunk_start);
    free_mem.clear();
    occupied_mem.clear();
    chunks_start.clear();
    std::cout << "Pool now is free" << std::endl;
}
