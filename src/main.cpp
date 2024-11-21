#include "node_allocator.h"
#include "tree_dump.h"
#include "custom_assert.h"

const int NumOfAllocatedNodeArrays   = 1;
const int NumOfNodesInAllocatedArray = 1024;

int main()
{
    NodeAllocator_t  node_allocator_struct = {};
    NodeAllocator_t* node_allocator        = &node_allocator_struct;

    VERIFY(NodeAllocatorCtor(node_allocator,
                             NumOfAllocatedNodeArrays,
                             NumOfNodesInAllocatedArray),
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    Node_t* root = _DIV(_ADD(_VAR, _NUM(3)), _SUB(_NUM(1000), _NUM(7)));

    // Node_t* root = NodeCtor(&node_allocator, OPR, DIV,
    //                    NodeCtor(&node_allocator, OPR, ADD,
    //                         NodeCtor(&node_allocator, VAR, 1,    nullptr, nullptr),
    //                         NodeCtor(&node_allocator, NUM, 3,    nullptr, nullptr)),
    //                    NodeCtor(&node_allocator, OPR, SUB,
    //                         NodeCtor(&node_allocator, NUM, 1000, nullptr, nullptr),
    //                         NodeCtor(&node_allocator, NUM, 7,    nullptr, nullptr)));

    //-------------------------------------------------------------------//

    VERIFY(Dump(root, "TreeDump") != TREE_DUMP_SUCCESS,
           NodeAllocatorDtor(node_allocator);
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    VERIFY(NodeAllocatorDtor(node_allocator),
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    return EXIT_SUCCESS;
}
