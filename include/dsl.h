////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////DSL/////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

#define _NUM(num_)         node_ctor(node_allocator, NUM, {.num = num_}, nullptr,   &diff_const, nullptr, nullptr)
#define _VAR(var_)         node_ctor(node_allocator, VAR, {.var = var_}, nullptr,   &diff_var,   nullptr, nullptr)
#define _ADD(left, right)  node_ctor(node_allocator, OPR, {.opr = ADD},  &calc_add, &diff_add,   left,    right)
#define _SUB(left, right)  node_ctor(node_allocator, OPR, {.opr = SUB},  &calc_sub, &diff_sub,   left,    right)
#define _MUL(left, right)  node_ctor(node_allocator, OPR, {.opr = MUL},  &calc_mul, &diff_mul,   left,    right)
#define _DIV(left, right)  node_ctor(node_allocator, OPR, {.opr = DIV},  &calc_div, &diff_div,   left,    right)
