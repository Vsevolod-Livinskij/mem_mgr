//
// Created by vsevolod on 17.04.17.
//

#pragma once

#include <uuid/uuid.h>
#include <cstdint>

#include "mem_mgr.h"

struct A {
    int mem1;
    double mem2;

    int get_mem1 ();
    bool set_mem1 (int val);

    static constexpr uint32_t debug_typeid = 1; // Replace type with uuid_t
    static A* create ();
    static void remove (A* ptr);

private:
    A () {}
    template <typename T>
    friend T* MemoryManager::allocate();
};

struct B {
    int mem1;
    double mem2;

//This field should always be private, even in structs
    static constexpr uint32_t debug_typeid = 2; // Replace type with uuid_t
    B () {}

    static constexpr uint32_t get_debug_typeid() { return debug_typeid; }
    static B* create_B ();
};

