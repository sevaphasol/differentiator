// #include "diff.h"
#include <stdlib.h>

//-------------------------------------------------------------------//

#include "diff.h"

//———————————————————————————————————————————————————————————————————//

const size_t nOperations = 24;

//———————————————————————————————————————————————————————————————————//

struct operation_t
{
    opr_t       code;
    const char* name;
    bool        binary;
    num_t       (*calc_func)(num_t, num_t);
    node_t*     (*diff_func)(diff_context_t* context, node_t* node);
    void        (*tex_func) (diff_context_t* context, node_t* node);
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

node_t* diff_num     (diff_context_t* ctx, node_t* node);
node_t* diff_var     (diff_context_t* ctx, node_t* node);
node_t* diff_add     (diff_context_t* ctx, node_t* node);
node_t* diff_sub     (diff_context_t* ctx, node_t* node);
node_t* diff_mul     (diff_context_t* ctx, node_t* node);
node_t* diff_div     (diff_context_t* ctx, node_t* node);
node_t* diff_sqrt    (diff_context_t* ctx, node_t* node);
node_t* diff_pow     (diff_context_t* ctx, node_t* node);
node_t* diff_log     (diff_context_t* ctx, node_t* node);
node_t* diff_ln      (diff_context_t* ctx, node_t* node);
node_t* diff_sin     (diff_context_t* ctx, node_t* node);
node_t* diff_cos     (diff_context_t* ctx, node_t* node);
node_t* diff_tan     (diff_context_t* ctx, node_t* node);
node_t* diff_cot     (diff_context_t* ctx, node_t* node);
node_t* diff_arcsin  (diff_context_t* ctx, node_t* node);
node_t* diff_arccos  (diff_context_t* ctx, node_t* node);
node_t* diff_arctan  (diff_context_t* ctx, node_t* node);
node_t* diff_arccot  (diff_context_t* ctx, node_t* node);
node_t* diff_sinh    (diff_context_t* ctx, node_t* node);
node_t* diff_cosh    (diff_context_t* ctx, node_t* node);
node_t* diff_tanh    (diff_context_t* ctx, node_t* node);
node_t* diff_coth    (diff_context_t* ctx, node_t* node);
node_t* diff_arcsinh (diff_context_t* ctx, node_t* node);
node_t* diff_arccosh (diff_context_t* ctx, node_t* node);
node_t* diff_arctanh (diff_context_t* ctx, node_t* node);
node_t* diff_arccoth (diff_context_t* ctx, node_t* node);

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

const operation_t OperationsTable[nOperations] =
    {
    //   .code      .name     .is_binary     .calc_func       .diff_func        .tex_func
        { ADD,       "+",         true,       &calc_add,       &diff_add,        &tex_add     },
        { SUB,       "-",         true,       &calc_sub,       &diff_sub,        &tex_sub     },
        { MUL,       "*",         true,       &calc_mul,       &diff_mul,        &tex_mul     },
        { DIV,       "/",         true,       &calc_div,       &diff_div,        &tex_div     },
        { SQRT,      "sqrt",      false,      &calc_sqrt,      &diff_sqrt,       &tex_sqrt    },
        { POW,       "^",         true,       &calc_pow,       &diff_pow,        &tex_pow     },
        { LOG,       "log",       true,       &calc_log,       &diff_log,        &tex_log     },
        { LN,        "ln",        false,      &calc_ln,        &diff_ln,         &tex_ln      },
        { SIN,       "sin",       false,      &calc_sin,       &diff_sin,        &tex_sin     },
        { COS,       "cos",       false,      &calc_cos,       &diff_cos,        &tex_cos     },
        { TAN,       "tan",       false,      &calc_tan,       &diff_tan,        &tex_tan     },
        { COT,       "cot",       false,      &calc_cot,       &diff_cot,        &tex_cot     },
        { ARCSIN,    "arcsin",    false,      &calc_arcsin,    &diff_arcsin,     &tex_arcsin  },
        { ARCCOS,    "arccos",    false,      &calc_arccos,    &diff_arccos,     &tex_arccos  },
        { ARCTAN,    "arctan",    false,      &calc_arctan,    &diff_arctan,     &tex_arctan  },
        { ARCCOT,    "arccot",    false,      &calc_arccot,    &diff_arccot,     &tex_arccot  },
        { SINH,      "sinh",      false,      &calc_sinh,      &diff_sinh,       &tex_sinh    },
        { COSH,      "cosh",      false,      &calc_cosh,      &diff_cosh,       &tex_cosh    },
        { TANH,      "tanh",      false,      &calc_tanh,      &diff_tanh,       &tex_tanh    },
        { COTH,      "coth",      false,      &calc_coth,      &diff_coth,       &tex_coth    },
        { ARCSINH,   "arcsinh",   false,      &calc_arcsinh,   &diff_arcsinh,    &tex_arcsinh },
        { ARCCOSH,   "arccosh",   false,      &calc_arccosh,   &diff_arccosh,    &tex_arccosh },
        { ARCTANH,   "arctanh",   false,      &calc_arctanh,   &diff_arctanh,    &tex_arctanh },
        { ARCCOTH,   "arccoth",   false,      &calc_arccoth,   &diff_arccoth,    &tex_arccoth },
    };

//———————————————————————————————————————————————————————————————————//
