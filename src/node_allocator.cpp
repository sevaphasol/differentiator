#include <stdlib.h>

//-------------------------------------------------------------------//

#include "node_allocator.h"
#include "custom_assert.h"

//———————————————————————————————————————————————————————————————————//

static NodeAllocatorStatus BigArrayRealloc (NodeAllocator_t* node_allocator);
static NodeAllocatorStatus ArraysCalloc    (NodeAllocator_t* node_allocator);

//———————————————————————————————————————————————————————————————————//

NodeAllocatorStatus NodeAllocatorCtor(NodeAllocator_t* node_allocator,
                                      size_t           n_arrays,
                                      size_t           n_nodes_in_array)
{
    VERIFY(!node_allocator,
           return NODE_ALLOCATOR_STRUCT_NULL_PTR_ERROR);

    //-------------------------------------------------------------------//

    node_allocator->n_arrays  = n_arrays;

    node_allocator->big_array = (Node_t**) calloc(n_arrays, sizeof(Node_t**));
    VERIFY(!node_allocator->big_array,
           return NODE_ALLOCATORE_STD_CALLOC_ERROR);

    //-------------------------------------------------------------------//

    node_allocator->n_nodes_in_array = n_nodes_in_array;

    for (int i = 0; i < n_arrays; i++)
    {
        node_allocator->big_array[i] = (Node_t*) calloc (n_nodes_in_array, sizeof(Node_t*));
        VERIFY(!node_allocator->big_array[i],
               return NODE_ALLOCATORE_STD_CALLOC_ERROR);
    }

    //-------------------------------------------------------------------//

    node_allocator->free_place = 0;

    //-------------------------------------------------------------------//

    return NODE_ALLOCATOR_SUCCESS;
}

//===================================================================//

NodeAllocatorStatus NodeAllocatorDtor(NodeAllocator_t* node_allocator)
{
    VERIFY(!node_allocator,
           return NODE_ALLOCATOR_STRUCT_NULL_PTR_ERROR);

    //-------------------------------------------------------------------//

    for (int i = 0; i < node_allocator->n_arrays; i++)
    {
        free(node_allocator->big_array[i]);
    }

    //-------------------------------------------------------------------//

    free(node_allocator->big_array);

    //-------------------------------------------------------------------//

    node_allocator->free_place       = 0;
    node_allocator->n_arrays         = 0;
    node_allocator->n_nodes_in_array = 0;

    //-------------------------------------------------------------------//

    return NODE_ALLOCATOR_SUCCESS;
}

//===================================================================//

Node_t* NodeCtor(NodeAllocator_t* node_allocator,
                 ArgType          arg_type,
                 uint64_t         val,
                 Node_t*          left,
                 Node_t*          right)
{
    VERIFY(!node_allocator, return nullptr);

    //-------------------------------------------------------------------//

    if (node_allocator->free_place >= node_allocator->n_arrays * node_allocator->n_nodes_in_array)
    {
        VERIFY(BigArrayRealloc(node_allocator), return nullptr);
        VERIFY(ArraysCalloc   (node_allocator), return nullptr);
    }

    //-------------------------------------------------------------------//

    size_t cur_array      = node_allocator->free_place / node_allocator->n_nodes_in_array;
    size_t rel_free_place = node_allocator->free_place % node_allocator->n_nodes_in_array;

    Node_t* new_node = &node_allocator->big_array[cur_array][rel_free_place];

    node_allocator->free_place++;

    //-------------------------------------------------------------------//

    new_node->arg_type = arg_type;
    new_node->val      = val;
    new_node->left     = left;
    new_node->right    = right;

    //-------------------------------------------------------------------//

    return new_node;
}

//===================================================================//

NodeAllocatorStatus BigArrayRealloc(NodeAllocator_t* node_allocator)
{
    return NODE_ALLOCATOR_SUCCESS;
}

//===================================================================//

NodeAllocatorStatus ArraysCalloc(NodeAllocator_t* node_allocator)
{
    return NODE_ALLOCATOR_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//
