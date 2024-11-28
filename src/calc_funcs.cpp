#include <math.h>

#include "operations.h"

//———————————————————————————————————————————————————————————————————//

num_t calc_add     (num_t n1, num_t n2) { return n1 + n2; }
num_t calc_sub     (num_t n1, num_t n2) { return n1 - n2; }
num_t calc_mul     (num_t n1, num_t n2) { return n1 * n2; }
num_t calc_div     (num_t n1, num_t n2) { return n1 / n2; }
num_t calc_sqrt    (num_t n1, num_t n2) { return sqrt(n1); }
num_t calc_pow     (num_t n1, num_t n2) { return pow(n1, n2); }
num_t calc_log     (num_t n1, num_t n2) { return log(n2) / log(n1); }
num_t calc_ln      (num_t n1, num_t n2) { return log(n1); }
num_t calc_sin     (num_t n1, num_t n2) { return sin(n1); }
num_t calc_cos     (num_t n1, num_t n2) { return cos(n1); }
num_t calc_tan     (num_t n1, num_t n2) { return tan(n1); }
num_t calc_cot     (num_t n1, num_t n2) { return 1 / tan(n1); }
num_t calc_arcsin  (num_t n1, num_t n2) { return asin(n1); }
num_t calc_arccos  (num_t n1, num_t n2) { return acos(n1); }
num_t calc_arctan  (num_t n1, num_t n2) { return atan(n1); }
num_t calc_arccot  (num_t n1, num_t n2) { return M_PI_2 - atan(n1); }
num_t calc_sinh    (num_t n1, num_t n2) { return sinh(n1); }
num_t calc_cosh    (num_t n1, num_t n2) { return cosh(n1); }
num_t calc_tanh    (num_t n1, num_t n2) { return tanh(n1); }
num_t calc_coth    (num_t n1, num_t n2) { return 1 / tanh(n1); }
num_t calc_arcsinh (num_t n1, num_t n2) { return asinh(n1); }
num_t calc_arccosh (num_t n1, num_t n2) { return acosh(n1); }
num_t calc_arctanh (num_t n1, num_t n2) { return atanh(n1); }
num_t calc_arccoth (num_t n1, num_t n2) { return 0.5 * (log(1 + 1 / n1) - log(1 - 1 / n1)); }

//———————————————————————————————————————————————————————————————————//

// #include "custom_assert.h"
// #include "dsl.h"
// #include "operations.h"
// #include "tree_dump.h"
// #include "node_allocator.h"
//
// //———————————————————————————————————————————————————————————————————//
//
// #define _CALC_FUNC(name, code)                              \
// node_t* diff_##name(diff_context_t* ctx, node_t* node)      \
// {                                                           \
//     ASSERT(ctx);                                            \
//     ASSERT(node);                                           \
//                                                             \
//     dot_dump(ctx);                                          \
//                                                             \
//     node_allocator_t* node_allocator = ctx->node_allocator; \
//     node_t *l, *r, *dl, *dr, *diffed_node;                  \
//                                                             \
//     l = node->left;                                         \
//     if (l) {_CALC(l);}                                      \
//                                                             \
//     r = node->right;                                        \
//     if (r) {_CALC(r);}                                      \
//                                                             \
//
//     code                                                    \
//                                                             \
//     int random_phrase = (int) random() % ctx->dump_info.n_phrases; \
//     _PRINT("%s", ctx->dump_info.phrases[random_phrase]);           \
//                                                             \
//     _PRINT("\n\\begin{equation}\n");                        \
//                                                             \
//     _PRINT("\\frac{d}{dx}(");                               \
//     _TEX(node);                                             \
//     _PRINT(") = ");                                         \
//                                                             \
//     _TEX(diffed_node);                                      \
//                                                             \
//     _PRINT("\n\\end{equation}\n");                          \
//                                                             \
//     _SIMPLIFY(diffed_node);                                 \
//                                                             \
//     return diffed_node;                                     \
// }
//
// //-------------------------------------------------------------------//
//
// #define _PRINT(...) fprintf(ctx->dump_info.tex_file, ##__VA_ARGS__)
// #define _RESULT diffed_node
// #define _DIFF_L             \
// if (l)                      \
// {                           \
//     if (l->arg_type != VAR) \
//     {                       \
//         dl = _DIFF(l);      \
//     }                       \
//     else                    \
//     {                       \
//         dl = _NUM(1);       \
//     }                       \
// }                           \
//
// #define _DIFF_R             \
// if (r)                      \
// {                           \
//     if (r->arg_type != VAR) \
//     {                       \
//         dr = _DIFF(r);      \
//     }                       \
//     else                    \
//     {                       \
//         dr = _NUM(1);       \
//     }                       \
// }                           \
//
// //———————————————————————————————————————————————————————————————————//
//
// _CALC_FUNC(num,
//     _RESULT = _NUM(0);
// )
//
// //===================================================================//
//
// _CALC_FUNC(var,
//     _RESULT = _NUM(1);
// )
//
// //===================================================================//
//
// _CALC_FUNC(add,
//     _DIFF_L
//     _DIFF_R
//     _RESULT = _ADD(dl, dr);
// )
//
// //===================================================================//
//
// _CALC_FUNC(sub,
//     _DIFF_L
//     _DIFF_R
//     _RESULT = _SUB(dl, dr);
// )
//
// //===================================================================//
//
// _CALC_FUNC(mul,
//     _DIFF_L
//     _DIFF_R
//     _RESULT = _ADD(_MUL(dl, r),
//                    _MUL(dr, l));
// )
//
// //===================================================================//
//
// _CALC_FUNC(div,
//     _DIFF_L
//     _DIFF_R
//     _RESULT = _DIV(_SUB(_MUL(dl,  dr),
//                         _MUL(dr, l)),
//                    _POW(dr, _NUM(2)));
// )
//
// //===================================================================//
//
// _CALC_FUNC(sqrt,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _MUL(_NUM(2),
//                         _SQRT(l)));
// )
//
// //===================================================================//
//
// _CALC_FUNC(pow,
//
//     if (r->arg_type == NUM)
//     {
//         _RESULT = _MUL(_NUM(r->val.num),
//                        _POW(l,
//                             _NUM(r->val.num - 1)));
//     }
//     else
//     {
//         _DIFF_R
//         _RESULT = _MUL(_POW(l,
//                             dr),
//                        _DIFF(_MUL(_LN(l),
//                                   dr)));
//     }
// )
//
// //===================================================================//
//
// _CALC_FUNC(log,
//     if (l->arg_type == NUM)
//     {
//         _DIFF_R
//         _RESULT = _DIV(dr,
//                        _MUL(_LN(l),
//                             r));
//     }
//     else
//     {
//         _RESULT = _DIFF(_DIV(_LN(r),
//                              _LN(l)));
//     }
// )
//
// //===================================================================//
//
// _CALC_FUNC(ln,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    l);
// )
//
// //===================================================================//
//
// _CALC_FUNC(sin,
//     _DIFF_L
//     _RESULT = _MUL(_COS(l),
//                    dl);
// )
//
// //===================================================================//
//
// _CALC_FUNC(cos,
//     _DIFF_L
//     _RESULT = _MUL(_MUL(_NUM(-1),
//                         _SIN(l)),
//                    dl);
// )
//
// //===================================================================//
//
// _CALC_FUNC(tan,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _POW(_COS(l),
//                         _NUM(2)));
// )
//
// //===================================================================//
//
// _CALC_FUNC(cot,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _POW(_SIN(l),
//                         _NUM(2)));
// )
//
// //===================================================================//
//
// _CALC_FUNC(arcsin,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _SQRT(_SUB(_NUM(1),
//                               _POW(l,
//                                    _NUM(2)))));
// )
//
// //===================================================================//
//
// _CALC_FUNC(arccos,
//     _DIFF_L
//     _RESULT = _DIV(_MUL(_NUM(-1),
//                         dl),
//                    _SQRT(_SUB(_NUM(1),
//                               _POW(l,
//                                     _NUM(2)))));
// )
//
// //===================================================================//
//
// _CALC_FUNC(arctan,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _ADD(_NUM(1),
//                         _POW(l,
//                              _NUM(2))));
// )
//
// //===================================================================//
//
// _CALC_FUNC(arccot,
//     _DIFF_L
//     _RESULT = _DIV(_MUL(_NUM(-1),
//                         dl),
//                    _ADD(_NUM(1),
//                         _POW(l,
//                              _NUM(2))));
// )
//
// //===================================================================//
//
// _CALC_FUNC(sinh,
//     _DIFF_L
//     _RESULT = _MUL(_COSH(l),
//                    dl);
// )
//
// //===================================================================//
//
// _CALC_FUNC(cosh,
//     _DIFF_L
//     _RESULT = _MUL(_SINH(l),
//                    dl);
// )
//
// //===================================================================//
//
// _CALC_FUNC(tanh,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _POW(_COSH(l),
//                         _NUM(2)));
// )
//
// //===================================================================//
//
// _CALC_FUNC(coth,
//     _DIFF_L
//     _RESULT = _DIV(_MUL(_NUM(-1),
//                         dl),
//                    _POW(_SINH(l),
//                         _NUM(2)));
// )
//
// //===================================================================//
//
// _CALC_FUNC(arcsinh,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _SQRT(_ADD(_NUM(1),
//                               _POW(l,
//                                    _NUM(2)))));
// )
//
// //===================================================================//
//
// _CALC_FUNC(arccosh,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _SQRT(_SUB(_POW(l,
//                                    _NUM(2)),
//                               _NUM(1))));
// )
//
// //===================================================================//
//
// _CALC_FUNC(arctanh,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _SUB(_NUM(1),
//                         _POW(l,
//                              _NUM(2))));
// )
//
// //===================================================================//
//
// _CALC_FUNC(arccoth,
//     _DIFF_L
//     _RESULT = _DIV(dl,
//                    _SUB(_NUM(1),
//                         _POW(l,
//                              _NUM(2))));
// )
//
// //———————————————————————————————————————————————————————————————————//
//
// #undef DIFF_FUNC
// #undef _RESULT
// #undef _PRINT
//
// //———————————————————————————————————————————————————————————————————//
