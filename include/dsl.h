#ifndef DSL_H__
#define DSL_H__

#include "node_allocator.h"

// #define _CALC(node)       node->calc_func(node->)
#define _DIFF(node)       node->diff_func(ctx, node)
#define _TEX(node)        node->tex_func(ctx, node)
#define _SIMPLIFY(node)   node->simplify_func(ctx, node)
#define _COPY(node)       copy_tree(ctx, node)

#define _NUM(_num)        node_ctor(node_allocator, NUM, {.num = _num},    nullptr,       &diff_num,     &tex_num,     &simplify_num,     nullptr, nullptr)
#define _VAR(_var)        node_ctor(node_allocator, VAR, {.var = _var},    nullptr,       &diff_var,     &tex_var,     &simplify_var,     nullptr, nullptr)
#define _ADD(left, right) node_ctor(node_allocator, OPR, {.opr = ADD},     &calc_add,     &diff_add,     &tex_add,     &simplify_add,     left,    right)
#define _SUB(left, right) node_ctor(node_allocator, OPR, {.opr = SUB},     &calc_sub,     &diff_sub,     &tex_sub,     &simplify_sub,     left,    right)
#define _MUL(left, right) node_ctor(node_allocator, OPR, {.opr = MUL},     &calc_mul,     &diff_mul,     &tex_mul,     &simplify_mul,     left,    right)
#define _DIV(left, right) node_ctor(node_allocator, OPR, {.opr = DIV},     &calc_div,     &diff_div,     &tex_div,     &simplify_div,     left,    right)
#define _SQRT(node)       node_ctor(node_allocator, OPR, {.opr = SQRT},    &calc_sqrt,    &diff_sqrt,    &tex_sqrt,    &simplify_sqrt,    node,    nullptr)
#define _POW(left, right) node_ctor(node_allocator, OPR, {.opr = POW},     &calc_pow,     &diff_pow,     &tex_pow,     &simplify_pow,     left,    right)
#define _LOG(left, right) node_ctor(node_allocator, OPR, {.opr = LOG},     &calc_log,     &diff_log,     &tex_log,     &simplify_log,     left,    right)
#define _LN(node)         node_ctor(node_allocator, OPR, {.opr = LN},      &calc_ln,      &diff_ln,      &tex_ln,      &simplify_ln,      node,    nullptr)
#define _SIN(node)        node_ctor(node_allocator, OPR, {.opr = SIN},     &calc_sin,     &diff_sin,     &tex_sin,     &simplify_sin,     node,    nullptr)
#define _COS(node)        node_ctor(node_allocator, OPR, {.opr = COS},     &calc_cos,     &diff_cos,     &tex_cos,     &simplify_cos,     node,    nullptr)
#define _TAN(node)        node_ctor(node_allocator, OPR, {.opr = TAN},     &calc_tan,     &diff_tan,     &tex_tan,     &simplify_tan,     node,    nullptr)
#define _COT(node)        node_ctor(node_allocator, OPR, {.opr = COT},     &calc_cot,     &diff_cot,     &tex_cot,     &simplify_cot,     node,    nullptr)
#define _ARCSIN(node)     node_ctor(node_allocator, OPR, {.opr = ARCSIN},  &calc_arcsin,  &diff_arcsin,  &tex_arcsin,  &simplify_arcsin,  node,    nullptr)
#define _ARCCOS(node)     node_ctor(node_allocator, OPR, {.opr = ARCCOS},  &calc_arccos,  &diff_arccos,  &tex_arccos,  &simplify_arccos,  node,    nullptr)
#define _ARCTAN(node)     node_ctor(node_allocator, OPR, {.opr = ARCTAN},  &calc_arctan,  &diff_arctan,  &tex_arctan,  &simplify_arctan,  node,    nullptr)
#define _ARCCOT(node)     node_ctor(node_allocator, OPR, {.opr = ARCCOT},  &calc_arccot,  &diff_arccot,  &tex_arccot,  &simplify_arccot,  node,    nullptr)
#define _SINH(node)       node_ctor(node_allocator, OPR, {.opr = SINH},    &calc_sinh,    &diff_sinh,    &tex_sinh,    &simplify_sinh,    node,    nullptr)
#define _COSH(node)       node_ctor(node_allocator, OPR, {.opr = COSH},    &calc_cosh,    &diff_cosh,    &tex_cosh,    &simplify_cosh,    node,    nullptr)
#define _TANH(node)       node_ctor(node_allocator, OPR, {.opr = TANH},    &calc_tanh,    &diff_tanh,    &tex_tanh,    &simplify_tanh,    node,    nullptr)
#define _COTH(node)       node_ctor(node_allocator, OPR, {.opr = COTH},    &calc_coth,    &diff_coth,    &tex_coth,    &simplify_coth,    node,    nullptr)
#define _ARCSINH(node)    node_ctor(node_allocator, OPR, {.opr = ARCSINH}, &calc_arcsinh, &diff_arcsinh, &tex_arcsinh, &simplify_arcsinh, node,    nullptr)
#define _ARCCOSH(node)    node_ctor(node_allocator, OPR, {.opr = ARCCOSH}, &calc_arccosh, &diff_arccosh, &tex_arccosh, &simplify_arccosh, node,    nullptr)
#define _ARCTANH(node)    node_ctor(node_allocator, OPR, {.opr = ARCTANH}, &calc_arctanh, &diff_arctanh, &tex_arctanh, &simplify_arctanh, node,    nullptr)
#define _ARCCOTH(node)    node_ctor(node_allocator, OPR, {.opr = ARCCOTH}, &calc_arccoth, &diff_arccoth, &tex_arccoth, &simplify_arccoth, node,    nullptr)

#endif // DSL_H__
