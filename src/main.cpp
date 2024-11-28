#include "node_allocator.h"
#include "tree_dump.h"
#include "custom_assert.h"
#include "dsl.h"
#include "expression_reader.h"

//———————————————————————————————————————————————————————————————————//

const char* const Expression = "(*(+(arctan(x))(-(sinh(^(x)(2)))(sqrt(^(x)(2)))))(sinh(cosh(ln(x)))))";
// const char* const Expression = "(+(+(x)(x))(0))";
// const char* const Expression = "(sqrt(-(^(x)(2))(1))))";
// const char* const Expression = "(^(*(sqrt(x))(ln(x)))(+(x)(x)))";
// const char* const Expression = "(^(x)(3))";
// const char* const Expression = "(*(/(x)(sin(x)))(x))";

//———————————————————————————————————————————————————————————————————//

int main() // GNU plot
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

    VERIFY(write_tex_intro(&ctx) != DIFF_SUCCESS,
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    node_t* res = diff_tree(&ctx, root);
    dot_dump(&ctx, res);

    //-------------------------------------------------------------------//

    VERIFY(write_tex_outro(&ctx) != DIFF_SUCCESS,
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    VERIFY(diff_context_dtor(&ctx),
           return EXIT_FAILURE);

    //-------------------------------------------------------------------//

    return EXIT_SUCCESS;
}
