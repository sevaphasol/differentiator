#ifndef NODE_ALLOCATOR_H__
#define NODE_ALLOCATOR_H__

//———————————————————————————————————————————————————————————————————//

#include <stdint.h>
#include <stdlib.h>

#include "diff.h"

//———————————————————————————————————————————————————————————————————//

enum NodeAllocatorStatus
{
    NODE_ALLOCATOR_SUCCESS = 0,
    NODE_ALLOCATOR_STRUCT_NULL_PTR_ERROR,
    NODE_ALLOCATORE_STD_CALLOC_ERROR,
    NODE_ALLOCATOR_INVALID_NEW_NODE_ERROR,
    NODE_ALLOCATOR_BIG_ARRAY_REALLOC_ERROR,
    NODE_ALLOCATOR_ARRAYS_CALLOC_ERROR,
};

//————————————————————————————————————————————————//

struct Node_t
{
    ArgType  arg_type;
    uint64_t val;

    Node_t*  left;
    Node_t*  right;
};

struct NodeAllocator_t
{
    size_t   n_arrays;
    size_t   n_nodes_in_array;
    Node_t** big_array;

    int      free_place;
};

//————————————————————————————————————————————————//

NodeAllocatorStatus NodeAllocatorCtor (NodeAllocator_t* node_allocator,
                                       size_t           n_arrays,
                                       size_t           n_nodes_in_array);

NodeAllocatorStatus NodeAllocatorDtor (NodeAllocator_t* allocator);

//------------------------------------------------//

Node_t* NodeCtor (NodeAllocator_t* node_allocator,
                  ArgType          arg_type,
                  uint64_t         val,
                  Node_t*          left,
                  Node_t*          right);

//————————————————————————————————————————————————//

#endif // NODE_ALLOCATOR_H__
