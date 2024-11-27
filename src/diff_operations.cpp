#include "custom_assert.h"
#include "dsl.h"
#include "operations.h"
#include "tree_dump.h"
#include "node_allocator.h"

//———————————————————————————————————————————————————————————————————//

#define _DIFF_FUNC(name, code)                              \
node_t* diff_##name(diff_context_t* ctx, node_t* node)      \
{                                                           \
    ASSERT(ctx);                                            \
    ASSERT(node);                                           \
                                                            \
    tree_dump(ctx);                                         \
                                                            \
    node_allocator_t* node_allocator = ctx->node_allocator; \
    node_t *l, *r, *dl, *dr;                                \
                                                            \
                                                            \
    l = node->left;                                         \
    if (l) {dl = _DIFF(l);}                                 \
                                                            \
    r = node->right;                                        \
    if (r) {dr = _DIFF(r);}                                 \
                                                            \
    code                                                    \
                                                            \
    fprintf(ctx->tex_file, "\n\\begin{equation}\n");        \
                                                            \
    fprintf(ctx->tex_file, "\\frac{d}{dx}(");               \
                                                            \
    _TEX(node);                                             \
                                                            \
    fprintf(ctx->tex_file, ") = ");                         \
                                                            \
    _TEX(diffed_node);                                      \
                                                            \
    fprintf(ctx->tex_file, "\n\\end{equation}\n");          \
                                                            \
    return diffed_node;                                     \
}                                                           \

//-------------------------------------------------------------------//

#define _RESULT node_t* diffed_node

//———————————————————————————————————————————————————————————————————//

_DIFF_FUNC(num,
    _RESULT = _NUM(0);
)

//===================================================================//

_DIFF_FUNC(var,
    _RESULT = _NUM(1);
)

//===================================================================//

_DIFF_FUNC(add,
    _RESULT = _ADD(dl, dr);
)

//===================================================================//

_DIFF_FUNC(sub,
    _RESULT = _SUB(dl, dr);
)

//===================================================================//

_DIFF_FUNC(mul,
    _RESULT = _ADD(_MUL(dl, r),
                   _MUL(dr, l));
)

//===================================================================//

_DIFF_FUNC(div,
    _RESULT = _DIV(_SUB(_MUL(dl,  dr),
                        _MUL(dr, l)),
                   _POW(dr, _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(sqrt,
    _RESULT = _DIV(dl,
                   _MUL(_NUM(2),
                        _SQRT(l)));
)

//===================================================================//

_DIFF_FUNC(pow,
    _RESULT = _MUL(_POW(l,
                        dr),
                   _DIFF(_MUL(_LN(l),
                              dr)));
)

//===================================================================//

_DIFF_FUNC(log,
    _RESULT = _DIFF(_DIV(_LN(r),
                         _LN(l)));
)

//===================================================================//

_DIFF_FUNC(ln,
    _RESULT = _DIV(dl,
                   l);
)

//===================================================================//

_DIFF_FUNC(sin,
    _RESULT = _MUL(_COS(l),
                   dl);
)

//===================================================================//

_DIFF_FUNC(cos,
    _RESULT = _MUL(_MUL(_NUM(-1),
                        _SIN(l)),
                   dl);
)

//===================================================================//

_DIFF_FUNC(tan,
    _RESULT = _DIV(dl,
                   _POW(_COS(l),
                        _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(cot,
    _RESULT = _DIV(dl,
                   _POW(_SIN(l),
                        _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(arcsin,
    _RESULT = _DIV(dl,
                   _SQRT(_SUB(_NUM(1),
                              _POW(l,
                                   _NUM(2)))));
)

//===================================================================//

_DIFF_FUNC(arccos,
    _RESULT = _DIV(_MUL(_NUM(-1),
                        dl),
                   _SQRT(_SUB(_NUM(1),
                              _POW(l,
                                    _NUM(2)))));
)

//===================================================================//

_DIFF_FUNC(arctan,
    _RESULT = _DIV(dl,
                   _ADD(_NUM(1),
                        _POW(l,
                             _NUM(2))));
)

//===================================================================//

_DIFF_FUNC(arccot,
    _RESULT = _DIV(_MUL(_NUM(-1),
                        dl),
                   _ADD(_NUM(1),
                        _POW(l,
                             _NUM(2))));
)

//===================================================================//

_DIFF_FUNC(sinh,
    _RESULT = _MUL(_COSH(l),
                   dl);
)

//===================================================================//

_DIFF_FUNC(cosh,
    _RESULT = _MUL(_SINH(l),
                   dl);
)

//===================================================================//

_DIFF_FUNC(tanh,
    _RESULT = _DIV(dl,
                   _POW(_COSH(l),
                        _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(coth,
    _RESULT = _DIV(_MUL(_NUM(-1),
                        dl),
                   _POW(_SINH(l),
                        _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(arcsinh,
    _RESULT = _DIV(dl,
                   _SQRT(_ADD(_NUM(1),
                              _POW(l,
                                   _NUM(2)))));
)

//===================================================================//

_DIFF_FUNC(arccosh,
    _RESULT = _DIV(dl,
                   _SQRT(_SUB(_POW(l,
                                   _NUM(2)),
                              _NUM(1))));
)

//===================================================================//

_DIFF_FUNC(arctanh,
    _RESULT = _DIV(dl,
                   _SUB(_NUM(1),
                        _POW(l,
                             _NUM(2))));
)

//===================================================================//

_DIFF_FUNC(arccoth,
    _RESULT = _DIV(dl,
                   _SUB(_NUM(1),
                        _POW(l,
                             _NUM(2))));
)

//———————————————————————————————————————————————————————————————————//

#undef DIFF_FUNC
#undef _RESULT

//———————————————————————————————————————————————————————————————————//
