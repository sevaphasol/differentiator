#ifndef DSL_H__
#define DSL_H__

#include "node_allocator.h"

// #define _CALC(node)       node->calc_func(node->);
#define _DIFF(node)       node->diff_func(ctx, node)
#define _TEX(node)        node->tex_func(ctx, node)

#define _NUM(_num)        node_ctor(node_allocator, NUM, {.num = _num},    nullptr,       &diff_num,     &tex_num,     nullptr, nullptr)
#define _VAR(_var)        node_ctor(node_allocator, VAR, {.var = _var},    nullptr,       &diff_var,     &tex_var,     nullptr, nullptr)
#define _ADD(left, right) node_ctor(node_allocator, OPR, {.opr = ADD},     &calc_add,     &diff_add,     &tex_add,     left,    right)
#define _SUB(left, right) node_ctor(node_allocator, OPR, {.opr = SUB},     &calc_sub,     &diff_sub,     &tex_sub,     left,    right)
#define _MUL(left, right) node_ctor(node_allocator, OPR, {.opr = MUL},     &calc_mul,     &diff_mul,     &tex_mul,     left,    right)
#define _DIV(left, right) node_ctor(node_allocator, OPR, {.opr = DIV},     &calc_div,     &diff_div,     &tex_div,     left,    right)
#define _SQRT(node)       node_ctor(node_allocator, OPR, {.opr = SQRT},    &calc_sqrt,    &diff_sqrt,    &tex_sqrt,    node,    nullptr)
#define _POW(left, right) node_ctor(node_allocator, OPR, {.opr = POW},     &calc_pow,     &diff_pow,     &tex_pow,     left,    right)
#define _LOG(left, right) node_ctor(node_allocator, OPR, {.opr = LOG},     &calc_log,     &diff_log,     &tex_log,     left,    right)
#define _LN(node)         node_ctor(node_allocator, OPR, {.opr = LN},      &calc_ln,      &diff_ln,      &tex_ln,      node,    nullptr)
#define _SIN(node)        node_ctor(node_allocator, OPR, {.opr = SIN},     &calc_sin,     &diff_sin,     &tex_sin,     node,    nullptr)
#define _COS(node)        node_ctor(node_allocator, OPR, {.opr = COS},     &calc_cos,     &diff_cos,     &tex_cos,     node,    nullptr)
#define _TAN(node)        node_ctor(node_allocator, OPR, {.opr = TAN},     &calc_tan,     &diff_tan,     &tex_tan,     node,    nullptr)
#define _COT(node)        node_ctor(node_allocator, OPR, {.opr = COT},     &calc_cot,     &diff_cot,     &tex_cot,     node,    nullptr)
#define _ARCSIN(node)     node_ctor(node_allocator, OPR, {.opr = ARCSIN},  &calc_arcsin,  &diff_arcsin,  &tex_arcsin,  node,    nullptr)
#define _ARCCOS(node)     node_ctor(node_allocator, OPR, {.opr = ARCCOS},  &calc_arccos,  &diff_arccos,  &tex_arccos,  node,    nullptr)
#define _ARCTAN(node)     node_ctor(node_allocator, OPR, {.opr = ARCTAN},  &calc_arctan,  &diff_arctan,  &tex_arctan,  node,    nullptr)
#define _ARCCOT(node)     node_ctor(node_allocator, OPR, {.opr = ARCCOT},  &calc_arccot,  &diff_arccot,  &tex_arccot,  node,    nullptr)
#define _SINH(node)       node_ctor(node_allocator, OPR, {.opr = SINH},    &calc_sinh,    &diff_sinh,    &tex_sinh,    node,    nullptr)
#define _COSH(node)       node_ctor(node_allocator, OPR, {.opr = COSH},    &calc_cosh,    &diff_cosh,    &tex_cosh,    node,    nullptr)
#define _TANH(node)       node_ctor(node_allocator, OPR, {.opr = TANH},    &calc_tanh,    &diff_tanh,    &tex_tanh,    node,    nullptr)
#define _COTH(node)       node_ctor(node_allocator, OPR, {.opr = COTH},    &calc_coth,    &diff_coth,    &tex_coth,    node,    nullptr)
#define _ARCSINH(node)    node_ctor(node_allocator, OPR, {.opr = ARCSINH}, &calc_arcsinh, &diff_arcsinh, &tex_arcsinh, node,    nullptr)
#define _ARCCOSH(node)    node_ctor(node_allocator, OPR, {.opr = ARCCOSH}, &calc_arccosh, &diff_arccosh, &tex_arccosh, node,    nullptr)
#define _ARCTANH(node)    node_ctor(node_allocator, OPR, {.opr = ARCTANH}, &calc_arctanh, &diff_arctanh, &tex_arctanh, node,    nullptr)
#define _ARCCOTH(node)    node_ctor(node_allocator, OPR, {.opr = ARCCOTH}, &calc_arccoth, &diff_arccoth, &tex_arccoth, node,    nullptr)

#endif // DSL_H__
