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
};

class Pointer {
private:
    void* address;
    List_node* block_start;
public:
    Pointer() : address(nullptr), block_start(nullptr) {};
    Pointer(void* _address, List_node* _block_start) :
                                                                address(_address),
                                                                block_start(_block_start)
                                                                {};
    void* get() const;
    List_node* get_block_start() const {return block_start;}
};

#endif //ALLOCATOR_POINTER
