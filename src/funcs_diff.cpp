#include "custom_assert.h"
#include "dsl.h"
#include "operations.h"
#include "tex_dump.h"
#include "node_allocator.h"
#include "graph_dump.h"

//———————————————————————————————————————————————————————————————————//

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
////////////////ADDITIONAL MACROS/////////////////
///////////////FOR DEFINING FUNCS/////////////////
////////////OF DIFFERENTIATION RULES//////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

//———————————————————————————————————————————————————————————————————//

#define _DIFF_FUNC_INTRO                                              \
                                                                      \
    ASSERT(ctx);                                                      \
    ASSERT(node);                                                     \
                                                                      \
    node_allocator_t* node_allocator = ctx->node_allocator;           \
    node_t *l, *r, *dl, *dr, *diffed_node;                            \
                                                                      \
                                                                      \
    (mode == QUIET) ? _QSIMPLIFY(node) : _SIMPLIFY(node);             \
                                                                      \
    l = node->left;                                                   \
    if (l) {(mode == QUIET) ? dl = _QDIFF(l) : dl = _DIFF(l);}        \
                                                                      \
    r = node->right;                                                  \
    if (r) {(mode == QUIET) ? dr = _QDIFF(r) : dr = _DIFF(r);}        \

//===================================================================//

#define _TEX_STEP                                                     \
                                                                      \
    _PRINT("%s", ctx->dump_info.phrases[random_phrase]);              \
                                                                      \
    _PRINT("\n\\begin{equation}\n");                                  \
    _PRINT("\\frac{d}{dx}(");                                         \
                                                                      \
    _METRIC(node);                                                    \
    _TEX(node);                                                       \
    _PRINT(") = ");                                                   \
                                                                      \
    graph_dump(ctx, diffed_node);\
    _METRIC(diffed_node);                                             \
    _TEX(diffed_node);                                                \
                                                                      \
    _PRINT("\n\\end{equation}\n");                                    \

//===================================================================//

#define _DIFF_FUNC_OUTRO                                              \
                                                                      \
    if (mode == QUIET)                                                \
        _QSIMPLIFY(diffed_node);                                      \
    else                                                              \
        _SIMPLIFY(diffed_node);                                       \
                                                                      \
    int random_phrase = (int) random() % ctx->dump_info.n_phrases;    \
                                                                      \
    if (mode != QUIET)                                                \
    {                                                                 \
        _TEX_STEP;                                                    \
    }                                                                 \
                                                                      \
    renames_encrypt(ctx, node);                                       \
    renames_encrypt(ctx, diffed_node);                                \
                                                                      \
    return diffed_node;                                               \

//===================================================================//

#define _DIFF_FUNC(func_name, executing_code)                         \
                                                                      \
node_t* diff_##func_name(diff_context_t* ctx,                         \
                         node_t* node,                                \
                         exec_mode_t mode)                            \
{                                                                     \
    _DIFF_FUNC_INTRO;                                                 \
    \
    executing_code;                                                   \
    _DIFF_FUNC_OUTRO;                                                 \
}                                                                     \

//===================================================================//

#define _PRINT(...) fprintf(ctx->dump_info.tex_file, ##__VA_ARGS__)

//-------------------------------------------------------------------//

#define _RESULT diffed_node

//———————————————————————————————————————————————————————————————————//

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
///////////////DEFINITION OF FUNCS////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

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
    _RESULT = _ADD(_MUL(dl, _COPY(r)),
                   _MUL(dr, _COPY(l)));
)

//===================================================================//

_DIFF_FUNC(div,
    _RESULT = _DIV(_SUB(_MUL(dl,  _COPY(r)),
                        _MUL(dr,  _COPY(l))),
                   _POW(_COPY(r), _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(sqrt,
    _RESULT = _DIV(dl,
                   _MUL(_NUM(2),
                        _SQRT(_COPY(l))));
)

//===================================================================//

_DIFF_FUNC(pow,
    int l_n_vars = 0;
    ASSERT(count_n_vars(ctx, node->left,  &l_n_vars) == DIFF_SUCCESS);

    int r_n_vars = 0;
    ASSERT(count_n_vars(ctx, node->right, &r_n_vars) == DIFF_SUCCESS);

    if (r->arg_type == NUM)
    {
        _RESULT = _MUL(_NUM(r->val.num),
                       _MUL(_DIFF(l),
                       _POW(_COPY(l),
                            _NUM(r->val.num - 1))));
    }
    else if (r_n_vars == 1 && l_n_vars == 0)
    {
        _RESULT = _MUL(_MUL(_COPY(node),
                            _DIFF(r)),
                       _LN(l));
    }
    else
    {
        _RESULT = _MUL(_COPY(node),
                       _DIFF(_MUL(_LN(_COPY(l)),
                                  _COPY(r))));
    }
)

//===================================================================//

_DIFF_FUNC(log,
    if (l->arg_type == NUM)
    {
        _RESULT = _DIV(dr,
                       _MUL(_LN(_COPY(l)),
                            _COPY(r)));
    }
    else
    {
        _RESULT = _DIFF(_DIV(_LN(_COPY(r)),
                             _LN(_COPY(l))));
    }
)

//===================================================================//

_DIFF_FUNC(ln,

    _RESULT = _DIV(dl,
                   _COPY(l));
)

//===================================================================//

_DIFF_FUNC(sin,

    _RESULT = _MUL(_COS(_COPY(l)),
                   dl);
)

//===================================================================//

_DIFF_FUNC(cos,

    _RESULT = _MUL(_MUL(_NUM(-1),
                        _SIN(_COPY(l))),
                   dl);
)

//===================================================================//

_DIFF_FUNC(tan,

    _RESULT = _DIV(dl,
                   _POW(_COS(_COPY(l)),
                        _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(cot,

    _RESULT = _DIV(dl,
                   _POW(_SIN(_COPY(l)),
                        _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(arcsin,

    _RESULT = _DIV(dl,
                   _SQRT(_SUB(_NUM(1),
                              _POW(_COPY(l),
                                   _NUM(2)))));
)

//===================================================================//

_DIFF_FUNC(arccos,

    _RESULT = _DIV(_MUL(_NUM(-1),
                        dl),
                   _SQRT(_SUB(_NUM(1),
                              _POW(_COPY(l),
                                    _NUM(2)))));
)

//===================================================================//

_DIFF_FUNC(arctan,

    _RESULT = _DIV(dl,
                   _ADD(_NUM(1),
                        _POW(_COPY(l),
                             _NUM(2))));
)

//===================================================================//

_DIFF_FUNC(arccot,

    _RESULT = _DIV(_MUL(_NUM(-1),
                        dl),
                   _ADD(_NUM(1),
                        _POW(_COPY(l),
                             _NUM(2))));
)

//===================================================================//

_DIFF_FUNC(sinh,

    _RESULT = _MUL(_COSH(_COPY(l)),
                   dl);
)

//===================================================================//

_DIFF_FUNC(cosh,

    _RESULT = _MUL(_SINH(_COPY(l)),
                   dl);
)

//===================================================================//

_DIFF_FUNC(tanh,

    _RESULT = _DIV(dl,
                   _POW(_COSH(_COPY(l)),
                        _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(coth,

    _RESULT = _DIV(_MUL(_NUM(-1),
                        dl),
                   _POW(_SINH(_COPY(l)),
                        _NUM(2)));
)

//===================================================================//

_DIFF_FUNC(arcsinh,

    _RESULT = _DIV(dl,
                   _SQRT(_ADD(_NUM(1),
                              _POW(_COPY(l),
                                   _NUM(2)))));
)

//===================================================================//

_DIFF_FUNC(arccosh,

    _RESULT = _DIV(dl,
                   _SQRT(_SUB(_POW(_COPY(l),
                                   _NUM(2)),
                              _NUM(1))));
)

//===================================================================//

_DIFF_FUNC(arctanh,

    _RESULT = _DIV(dl,
                   _SUB(_NUM(1),
                        _POW(_COPY(l),
                             _NUM(2))));
)

//===================================================================//

_DIFF_FUNC(arccoth,

    _RESULT = _DIV(dl,
                   _SUB(_NUM(1),
                        _POW(_COPY(l),
                             _NUM(2))));
)

//———————————————————————————————————————————————————————————————————//

#undef _DIFF_FUNC_INTRO
#undef _RESULT
#undef _PRINT
#undef _TEX_STEP
#undef _DIFF_FUNC_OUTRO
#undef _DIFF_FUNC

//———————————————————————————————————————————————————————————————————//
