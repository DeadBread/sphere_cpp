#include "allocator_pointer.h"

void* Pointer::get() const {

    List_node* block_start = this->get_block_start();

    if (block_start->is_free)
        return nullptr;
    else
        return (void*) (block_start + 1);
}

List_node* Pointer::get_block_start() const {
    List_node* block_start = this->base;
    while (block_start->id != this->id)
        block_start = block_start->next;

    if (block_start == nullptr)
        throw ("weird!");

    return block_start;
}