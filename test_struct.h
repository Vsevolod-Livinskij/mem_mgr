//
// Created by vsevolod on 17.04.17.
//

#pragma once

#include <uuid/uuid.h>
#include <cstdint>

#include "mem_mgr.h"

struct A {
    int mem1;
    long long int mem2;

    static int get_mem1 (A* ptr);
    static void set_mem1 (A* ptr, int val);
    static long long int get_mem2 (A* ptr);
    static void set_mem2 (A* ptr, long long int val);

    static constexpr uint32_t debug_typeid = 1; // Replace type with uuid_t
    static A* create ();
    static void remove (A* ptr);
    static bool is_ptr_are_equal (A* ptr_lhs, A* ptr_rhs);

private:
    A () {}
    static bool is_ok (A* ptr);
    template <typename T>
    friend T* MemoryManager::allocate();
};

struct B {
    double mem1;

    static double get_mem1 (B* ptr);
    static void set_mem1 (B* ptr, double val);

    static constexpr uint32_t debug_typeid = 2; // Replace type with uuid_t
    static B* create ();
    static void remove (B* ptr);

private:
    B () {}
    static bool is_ok (B* ptr);
    template <typename T>
    friend T* MemoryManager::allocate();
};

