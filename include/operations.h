// #include "diff.h"
#include <stdlib.h>

#include "node_allocator.h"

//———————————————————————————————————————————————————————————————————//


//-------------------------------------------------------------------//

struct operation_t
{
    const char* name;
    opr_t       code;
    num_t       (*calc_func)(num_t, num_t);
    node_t*     (*diff_func)(node_allocator_t*, node_t*, node_t*);
};

//-------------------------------------------------------------------//

num_t   calc_add   (num_t n1, num_t n2);
num_t   calc_sub   (num_t n1, num_t n2);
num_t   calc_mul   (num_t n1, num_t n2);
num_t   calc_div   (num_t n1, num_t n2);
node_t* diff_add   (node_allocator_t* node_allocator, node_t* node1, node_t* node2);
node_t* diff_sub   (node_allocator_t* node_allocator, node_t* node1, node_t* node2);
node_t* diff_mul   (node_allocator_t* node_allocator, node_t* node1, node_t* node2);
node_t* diff_div   (node_allocator_t* node_allocator, node_t* node1, node_t* node2);
node_t* diff_const (node_allocator_t* node_allocator, node_t* node1, node_t* node2);
node_t* diff_var   (node_allocator_t* node_allocator, node_t* node1, node_t* node2);
// num_t pow(num_t n1, num_t n2);
// num_t log(num_t n1, num_t n2);
// num_t lna(num_t n1, num_t n2);
// num_t sin(num_t n1, num_t n2);
// num_t cos(num_t n1, num_t n2);
// num_t tan(num_t n1, num_t n2);
// num_t cot(num_t n1, num_t n2);
// num_t asn(num_t n1, num_t n2);
// num_t acs(num_t n1, num_t n2);
// num_t atg(num_t n1, num_t n2);
// num_t act(num_t n1, num_t n2);
// num_t shn(num_t n1, num_t n2);
// num_t chn(num_t n1, num_t n2);
// num_t thn(num_t n1, num_t n2);
// num_t cth(num_t n1, num_t n2);
// num_t ash(num_t n1, num_t n2);
// num_t ach(num_t n1, num_t n2);
// num_t ath(num_t n1, num_t n2);
// num_t akh(num_t n1, num_t n2);

//-------------------------------------------------------------------//

const operation_t OperationsTable[nOperations] =
    {
       {.name = "+",       .code = ADD,     .calc_func = &calc_add, .diff_func = &diff_add},
       {.name = "-",       .code = SUB,     .calc_func = &calc_sub, .diff_func = &diff_sub},
       {.name = "*",       .code = MUL,     .calc_func = &calc_mul, .diff_func = &diff_mul},
       {.name = "/",       .code = DIV,     .calc_func = &calc_div, .diff_func = &diff_div},
       {.name = "sqrt",    .code = SQRT,    .calc_func = &calc_sqrt, .diff_func = &diff_sqr},
       {.name = "^",       .code = POW,     .calc_func = &calc_pow, .diff_func = &diff_pow},
       {.name = "log",     .code = LOG,     .calc_func = &calc_log, .diff_func = &diff_log},
       {.name = "ln",      .code = LN,      .calc_func = &calc_ln, .diff_func = &diff_lna},
       {.name = "sin",     .code = SIN,     .calc_func = &calc_sin, .diff_func = &diff_sin},
       {.name = "cos",     .code = COS,     .calc_func = &calc_cos, .diff_func = &diff_cos},
       {.name = "tan",     .code = TAN,     .calc_func = &calc_tan, .diff_func = &diff_tan},
       {.name = "cot",     .code = COT,     .calc_func = &calc_cot, .diff_func = &diff_cot},
       {.name = "arcsin",  .code = ARCSIN,  .calc_func = &calc_arcsin, .diff_func = &diff_asn},
       {.name = "arccos",  .code = ARCCOS,  .calc_func = &calc_arccos, .diff_func = &diff_acs},
       {.name = "arctan",  .code = ARCTAN,  .calc_func = &calc_arctan, .diff_func = &diff_atg},
       {.name = "arccot",  .code = ARCCOT,  .calc_func = &calc_arccot, .diff_func = &diff_act},
       {.name = "sh",      .code = SINH,    .calc_func = &calc_shn, .diff_func = &diff_shn},
       {.name = "ch",      .code = COSH,    .calc_func = &calc_chn, .diff_func = &diff_chn},
       {.name = "tanh",    .code = TANH,    .calc_func = &calc_thn, .diff_func = &diff_thn},
       {.name = "coth",    .code = COTH,    .calc_func = &calc_cth, .diff_func = &diff_cth},
       {.name = "arcsinh", .code = ARCSINH, .calc_func = &calc_ash, .diff_func = &diff_ash},
       {.name = "arccosh", .code = ARCCOSH, .calc_func = &calc_ach, .diff_func = &diff_ach},
       {.name = "arctanh", .code = ARCTANH, .calc_func = &calc_ath, .diff_func = &diff_ath},
       {.name = "arccoth", .code = ARCCOTH, .calc_func = &calc_akh, .diff_func = &diff_akh},
    };

//———————————————————————————————————————————————————————————————————//
