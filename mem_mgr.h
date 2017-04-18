//
// Created by vsevolod on 17.04.17.
//

#pragma once

#include <cstdint>
#include <list>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

class Pool {
public:
    Pool (size_t _elem_size);
    void* add_element ();
    void delete_element(void* ptr);
    void free_pool ();
    bool is_ptr_belongs (void* ptr);
    bool is_ptr_in_chunk (void* ptr);

private:
    void extend_pool (uint32_t new_elem_num);

    struct PoolElement {
        void* mem_addr;
        bool is_occupied;
    };

    uint32_t elem_num;
    size_t elem_size;
    std::list<PoolElement> free_mem;
    std::list<PoolElement> occupied_mem;
    std::vector<char*> chunks_start;
};

class MemoryManager {
public:
    static MemoryManager& instance () {
        static MemoryManager memoryManager;
        return memoryManager;
    }

    template <typename T>
    T* allocate ();
    template <typename T>
    void deallocate (T* ptr);
    template <typename T>
    bool is_belongs_to_pool (T* ptr);
    template <typename T1, typename T2>
    bool is_ptrs_are_equal (T1* ptr_lhs, T2* ptr_rhs);
    void free_pools () {
        for (auto &&pool : pools)
            pool.second.free_pool();
    };



private:
    MemoryManager () {}
    ~MemoryManager() { free_pools(); }
    MemoryManager(MemoryManager const&) = delete;
    MemoryManager& operator= (MemoryManager const&) = delete;

    std::vector<std::pair<uint32_t, Pool>>::iterator find_pool (uint32_t debug_typeid);

    std::vector<std::pair<uint32_t, Pool>> pools;
};

template<typename T>
T* MemoryManager::allocate() {
    std::cout << "Alloc id: " << T::debug_typeid << std::endl;
    auto existing_pool_iter = find_pool(T::debug_typeid);
    if (existing_pool_iter == pools.end()) {
        std::cout << "Can't find pool" << std::endl;
        Pool new_pool (sizeof(T));
        uint32_t debug_typeid = T::debug_typeid;
        pools.push_back(std::make_pair(debug_typeid, new_pool));
        existing_pool_iter = pools.end();
        std::advance(existing_pool_iter, -1);
    }
    void* mem_chunk =  existing_pool_iter->second.add_element();
    return new(mem_chunk) T;
}

template<typename T>
void MemoryManager::deallocate(T* ptr) {
    auto existing_pool_iter = find_pool(T::debug_typeid);
    if (existing_pool_iter == pools.end()) {
        std::cerr << "Can't find pool to deallocate " << (void*)ptr << std::endl;
        return;
    }
    existing_pool_iter->second.delete_element(ptr);
}

template<typename T>
bool MemoryManager::is_belongs_to_pool(T *ptr) {
    auto pool_iter = find_pool(T::debug_typeid);
    if (pool_iter == pools.end()) {
        std::cout <<"Can't find pool for ptr" << std::endl;
        return false;
    }
    return pool_iter->second.is_ptr_in_chunk(ptr);
}

template<typename T1, typename T2>
bool MemoryManager::is_ptrs_are_equal(T1 *ptr_lhs, T2 *ptr_rhs) {
    if (ptr_lhs == NULL || ptr_rhs == NULL)
        return (void*)ptr_lhs == (void*)ptr_rhs;
    return (T1::debug_typeid == T2::debug_typeid) &&
           ((void*)ptr_lhs == (void*)ptr_rhs);
}
