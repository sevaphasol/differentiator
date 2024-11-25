#ifndef DSL_H__
#define DSL_H__

#define _DIFF(node)           node->diff_func(node_allocator, node)

#define _NUM(_num)            node_ctor(node_allocator, NUM, {.num = _num},    nullptr,       &diff_const,   nullptr, nullptr)
#define _VAR(_var)            node_ctor(node_allocator, VAR, {.var = _var},    nullptr,       &diff_var,     nullptr, nullptr)
#define _ADD(left, right)     node_ctor(node_allocator, OPR, {.opr = ADD},     &calc_add,     &diff_add,     left,    right)
#define _SUB(left, right)     node_ctor(node_allocator, OPR, {.opr = SUB},     &calc_sub,     &diff_sub,     left,    right)
#define _MUL(left, right)     node_ctor(node_allocator, OPR, {.opr = MUL},     &calc_mul,     &diff_mul,     left,    right)
#define _DIV(left, right)     node_ctor(node_allocator, OPR, {.opr = DIV},     &calc_div,     &diff_div,     left,    right)
#define _SQRT(node)           node_ctor(node_allocator, OPR, {.opr = SQRT},    &calc_sqrt,    &diff_sqrt,    node,    nullptr)
#define _POW(left, right)     node_ctor(node_allocator, OPR, {.opr = POW},     &calc_pow,     &diff_pow,     left,    right)
#define _LOG(left, right)     node_ctor(node_allocator, OPR, {.opr = LOG},     &calc_log,     &diff_log,     left,    right)
#define _LN(left, right)      node_ctor(node_allocator, OPR, {.opr = LN},      &calc_ln,      &diff_ln,      left,    nullptr)
#define _SIN(left, right)     node_ctor(node_allocator, OPR, {.opr = SIN},     &calc_sin,     &diff_sin,     left,    nullptr)
#define _COS(left, right)     node_ctor(node_allocator, OPR, {.opr = COS},     &calc_cos,     &diff_cos,     left,    nullptr)
#define _TAN(left, right)     node_ctor(node_allocator, OPR, {.opr = TAN},     &calc_tan,     &diff_tan,     left,    nullptr)
#define _COT(left, right)     node_ctor(node_allocator, OPR, {.opr = COT},     &calc_cot,     &diff_cot,     left,    nullptr)
#define _ARCSIN(left, right)  node_ctor(node_allocator, OPR, {.opr = ARCSIN},  &calc_arcsin,  &diff_arcsin,  left,    nullptr)
#define _ARCCOS(left, right)  node_ctor(node_allocator, OPR, {.opr = ARCCOS},  &calc_arccos,  &diff_arccos,  left,    nullptr)
#define _ARCTAN(left, right)  node_ctor(node_allocator, OPR, {.opr = ARCTAN},  &calc_arctan,  &diff_arctan,  left,    nullptr)
#define _ARCCOT(left, right)  node_ctor(node_allocator, OPR, {.opr = ARCCOT},  &calc_arccot,  &diff_arccot,  left,    nullptr)
#define _SINH(left, right)    node_ctor(node_allocator, OPR, {.opr = SINH},    &calc_sinh,    &diff_sinh,    left,    nullptr)
#define _COSH(left, right)    node_ctor(node_allocator, OPR, {.opr = COSH},    &calc_cosh,    &diff_cosh,    left,    nullptr)
#define _TANH(left, right)    node_ctor(node_allocator, OPR, {.opr = TANH},    &calc_tanh,    &diff_tanh,    left,    nullptr)
#define _COTH(left, right)    node_ctor(node_allocator, OPR, {.opr = COTH},    &calc_coth,    &diff_coth,    left,    nullptr)
#define _ARCSINH(left, right) node_ctor(node_allocator, OPR, {.opr = ARCSINH}, &calc_arcsinh, &diff_arcsinh, left,    nullptr)
#define _ARCCOSH(left, right) node_ctor(node_allocator, OPR, {.opr = ARCCOSH}, &calc_arccosh, &diff_arccosh, left,    nullptr)
#define _ARCTANH(left, right) node_ctor(node_allocator, OPR, {.opr = ARCTANH}, &calc_arctanh, &diff_arctanh, left,    nullptr)
#define _ARCCOTH(left, right) node_ctor(node_allocator, OPR, {.opr = ARCCOTH}, &calc_arccoth, &diff_arccoth, left,    nullptr)

#endif // DSL_H__
