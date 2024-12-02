#include "custom_assert.h"
#include "dsl.h"
#include "operations.h"
#include "tree_dump.h"
#include "node_allocator.h"

//———————————————————————————————————————————————————————————————————//

#define _SIMPLIFY_FUNC(func_name, code)                                           \
node_t* simplify_##func_name(diff_context_t* ctx, node_t* node, exec_mode_t mode) \
{                                                                            \
    ASSERT(ctx);                                                             \
    ASSERT(node);                                                            \
                                                                             \
    node_allocator_t* node_allocator = ctx->node_allocator;                  \
    node_t* l = node->left;                                                  \
    node_t* r = node->right;                                                 \
    node_t* simplified_node = nullptr;                                       \
                                                                             \
    if (l) {(mode == QUIET) ? _QSIMPLIFY(l) : _SIMPLIFY(l);}                 \
    if (r) {(mode == QUIET) ? _QSIMPLIFY(r) : _SIMPLIFY(r);}                 \
                                                                             \
    bool simplified = false;                                                 \
                                                                             \
    _TRY_CALC(node)                                                          \
                                                                             \
    code                                                                     \
                                                                             \
    _TRY_CALC(node)                                                          \
                                                                             \
    if (simplified)                                                          \
    {                                                                        \
        *node = *simplified_node;                                            \
    }                                                                        \
                                                                             \
    return nullptr;                                                          \
}                                                                            \

//-------------------------------------------------------------------//

#define _PRINT(...) fprintf(ctx->dump_info.tex_file, ##__VA_ARGS__)

#define _IF_LEFT(_val, new_node) \
if (l->arg_type == NUM &&        \
    l->val.num  == _val)         \
{                                \
    simplified_node = new_node;  \
    simplified = true;           \
}                                \

#define _IF_RIGHT(_val, new_node) \
if (r->arg_type == NUM &&        \
    r->val.num  == _val)         \
{                                \
    simplified_node = new_node;  \
    simplified = true;           \
}                                \

#define _POWER2

#define _TRY_CALC(node)                                 \
if (l && l->arg_type == NUM &&                          \
    r && r->arg_type == NUM)                            \
{                                                       \
    if (mode == QUIET)                                  \
    {                                                   \
        try_calc(node);                                 \
    }                                                   \
    else                                                \
    {                                                   \
        _PRINT("Упростим\n");                           \
                                                        \
        _PRINT("\n\\begin{equation}\n");                \
                                                        \
        _TEX(node);                                     \
        _PRINT(" = ");                                  \
                                                        \
        try_calc(node);                                 \
        _TEX(node);                                     \
        _PRINT("\n\\end{equation}\n");                  \
    }                                                   \
}                                                       \

//———————————————————————————————————————————————————————————————————//

_SIMPLIFY_FUNC(num,

)

//===================================================================//

_SIMPLIFY_FUNC(var,

)

//===================================================================//

_SIMPLIFY_FUNC(add,
    _IF_LEFT (0, r)
    _IF_RIGHT(0, l)
)

//===================================================================//

_SIMPLIFY_FUNC(sub,
    _IF_LEFT(0, _MUL(_NUM(-1), r))
    _IF_RIGHT(0, l)
)

//===================================================================//

_SIMPLIFY_FUNC(mul,
    _IF_LEFT (0, _NUM(0))
    _IF_RIGHT(0, _NUM(0))

    _IF_LEFT (1, r)
    _IF_RIGHT(1, l)
)

//===================================================================//

_SIMPLIFY_FUNC(div,
    _IF_LEFT (0, _NUM(0))
    _IF_RIGHT(1, l)
)

//===================================================================//

_SIMPLIFY_FUNC(sqrt,
)

//===================================================================//

_SIMPLIFY_FUNC(pow,
    _IF_LEFT (1, l)
    _IF_RIGHT(1, l)
    _IF_RIGHT(0, _NUM(1))
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
