#include <iostream>

#include "test_struct.h"

int main() {
    std::vector<A*> tmp;
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 30; ++i) {
            std::cout << "iter# " << i << std::endl;
            A *obj = A::create();
            obj->mem1 = i;
            std::cout << obj->mem1 << std::endl;
            tmp.push_back(obj);
        }
        std::cout << "===============" << std::endl;
        for (int i = 0; i < 30; ++i) {
            std::cout << "iter# " << i << std::endl;
            A::remove(tmp.at(i));
        }
    }
    auto& mem_mgr = MemoryManager::instance();
    mem_mgr.free_pools();
    return 0;
}