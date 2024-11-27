#include "node_allocator.h"
#include "tree_dump.h"
#include "custom_assert.h"
#include "dsl.h"
#include "expression_reader.h"

//———————————————————————————————————————————————————————————————————//

const char* const Expression = "(^(sqrt(arcsin(sinh(x))))(2))";

//———————————————————————————————————————————————————————————————————//

int main()
{
    node_allocator_t  node_allocator = {};
    diff_context_t    ctx = {};

    //-------------------------------------------------------------------//

    VERIFY(diff_context_ctor(&ctx, &node_allocator),
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    node_t* root = prefix_expression_reader(&node_allocator, Expression);

    ctx.root = root;

    //-------------------------------------------------------------------//

    VERIFY(dump(&ctx, root) != DIFF_SUCCESS,
           diff_context_dtor(&ctx);
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    node_t* res = diff_tree(&ctx, root);

    //-------------------------------------------------------------------//

    VERIFY(dump(&ctx, res) != DIFF_SUCCESS,
           diff_context_dtor(&ctx);
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    VERIFY(diff_context_dtor(&ctx),
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    return EXIT_SUCCESS;
}
