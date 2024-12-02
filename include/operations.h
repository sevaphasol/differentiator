// #include "diff.h"
#include <stdlib.h>

//-------------------------------------------------------------------//

#include "diff.h"

//———————————————————————————————————————————————————————————————————//

const size_t nOperations = 24;

//———————————————————————————————————————————————————————————————————//

struct operation_t
{
    opr_t            code;
    const char*      name;
    bool             binary;
    node_func_ptrs_t func_ptrs;
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

void simplify_num     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_var     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_add     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_sub     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_mul     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_div     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_sqrt    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_pow     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_log     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_ln      (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_sin     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_cos     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_tan     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_cot     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_arcsin  (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_arccos  (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_arctan  (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_arccot  (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_sinh    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_cosh    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_tanh    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_coth    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_arcsinh (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_arccosh (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_arctanh (diff_context_t* ctx, node_t* node, exec_mode_t mode);
void simplify_arccoth (diff_context_t* ctx, node_t* node, exec_mode_t mode);

//-------------------------------------------------------------------//

node_t* diff_num     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_var     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_add     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_sub     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_mul     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_div     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_sqrt    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_pow     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_log     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_ln      (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_sin     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_cos     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_tan     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_cot     (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_arcsin  (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_arccos  (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_arctan  (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_arccot  (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_sinh    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_cosh    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_tanh    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_coth    (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_arcsinh (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_arccosh (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_arctanh (diff_context_t* ctx, node_t* node, exec_mode_t mode);
node_t* diff_arccoth (diff_context_t* ctx, node_t* node, exec_mode_t mode);

//-------------------------------------------------------------------//

void tex_num         (diff_context_t* ctx, node_t* node);
void tex_var         (diff_context_t* ctx, node_t* node);
void tex_add         (diff_context_t* ctx, node_t* node);
void tex_sub         (diff_context_t* ctx, node_t* node);
void tex_mul         (diff_context_t* ctx, node_t* node);
void tex_div         (diff_context_t* ctx, node_t* node);
void tex_sqrt        (diff_context_t* ctx, node_t* node);
void tex_pow         (diff_context_t* ctx, node_t* node);
void tex_log         (diff_context_t* ctx, node_t* node);
void tex_ln          (diff_context_t* ctx, node_t* node);
void tex_sin         (diff_context_t* ctx, node_t* node);
void tex_cos         (diff_context_t* ctx, node_t* node);
void tex_tan         (diff_context_t* ctx, node_t* node);
void tex_cot         (diff_context_t* ctx, node_t* node);
void tex_arcsin      (diff_context_t* ctx, node_t* node);
void tex_arccos      (diff_context_t* ctx, node_t* node);
void tex_arctan      (diff_context_t* ctx, node_t* node);
void tex_arccot      (diff_context_t* ctx, node_t* node);
void tex_sinh        (diff_context_t* ctx, node_t* node);
void tex_cosh        (diff_context_t* ctx, node_t* node);
void tex_tanh        (diff_context_t* ctx, node_t* node);
void tex_coth        (diff_context_t* ctx, node_t* node);
void tex_arcsinh     (diff_context_t* ctx, node_t* node);
void tex_arccosh     (diff_context_t* ctx, node_t* node);
void tex_arctanh     (diff_context_t* ctx, node_t* node);
void tex_arccoth     (diff_context_t* ctx, node_t* node);

//-------------------------------------------------------------------//

int metric_num     (diff_context_t* ctx, node_t* node);
int metric_var     (diff_context_t* ctx, node_t* node);
int metric_add     (diff_context_t* ctx, node_t* node);
int metric_sub     (diff_context_t* ctx, node_t* node);
int metric_mul     (diff_context_t* ctx, node_t* node);
int metric_div     (diff_context_t* ctx, node_t* node);
int metric_sqrt    (diff_context_t* ctx, node_t* node);
int metric_pow     (diff_context_t* ctx, node_t* node);
int metric_log     (diff_context_t* ctx, node_t* node);
int metric_ln      (diff_context_t* ctx, node_t* node);
int metric_sin     (diff_context_t* ctx, node_t* node);
int metric_cos     (diff_context_t* ctx, node_t* node);
int metric_tan     (diff_context_t* ctx, node_t* node);
int metric_cot     (diff_context_t* ctx, node_t* node);
int metric_arcsin  (diff_context_t* ctx, node_t* node);
int metric_arccos  (diff_context_t* ctx, node_t* node);
int metric_arctan  (diff_context_t* ctx, node_t* node);
int metric_arccot  (diff_context_t* ctx, node_t* node);
int metric_sinh    (diff_context_t* ctx, node_t* node);
int metric_cosh    (diff_context_t* ctx, node_t* node);
int metric_tanh    (diff_context_t* ctx, node_t* node);
int metric_coth    (diff_context_t* ctx, node_t* node);
int metric_arcsinh (diff_context_t* ctx, node_t* node);
int metric_arccosh (diff_context_t* ctx, node_t* node);
int metric_arctanh (diff_context_t* ctx, node_t* node);
int metric_arccoth (diff_context_t* ctx, node_t* node);

//-------------------------------------------------------------------//

const operation_t OperationsTable[nOperations] =
    {
    //   .code      .name     .is_binary     .calc_func       .diff_func        .tex_func       .simplify_func     .metric_func
        { ADD,       "+",         true,     { &calc_add,       &diff_add,        &tex_add,      &simplify_add,     &metric_add     }},
        { SUB,       "-",         true,     { &calc_sub,       &diff_sub,        &tex_sub,      &simplify_sub,     &metric_sub     }},
        { MUL,       "*",         true,     { &calc_mul,       &diff_mul,        &tex_mul,      &simplify_mul,     &metric_mul     }},
        { DIV,       "/",         true,     { &calc_div,       &diff_div,        &tex_div,      &simplify_div,     &metric_div     }},
        { SQRT,      "sqrt",      false,    { &calc_sqrt,      &diff_sqrt,       &tex_sqrt,     &simplify_sqrt,    &metric_sqrt    }},
        { POW,       "^",         true,     { &calc_pow,       &diff_pow,        &tex_pow,      &simplify_pow,     &metric_pow     }},
        { LOG,       "log",       true,     { &calc_log,       &diff_log,        &tex_log,      &simplify_log,     &metric_log     }},
        { LN,        "ln",        false,    { &calc_ln,        &diff_ln,         &tex_ln,       &simplify_ln,      &metric_ln      }},
        { SIN,       "sin",       false,    { &calc_sin,       &diff_sin,        &tex_sin,      &simplify_sin,     &metric_sin     }},
        { COS,       "cos",       false,    { &calc_cos,       &diff_cos,        &tex_cos,      &simplify_cos,     &metric_cos     }},
        { TAN,       "tan",       false,    { &calc_tan,       &diff_tan,        &tex_tan,      &simplify_tan,     &metric_tan     }},
        { COT,       "cot",       false,    { &calc_cot,       &diff_cot,        &tex_cot,      &simplify_cot,     &metric_cot     }},
        { ARCSIN,    "arcsin",    false,    { &calc_arcsin,    &diff_arcsin,     &tex_arcsin,   &simplify_arcsin,  &metric_arcsin  }},
        { ARCCOS,    "arccos",    false,    { &calc_arccos,    &diff_arccos,     &tex_arccos,   &simplify_arccos,  &metric_arccos  }},
        { ARCTAN,    "arctan",    false,    { &calc_arctan,    &diff_arctan,     &tex_arctan,   &simplify_arctan,  &metric_arctan  }},
        { ARCCOT,    "arccot",    false,    { &calc_arccot,    &diff_arccot,     &tex_arccot,   &simplify_arccot,  &metric_arccot  }},
        { SINH,      "sinh",      false,    { &calc_sinh,      &diff_sinh,       &tex_sinh,     &simplify_sinh,    &metric_sinh    }},
        { COSH,      "cosh",      false,    { &calc_cosh,      &diff_cosh,       &tex_cosh,     &simplify_cosh,    &metric_cosh    }},
        { TANH,      "tanh",      false,    { &calc_tanh,      &diff_tanh,       &tex_tanh,     &simplify_tanh,    &metric_tanh    }},
        { COTH,      "coth",      false,    { &calc_coth,      &diff_coth,       &tex_coth,     &simplify_coth,    &metric_coth    }},
        { ARCSINH,   "arcsinh",   false,    { &calc_arcsinh,   &diff_arcsinh,    &tex_arcsinh,  &simplify_arcsinh, &metric_arcsinh }},
        { ARCCOSH,   "arccosh",   false,    { &calc_arccosh,   &diff_arccosh,    &tex_arccosh,  &simplify_arccosh, &metric_arccosh }},
        { ARCTANH,   "arctanh",   false,    { &calc_arctanh,   &diff_arctanh,    &tex_arctanh,  &simplify_arctanh, &metric_arctanh }},
        { ARCCOTH,   "arccoth",   false,    { &calc_arccoth,   &diff_arccoth,    &tex_arccoth,  &simplify_arccoth, &metric_arccoth }},
    };

//———————————————————————————————————————————————————————————————————//
