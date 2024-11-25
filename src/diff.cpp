#include "node_allocator.h"
#include "diff.h"
#include "operations.h"
#include "custom_assert.h"

//———————————————————————————————————————————————————————————————————//

num_t calc_tree(node_t* root)
{
    num_t val = 0;

    switch (root->arg_type)
    {
        case NUM:
        {
            return root->val.num;
        }

        case OPR:
        {
            return OperationsTable[root->val.opr].calc_func(
                calc_tree(root->left),
                calc_tree(root->right));
        }

        default:
        {
            ASSERT(0);
        }
    }

    return DIFF_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//

node_t* diff_tree(node_allocator_t* node_allocator, node_t* root)
{
    ASSERT(root);

    //-------------------------------------------------------------------//

    return root->diff_func(node_allocator, root->left, root->right);

    // switch (root->arg_type)
    // {
    //     case NUM:
    //     {
    //         return node_ctor(node_allocator, NUM, {.num = 0}, nullptr, nullptr);
    //     }
    //     case VAR:
    //     {
    //         return node_ctor(node_allocator, NUM, {.num = 1}, nullptr, nullptr);
    //     }
    //     case OPR:
    //     {
    //         return OperationsTable[root->arg_type].
    //     }
    // }
}

//———————————————————————————————————————————————————————————————————//

node_t* copy_tree(node_t* root)
{
    return root;
}

//———————————————————————————————————————————————————————————————————//
