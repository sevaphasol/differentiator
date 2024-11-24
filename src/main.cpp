#include "node_allocator.h"
#include "tree_dump.h"
#include "custom_assert.h"
#include "dsl.h"
#include "io.h"

const int nAllocatedNodes = 1024;

int main()
{
    node_allocator_t  node_allocator_struct = {};
    node_allocator_t* node_allocator        = &node_allocator_struct;

    VERIFY(node_allocator_ctor(node_allocator, nAllocatedNodes),
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    // node_t* root = _DIV(_ADD(_NUM(990), _NUM(3)), _SUB(_NUM(1000), _NUM(7)));
    // node_t* root = prefix_expression_reader(node_allocator, "(/(+(-(12.1)(x))(12))(12))");
    node_t* root = prefix_expression_reader(node_allocator, "(-(*(x)(2))(2))");

//     node_t* root = node_ctor(node_allocator, OPR, {.opr = DIV},
//                        node_ctor(node_allocator, OPR, {.opr = ADD},
//                             node_ctor(node_allocator, VAR, {.var = X},    nullptr, nullptr),
//                             node_ctor(node_allocator, NUM, {.num = 3},    nullptr, nullptr)),
//                        node_ctor(node_allocator, OPR, {.opr = SUB},
//                             node_ctor(node_allocator, NUM, {.num = 1000}, nullptr, nullptr),
//                             node_ctor(node_allocator, NUM, {.num = 7},    nullptr, nullptr)));

    //-------------------------------------------------------------------//

    VERIFY(tree_dump(root, "TreeDump") != TREE_DUMP_SUCCESS,
           node_allocator_dtor(node_allocator);
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    node_t* res = diff_tree(node_allocator, root);

    //-------------------------------------------------------------------//

    VERIFY(tree_dump(res, "DiffTreeDump") != TREE_DUMP_SUCCESS,
           node_allocator_dtor(node_allocator);
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

//     num_t res = calc_tree(root);
//
//     printf("%lf\n", res);

    //-------------------------------------------------------------------//

//     node_t* root_ = prefix_expression_reader(node_allocator, "(/(1)(2))");
//
//     VERIFY(tree_dump(root_, "TreeDump_") != TREE_DUMP_SUCCESS,
//            node_allocator_dtor(node_allocator);
//            return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    VERIFY(node_allocator_dtor(node_allocator),
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    return EXIT_SUCCESS;
}
