#include "custom_assert.h"
#include "dsl.h"
#include "operations.h"
#include "tree_dump.h"

//———————————————————————————————————————————————————————————————————//

#define _METRIC_FUNC(func_name, code)                              \
int metric_##func_name(diff_context_t* ctx, node_t* node)      \
{                                                           \
    ASSERT(ctx);\
    ASSERT(node);                   \
                                                        \
    if (node->alias.renamed) {return 1;}\
                                                            \
    node_t *l, *r;                  \
    l = node->left;                                         \
    r = node->right;                                        \
                                    \
    int power = 0;                  \
                                    \
    code;                           \
                                    \
    if (power > CriticalMetricPower)  \
    {                   \
        node->alias.renamed = true;\
        node->alias.name    = ((ctx->n_renamed_nodes++ % 'A') + 'A');\
        node->alias.metrics = 1;\
    }\
    else\
    {\
        node->alias.renamed = false;\
        node->alias.name    = 'n';\
        node->alias.metrics = power;\
    }\
                                    \
    return power;                   \
}                                   \

//-------------------------------------------------------------------//

#define _RESULT power

//———————————————————————————————————————————————————————————————————//

_METRIC_FUNC(num,
    _RESULT = ((int) node->val.num) / 10 + 1;
)

//===================================================================//

_METRIC_FUNC(var,
    _RESULT = 1;
)

//===================================================================//

_METRIC_FUNC(add,
    _RESULT = _METRIC(l) + _METRIC(r) + 1;
)

//===================================================================//

_METRIC_FUNC(sub,
    _RESULT = _METRIC(l) + _METRIC(r) + 1;
)

//===================================================================//

_METRIC_FUNC(mul,
    _RESULT = _METRIC(l) + _METRIC(r) + 1;
)

//===================================================================//

_METRIC_FUNC(div,
    int ml = _METRIC(l);
    int mr = _METRIC(r);
    _RESULT = (ml > mr) ? ml : mr;
)

//===================================================================//

_METRIC_FUNC(sqrt,
    _RESULT = _METRIC(l) + 6;
)

//===================================================================//

_METRIC_FUNC(pow,
    _RESULT = _METRIC(l) + (int) (0.7 * _METRIC(r)) + 1;
)

//===================================================================//

_METRIC_FUNC(log,
    _RESULT = (int) (0.7 * _METRIC(l)) + _METRIC(r) + 5;
)

//===================================================================//

_METRIC_FUNC(ln,
    _RESULT = _METRIC(l) + 5;
)

//===================================================================//

_METRIC_FUNC(sin,
    _RESULT = _METRIC(l) + 5;
)

//===================================================================//

_METRIC_FUNC(cos,
    _RESULT = _METRIC(l) + 5;
)

//===================================================================//

_METRIC_FUNC(tan,
    _RESULT = _METRIC(l) + 5;
)

//===================================================================//

_METRIC_FUNC(cot,
    _RESULT = _METRIC(l) + 5;
)

//===================================================================//

_METRIC_FUNC(arcsin,
    _RESULT = _METRIC(l) + 8;
)

//===================================================================//

_METRIC_FUNC(arccos,
    _RESULT = _METRIC(l) + 8;
)

//===================================================================//

_METRIC_FUNC(arctan,
    _RESULT = _METRIC(l) + 8;
)

//===================================================================//

_METRIC_FUNC(arccot,
    _RESULT = _METRIC(l) + 8;
)

//===================================================================//

_METRIC_FUNC(sinh,
    _RESULT = _METRIC(l) + 6;
)

//===================================================================//

_METRIC_FUNC(cosh,
    _RESULT = _METRIC(l) + 6;
)

//===================================================================//

_METRIC_FUNC(tanh,
    _RESULT = _METRIC(l) + 6;
)

//===================================================================//

_METRIC_FUNC(coth,
    _RESULT = _METRIC(l) + 6;
)

//===================================================================//

_METRIC_FUNC(arcsinh,
    _RESULT = _METRIC(l) + 9;
)

//===================================================================//

_METRIC_FUNC(arccosh,
    _RESULT = _METRIC(l) + 9;
)

//===================================================================//

_METRIC_FUNC(arctanh,
    _RESULT = _METRIC(l) + 9;
)

//===================================================================//

_METRIC_FUNC(arccoth,
    _RESULT = _METRIC(l) + 9;
)

//———————————————————————————————————————————————————————————————————//

#undef _METRIC_FUNC
#undef _RESULT

//———————————————————————————————————————————————————————————————————//
