#ifndef ALLOCATOR
#define ALLOCATOR
#include <string>
#include <iostream>

// Forward declaration. Do not include real class definition
// to avoid expensive macros calculations and increase compile speed

#define BLOCK_NUM 100

class Pointer;

struct List_node;
/**
 * Wraps given memory area and provides defagmentation allocator interface on
 * the top of it.
 *
 *
 */
class Allocator {
private:
    void* base;
    size_t size;
    unsigned int count;

    List_node* inner_alloc(size_t size, List_node* iter);

//    void* head;
public:
    Allocator(void* _base, size_t _size);
    /**
     * TODO: semantics
     * @param N size_t
     */
    Pointer alloc(size_t N);

    /**
     * TODO: semantics
     * @param p Pointer
     * @param N size_t
     */
    void realloc(Pointer& p, size_t N);

    /**
     * TODO: semantics
     * @param p Pointer
     */
    void free(Pointer& p);

    /**
     * TODO: semantics
     */
    void defrag();

    /**
     * TODO: semantics
     */
    std::string dump() const { return ""; }
};

#endif // ALLOCATOR
