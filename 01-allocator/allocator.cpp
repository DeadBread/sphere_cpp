#include "allocator.h"
#include "allocator_pointer.h"
#include "allocator_error.h"

Allocator::Allocator(void *_base, size_t _size) : base(_base), size(_size), count(0) {
    if (size < BLOCK_NUM) {
        std::cout << "small pool" << std::endl;
        base = nullptr;
    }
    else {
        //creating temporary node
        List_node tmp_node = {size - sizeof(List_node),
                              true,
                              (char*) base + sizeof(List_node),
                              nullptr,
                              nullptr,
                              count};
        List_node* tmp_ptr = (List_node*) base;
        *tmp_ptr = tmp_node;
    }
}

List_node* Allocator::inner_alloc(size_t size, List_node* iter) {
    List_node tmp_old = *iter;

    List_node* next_ptr = (List_node*) ((char*)iter -> block_start + size);
    List_node tmp_node = {size,
                          false,
                          iter -> block_start,
                          next_ptr,
                          tmp_old.previous,
                          tmp_old.id};
    *iter = tmp_node;

    if (tmp_old.block_size > size + sizeof(List_node)) {

        List_node tmp_next = {tmp_old.block_size - size - sizeof(List_node),
                              true,
                              (void *) (next_ptr + 1),
                              tmp_old.next,
                              iter,
                              ++this->count};
        *next_ptr = tmp_next;

        next_ptr->previous = iter;
    }
    else {
        iter->next = tmp_old.next;
        if (iter->next != nullptr)
            iter->next->previous = iter;
    }
    return iter;
}


Pointer Allocator::alloc(size_t N) {
    List_node* iter = (List_node*) base;
    List_node* deb;
    while ((! iter -> is_free) ||
           (iter -> block_size < N)) {
        if (iter -> next == nullptr) {
            throw (AllocError(AllocErrorType::NoMemory, "string"));
        }

        deb = iter;
        iter = iter -> next;
    }
//    std::cout << deb << std::endl;

    iter = this->inner_alloc(N, iter);

    return Pointer((List_node*) this->base, iter->id);
}

void Allocator::free(Pointer& p) {
    List_node *tmp = p.get_block_start();

    if (tmp->is_free)
        throw AllocError(AllocErrorType::InvalidFree, "another string");

    tmp->is_free = true;

//    merging neighbouring free blocks
    if ((tmp->next != nullptr) && (tmp->next->is_free)) {
        tmp->block_size += tmp->next->block_size + sizeof(List_node);
        tmp->next = tmp->next->next;
    }

    if ((tmp->previous != nullptr) && (tmp->previous->is_free)) {
        tmp->previous->block_size += tmp->block_size + sizeof(List_node);
        tmp->previous->next = tmp->next;
    }
}

void Allocator::realloc(Pointer& p, size_t N) {

    if (p.get() == nullptr) {
        p = this->alloc(N);
        return;
    }

    List_node* tmp = p.get_block_start();

    if (tmp->block_size > N) {
        tmp->is_free = true;
        tmp = this->inner_alloc(N, tmp);
//        List_node* new_tmp = new_tmp_pointer.get_block_start();
//        new_tmp->id = tmp->id;
    }

//    if we are staying at the same place
    if (tmp->next->is_free) {
        if (tmp->block_size + tmp->next->block_size + sizeof(List_node) >= N) {
            tmp->block_size = tmp->block_size + tmp->next->block_size + sizeof(List_node);
            tmp->next = tmp->next->next;
            tmp = inner_alloc(N, tmp);
        }
    }
    else {
        p = this->alloc(N);
        List_node* new_tmp = p.get_block_start();
//        new_tmp->id = tmp->id;

        void* new_mem_start = new_tmp->block_start;

        for (int i = 0; i < tmp->block_size; i++)
            *((char*)new_mem_start + i) = *((char*)tmp->block_start + i);

        tmp->is_free = true;

        return;
    }
}

void Allocator::defrag() {
    List_node *iter = (List_node*) this->base;
    void* target = iter->is_free ? (char*) this->base + iter->block_size + sizeof(List_node) : this->base;
    List_node *previous = nullptr;
    while (iter != nullptr) {
        if (! iter->is_free) {
            List_node* new_node = ((List_node*) target);
            (*new_node) = (*iter);
            new_node->previous = previous;

            for (int i = 0; i < iter->block_size; i++)
                *((char*)target + sizeof(List_node) + i) = *((char*)iter + sizeof(List_node) + i);

            target = (void*) ((char*) target + sizeof(List_node) + iter->block_size);  //could it look any better?

            if (iter->next == nullptr)
                new_node->next = nullptr;
            else
                new_node->next = (List_node*) target;

            previous = new_node;
        }
        iter = iter->next;
    }

    unsigned int free_space = this->size - (unsigned int) ((char*)target - (char*)this->base);
    List_node tmp_final_node = {free_space - sizeof(List_node),
                                true,
                                (void*)((char*)target + sizeof(List_node)),
                                nullptr,
                                previous,
                                ++this->count};
    *((List_node*) target) = tmp_final_node;
    previous->next = (List_node*) target;

}
