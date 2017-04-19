#include "allocator_pointer.h"

void* Pointer::get() const {

    List_node* block_start = this->get_block_start();
    if (block_start == nullptr)
        return nullptr;

    if (block_start->is_free)
        return nullptr;
    else
        return (void*) (block_start + 1);
}

List_node* Pointer::get_block_start() const {
    List_node* block_start = (List_node*) this->base;
    if (block_start == nullptr)
        return nullptr;
    while (block_start->id != this->id)
        block_start = block_start->next;

    return block_start;
}