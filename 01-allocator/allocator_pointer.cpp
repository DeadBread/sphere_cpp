#include "allocator_pointer.h"

void* Pointer::get() const {
    if (this->block_start->is_free)
        return nullptr;
    else
        return address;
}