#include <iostream>

#include "test_struct.h"

#ifndef TEST_CASE
    #define TEST_CASE 0
#endif

void test () {
#if TEST_CASE == 0
    A* obj = A::create();
    A::set_mem1(obj, 123);
    std::cout << "Init value: " << A::get_mem1(obj) << std::endl;
    A::remove(obj);
#endif

#if TEST_CASE == 1
    A* obj = nullptr;
    A::set_mem1(obj, 123);
    std::cout << "Init value: " << A::get_mem1(obj) << std::endl;
#endif

#if TEST_CASE == 2
    A* obj = A::create();
    A::set_mem1(obj, 123);
    std::cout << "Init value: " << A::get_mem1(obj) << std::endl;
    A::remove(obj);
    A::set_mem1(obj, 111);
    std::cout << "Set value: " << A::get_mem1(obj) << std::endl;
#endif

#if TEST_CASE == 3
    A* obj;
    A::set_mem1(obj, 123);
    std::cout << "Init value: " << A::get_mem1(obj) << std::endl;
#endif

#if TEST_CASE == 4
    A* obj_A = A::create();
    B* obj_B = (B*) obj_A;
    B::set_mem1(obj_B, 100);
    std::cout << "Init value: " << B::get_mem1(obj_B) << std::endl;
#endif

#if TEST_CASE == 5
    A* obj_A1 = A::create();
    A* obj_A2 = obj_A1;
    MemoryManager& memoryManager = MemoryManager::instance();
    std::cout << "Equal: " << memoryManager.is_ptrs_are_equal(obj_A1, obj_A2) << std::endl;
    B* obj_B1 = B::create();
    std::cout << "Not equal: " << memoryManager.is_ptrs_are_equal(obj_B1, obj_A1) << std::endl;
    B* obj_B2 = (B*) obj_A1;
    std::cout << "Also not equal: " << memoryManager.is_ptrs_are_equal(obj_B1, obj_B2) << std::endl;
    A::remove(obj_A1);
    B::remove(obj_B1);
#endif

#if TEST_CASE == 6
    A* obj = A::create();
    obj = obj + 1;
    A::set_mem1(obj, 123);
    std::cout << "Ok: " << (A::get_mem1(obj) == 123) << std::endl;
    obj = obj + 2;
    std::cout << "Not ok: " << (A::get_mem1(obj) == 123) << std::endl;
#endif

#if TEST_CASE == 7
    A* obj = A::create();
    A::set_mem1(obj, 123);
    std::cout << "Init value: " << A::get_mem1(obj) << std::endl;
#endif
}

int main() {
    test();
    return 0;
}