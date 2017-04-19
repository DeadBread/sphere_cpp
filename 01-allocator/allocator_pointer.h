#ifndef ALLOCATOR_POINTER
#define ALLOCATOR_POINTER

#include <string>

// Forward declaration. Do not include real class definition
// to avoid expensive macros calculations and increase compile speed
class Allocator;

struct List_node {
    size_t block_size;
    bool is_free;
    void* block_start;
    List_node* next;
    List_node* previous;
    unsigned int id;
};

class Pointer {
private:
    List_node* base;
    unsigned int id;
public:
    Pointer() : base(nullptr), id(0)  {};
    Pointer(List_node* _base, unsigned int _id) :
                                                base(_base),
                                                id(_id)
                                                {};
    void* get() const;
    List_node* get_block_start() const;
};

#endif //ALLOCATOR_POINTER
