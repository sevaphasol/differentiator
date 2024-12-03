#include "node_allocator.h"
#include "tex_dump.h"
#include "custom_assert.h"
#include "dsl.h"
#include "expression_reader.h"
#include "graph_dump.h"

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

    VERIFY(taylor(&ctx, root, 5, 0) != DIFF_SUCCESS,
           return EXIT_FAILURE)

    //-------------------------------------------------------------------//

    VERIFY(diff_context_dtor(&ctx),
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    return EXIT_SUCCESS;
}
