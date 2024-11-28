#include "custom_assert.h"
#include "dsl.h"
#include "operations.h"
#include "tree_dump.h"
#include "node_allocator.h"

//———————————————————————————————————————————————————————————————————//

#define _SIMPLIFY_FUNC(name, code)                                     \
node_t* simplify_##name(diff_context_t* ctx, node_t* node)             \
{                                                                      \
    ASSERT(ctx);                                                       \
    ASSERT(node);                                                      \
                                                                       \
    node_allocator_t* node_allocator = ctx->node_allocator;            \
    node_t* l = node->left;                                            \
    node_t* r = node->right;                                           \
    node_t* simplified_node = nullptr;                                 \
                                                                       \
    if (l) {_SIMPLIFY(l);}                                             \
    if (r) {_SIMPLIFY(r);}                                             \
                                                                       \
    bool simplified = false;                                           \
                                                                       \
    _TRY_CALC(node)                                                    \
                                                                       \
    code                                                               \
                                                                       \
    if (simplified)                                                    \
    {                                                                  \
        *node = *simplified_node;                                      \
    }                                                                  \
                                                                       \
                                                                       \
    return nullptr;                                                    \
}                                                                      \

//-------------------------------------------------------------------//

#define _PRINT(...) fprintf(ctx->dump_info.tex_file, ##__VA_ARGS__)

#define _CHECK_IF_SIMPLE(con, new_node) \
if (con)                                \
{                                       \
    simplified_node = new_node;         \
    simplified = true;                  \
}                                       \

#define _TRY_CALC(node)                                 \
if (l && l->arg_type == NUM && r && r->arg_type == NUM) \
{                                                       \
    _PRINT("Упростим\n");                               \
                                                        \
    _PRINT("\n\\begin{equation}\n");                    \
                                                        \
    _TEX(node);                                         \
    _PRINT(" = ");                                      \
                                                        \
    try_calc(node);                                     \
    _TEX(node);                                         \
    _PRINT("\n\\end{equation}\n");                      \
}                                                       \

//———————————————————————————————————————————————————————————————————//

_SIMPLIFY_FUNC(num,

)

//===================================================================//

_SIMPLIFY_FUNC(var,

)

//===================================================================//

_SIMPLIFY_FUNC(add,
    _CHECK_IF_SIMPLE(l->arg_type == NUM && l->val.num == 0,
                     r)

    _CHECK_IF_SIMPLE(r->arg_type == NUM && r->val.num == 0,
                     l)
)

//===================================================================//

_SIMPLIFY_FUNC(sub,
    _CHECK_IF_SIMPLE(l->arg_type == NUM && l->val.num == 0,
                     _MUL(_NUM(-1), node))

    _CHECK_IF_SIMPLE(r->arg_type == NUM && r->val.num == 0,
                     l)
)

//===================================================================//

_SIMPLIFY_FUNC(mul,
    _CHECK_IF_SIMPLE((l->arg_type == NUM && l->val.num == 0) ||
                     (r->arg_type == NUM && r->val.num == 0),
                     _NUM(0))

    _CHECK_IF_SIMPLE(l->arg_type == NUM && l->val.num == 1,
                     r)

    _CHECK_IF_SIMPLE(r->arg_type == NUM && r->val.num == 1,
                     l)
)

//===================================================================//

_SIMPLIFY_FUNC(div,
    _CHECK_IF_SIMPLE(l->arg_type == NUM && l->val.num == 0,
                     r)

    _CHECK_IF_SIMPLE(r->arg_type == NUM && r->val.num == 1,
                     l)
)

//===================================================================//

_SIMPLIFY_FUNC(sqrt,
    _CHECK_IF_SIMPLE(l->arg_type == OPR && l->val.opr == POW &&
                                           l->right->arg_type == NUM &&
                                           l->right->val.num == 2,
                     l->left)
)

//===================================================================//

_SIMPLIFY_FUNC(pow,
    _CHECK_IF_SIMPLE(l->arg_type == NUM && l->val.num == 1,
                     l)

    _CHECK_IF_SIMPLE(r->arg_type == NUM && r->val.num == 1,
                     l)

    _CHECK_IF_SIMPLE(r->arg_type == NUM && r->val.num == 0,
                     _NUM(1))
)

//===================================================================//

_SIMPLIFY_FUNC(log,
)

//===================================================================//

_SIMPLIFY_FUNC(ln,

)

//===================================================================//

_SIMPLIFY_FUNC(sin,

)

//===================================================================//

_SIMPLIFY_FUNC(cos,

)

//===================================================================//

_SIMPLIFY_FUNC(tan,

)

//===================================================================//

_SIMPLIFY_FUNC(cot,

)

//===================================================================//

_SIMPLIFY_FUNC(arcsin,

)

//===================================================================//

_SIMPLIFY_FUNC(arccos,

)

//===================================================================//

_SIMPLIFY_FUNC(arctan,

)

//===================================================================//

_SIMPLIFY_FUNC(arccot,

)

//===================================================================//

_SIMPLIFY_FUNC(sinh,

)

//===================================================================//

_SIMPLIFY_FUNC(cosh,

)

//===================================================================//

_SIMPLIFY_FUNC(tanh,

)

//===================================================================//

_SIMPLIFY_FUNC(coth,

)

//===================================================================//

_SIMPLIFY_FUNC(arcsinh,

)

//===================================================================//

_SIMPLIFY_FUNC(arccosh,

)

//===================================================================//

_SIMPLIFY_FUNC(arctanh,

)

//===================================================================//

_SIMPLIFY_FUNC(arccoth,

)

//———————————————————————————————————————————————————————————————————//

#undef _SIMPLIFY_FUNC
#undef _PRINT
#undef CHECK_IF_SIMPLE

//———————————————————————————————————————————————————————————————————//
