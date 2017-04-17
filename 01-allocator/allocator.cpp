#include "allocator.h"
#include "allocator_pointer.h"
#include "allocator_error.h"

Allocator::Allocator(void *_base, size_t _size) : base(_base), size(_size) {
    if (size < BLOCK_NUM) {
        std::cout << "small pool" << std::endl;
        base = nullptr;
    }
    else {
        //creating temporary node
        List_node tmp_node = {size - sizeof(List_node),
                              true,
                              (char*) base + sizeof(List_node),
                              nullptr};
        List_node* tmp_ptr = (List_node*) base;
        *tmp_ptr = tmp_node;
    }
}


Pointer Allocator::alloc(size_t N) {
    List_node* iter = (List_node*) base;
    while ((! iter -> is_free) ||
           (iter -> block_size < N)) {
        if (iter -> next == nullptr)
            throw(AllocError(AllocErrorType::NoMemory, "string"));
        iter = iter -> next;
    }

    List_node tmp_old = *iter;

    List_node* next_ptr = (List_node*) ((char*)iter -> block_start + N);
    List_node tmp_node = {N,
                          false,
                          iter -> block_start,
                          next_ptr};
    *iter = tmp_node;

    if (tmp_old.block_size > N + sizeof(List_node)) {

        List_node tmp_next = {tmp_old.block_size - N - sizeof(List_node),
                              true,
                              (void *) (next_ptr + 1),
                              tmp_old.next};
        *next_ptr = tmp_next;
    }
    else {
//        throw ("wow");
        iter->next = tmp_old.next;
    }

    return Pointer((void*)(iter + 1), iter);
}

void Allocator::free(Pointer& p) {
    List_node *tmp = p.get_block_start();
    tmp->is_free = true;
//    merging neighbouring free blocks
    if (tmp->next->is_free) {
        tmp->block_size += tmp->next->block_size + sizeof(List_node);
        tmp->next = tmp->next->next;
    }
}
