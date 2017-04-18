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

bool A::is_ok(A* ptr) {
    if (ptr == nullptr) {
        std::cerr << "Error: NULL ptr access" << std::endl;
        exit(-1);
    }
    MemoryManager& memoryManager = MemoryManager::instance();
    return memoryManager.is_belongs_to_pool<A>(ptr);
}

int A::get_mem1(A* ptr) {
    if (!is_ok(ptr)) {
        std::cerr << "Can't get mem_1 in A" << std::endl;
        exit(-1);
    }
    return ptr->mem1;
}

void A::set_mem1(A *ptr, int val) {
    if (!is_ok(ptr)) {
        std::cerr << "Can't set mem_1 in A" << std::endl;
        exit(-1);
    }
    ptr->mem1 = val;
}

long long int A::get_mem2(A* ptr) {
    if (!is_ok(ptr)) {
        std::cerr << "Can't get mem_2 in A" << std::endl;
        exit(-1);
    }
    return ptr->mem2;
}

void A::set_mem2(A *ptr, long long int val) {
    if (!is_ok(ptr)) {
        std::cerr << "Can't set mem_2 in A" << std::endl;
        exit(-1);
    }
    ptr->mem2 = val;
}

bool A::is_ptr_are_equal(A* ptr_lhs, A* ptr_rhs) {
    if (!is_ok(ptr_lhs) || !is_ok(ptr_rhs)) {
        std::cerr << "Can't check for equality A" << std::endl;
        exit(-1);
    }
    return ptr_lhs == ptr_rhs;
}

B *B::create () {
    MemoryManager& memoryManager = MemoryManager::instance();
    return memoryManager.allocate<B>();
}

void B::remove (B* ptr) {
    MemoryManager& memoryManager = MemoryManager::instance();
    memoryManager.deallocate(ptr);
}

bool B::is_ok(B* ptr) {
    if (ptr == nullptr) {
        std::cerr << "Error: NULL ptr access" << std::endl;
        exit(-1);
    }
    MemoryManager& memoryManager = MemoryManager::instance();
    return memoryManager.is_belongs_to_pool<B>(ptr);
}

double B::get_mem1(B* ptr) {
    if (!is_ok(ptr)) {
        std::cerr << "Can't get mem_1 in B" << std::endl;
        exit(-1);
    }
    return ptr->mem1;
}

void B::set_mem1(B *ptr, double val) {
    if (!is_ok(ptr)) {
        std::cerr << "Can't set mem_1 in B" << std::endl;
        exit(-1);
    }
    ptr->mem1 = val;
}
