// #include "diff.h"
#include <stdlib.h>

#include "node_allocator.h"

//———————————————————————————————————————————————————————————————————//

struct operation_t
{
    const char* name;
    opr_t       code;
    num_t       (*calc_func)(num_t, num_t);
    node_t*     (*diff_func)(node_allocator_t*, node_t*);
};

//-------------------------------------------------------------------//

num_t   calc_add     (num_t n1, num_t n2);
num_t   calc_sub     (num_t n1, num_t n2);
num_t   calc_mul     (num_t n1, num_t n2);
num_t   calc_div     (num_t n1, num_t n2);
num_t   calc_sqrt    (num_t n1, num_t n2);
num_t   calc_pow     (num_t n1, num_t n2);
num_t   calc_log     (num_t n1, num_t n2);
num_t   calc_ln      (num_t n1, num_t n2);
num_t   calc_sin     (num_t n1, num_t n2);
num_t   calc_cos     (num_t n1, num_t n2);
num_t   calc_tan     (num_t n1, num_t n2);
num_t   calc_cot     (num_t n1, num_t n2);
num_t   calc_arcsin  (num_t n1, num_t n2);
num_t   calc_arccos  (num_t n1, num_t n2);
num_t   calc_arctan  (num_t n1, num_t n2);
num_t   calc_arccot  (num_t n1, num_t n2);
num_t   calc_sinh    (num_t n1, num_t n2);
num_t   calc_cosh    (num_t n1, num_t n2);
num_t   calc_tanh    (num_t n1, num_t n2);
num_t   calc_coth    (num_t n1, num_t n2);
num_t   calc_arcsinh (num_t n1, num_t n2);
num_t   calc_arccosh (num_t n1, num_t n2);
num_t   calc_arctanh (num_t n1, num_t n2);
num_t   calc_arccoth (num_t n1, num_t n2);

//-------------------------------------------------------------------//

node_t* diff_const   (node_allocator_t* node_allocator, node_t* node);
node_t* diff_var     (node_allocator_t* node_allocator, node_t* node);

node_t* diff_add     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_sub     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_mul     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_div     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_sqrt    (node_allocator_t* node_allocator, node_t* node);
node_t* diff_pow     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_log     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_ln      (node_allocator_t* node_allocator, node_t* node);
node_t* diff_sin     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_cos     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_tan     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_cot     (node_allocator_t* node_allocator, node_t* node);
node_t* diff_arcsin  (node_allocator_t* node_allocator, node_t* node);
node_t* diff_arccos  (node_allocator_t* node_allocator, node_t* node);
node_t* diff_arctan  (node_allocator_t* node_allocator, node_t* node);
node_t* diff_arccot  (node_allocator_t* node_allocator, node_t* node);
node_t* diff_sinh    (node_allocator_t* node_allocator, node_t* node);
node_t* diff_cosh    (node_allocator_t* node_allocator, node_t* node);
node_t* diff_tanh    (node_allocator_t* node_allocator, node_t* node);
node_t* diff_coth    (node_allocator_t* node_allocator, node_t* node);
node_t* diff_arcsinh (node_allocator_t* node_allocator, node_t* node);
node_t* diff_arccosh (node_allocator_t* node_allocator, node_t* node);
node_t* diff_arctanh (node_allocator_t* node_allocator, node_t* node);
node_t* diff_arccoth (node_allocator_t* node_allocator, node_t* node);

//-------------------------------------------------------------------//

const operation_t OperationsTable[nOperations] =
    {
       {.name = "+",       .code = ADD,     .calc_func = &calc_add,     .diff_func = &diff_add},
       {.name = "-",       .code = SUB,     .calc_func = &calc_sub,     .diff_func = &diff_sub},
       {.name = "*",       .code = MUL,     .calc_func = &calc_mul,     .diff_func = &diff_mul},
       {.name = "/",       .code = DIV,     .calc_func = &calc_div,     .diff_func = &diff_div},
       {.name = "sqrt",    .code = SQRT,    .calc_func = &calc_sqrt,    .diff_func = &diff_sqrt},
       {.name = "^",       .code = POW,     .calc_func = &calc_pow,     .diff_func = &diff_pow},
       {.name = "log",     .code = LOG,     .calc_func = &calc_log,     .diff_func = &diff_log},
       {.name = "ln",      .code = LN,      .calc_func = &calc_ln,      .diff_func = &diff_ln},
       {.name = "sin",     .code = SIN,     .calc_func = &calc_sin,     .diff_func = &diff_sin},
       {.name = "cos",     .code = COS,     .calc_func = &calc_cos,     .diff_func = &diff_cos},
       {.name = "tan",     .code = TAN,     .calc_func = &calc_tan,     .diff_func = &diff_tan},
       {.name = "cot",     .code = COT,     .calc_func = &calc_cot,     .diff_func = &diff_cot},
       {.name = "arcsin",  .code = ARCSIN,  .calc_func = &calc_arcsin,  .diff_func = &diff_arcsin},
       {.name = "arccos",  .code = ARCCOS,  .calc_func = &calc_arccos,  .diff_func = &diff_arccos},
       {.name = "arctan",  .code = ARCTAN,  .calc_func = &calc_arctan,  .diff_func = &diff_arctan},
       {.name = "arccot",  .code = ARCCOT,  .calc_func = &calc_arccot,  .diff_func = &diff_arccot},
       {.name = "sh",      .code = SINH,    .calc_func = &calc_sinh,    .diff_func = &diff_sinh},
       {.name = "ch",      .code = COSH,    .calc_func = &calc_cosh,    .diff_func = &diff_cosh},
       {.name = "tanh",    .code = TANH,    .calc_func = &calc_tanh,    .diff_func = &diff_tanh},
       {.name = "coth",    .code = COTH,    .calc_func = &calc_coth,    .diff_func = &diff_coth},
       {.name = "arcsinh", .code = ARCSINH, .calc_func = &calc_arcsinh, .diff_func = &diff_arcsinh},
       {.name = "arccosh", .code = ARCCOSH, .calc_func = &calc_arccosh, .diff_func = &diff_arccosh},
       {.name = "arctanh", .code = ARCTANH, .calc_func = &calc_arctanh, .diff_func = &diff_arctanh},
       {.name = "arccoth", .code = ARCCOTH, .calc_func = &calc_arccoth, .diff_func = &diff_arccoth},
    };

//———————————————————————————————————————————————————————————————————//
