#ifndef DIFF_H__
#define DIFF_H__

//———————————————————————————————————————————————————————————————————//

#include <stdlib.h>
#include <stdio.h>

//———————————————————————————————————————————————————————————————————//

enum diff_status_t
{
    DIFF_SUCCESS                   = 0,
    DIFF_NODE_ALLOCATOR_CTOR_ERROR = 1,
    DIFF_FILE_OPEN_ERROR           = 2,
    DIFF_DOT_DUMP_ERROR            = 3,
};

//———————————————————————————————————————————————————————————————————//

enum arg_type_t
{
    NUM              = 0,
    VAR              = 1,
    OPR              = 2,
    INVALID_ARG_TYPE = 3,
};

//———————————————————————————————————————————————————————————————————//

typedef double num_t;

//———————————————————————————————————————————————————————————————————//

const size_t nVars = 3;

//-------------------------------------------------------------------//

enum var_t
{
    X = 0,
    Y = 1,
    Z = 2,
};

//-------------------------------------------------------------------//

struct variable_t
{
    char  name;
    var_t code;
};

//-------------------------------------------------------------------//

const variable_t VarsTable[nVars] =
    {
    //    .name .code
        {  'x',   X   },
        {  'y',   Y   },
        {  'z',   Z   }
    };

//———————————————————————————————————————————————————————————————————//

enum opr_t
{
    ADD     = 0,    // adding
    SUB     = 1,    // subtraction
    MUL     = 2,    // multiplication
    DIV     = 3,    // divison
    SQRT    = 4,    // square root
    POW     = 5,    // powering
    LOG     = 6,    // logarithm
    LN      = 7,    // natural logarithm
    SIN     = 8,    // sinus
    COS     = 9,    // cosinus
    TAN     = 10,   // tangent
    COT     = 11,   // cotangent
    ARCSIN  = 12,   // arcsinus
    ARCCOS  = 13,   // arccosinus
    ARCTAN  = 14,   // argctangent
    ARCCOT  = 15,   // arccotangent
    SINH    = 16,   // hyperbolic sinus
    COSH    = 17,   // hyperbolic cosinus
    TANH    = 18,   // hyperbolic tagent
    COTH    = 19,   // hyperbolic cotangent
    ARCSINH = 20,   // hyperbolic arcsinus
    ARCCOSH = 21,   // hyperbolic arccosinus
    ARCTANH = 22,   // hyperbolic arctangent
    ARCCOTH = 23,   // hyperbolic arccotangent
};

//———————————————————————————————————————————————————————————————————//

union val_t
{
    num_t num;
    var_t var;
    opr_t opr;
};

//———————————————————————————————————————————————————————————————————//

struct node_allocator_t;
struct node_t;

//———————————————————————————————————————————————————————————————————//

struct diff_context_t
{
    node_allocator_t* node_allocator;
    node_t*           root;
    FILE*             tex_file;
    const char*       tex_file_name;
    int               n_dumps;
};

//———————————————————————————————————————————————————————————————————//

struct node_t
{
    arg_type_t arg_type;
    val_t      val;

    num_t      (*calc_func)(num_t, num_t);
    node_t*    (*diff_func)(diff_context_t* context, node_t* node);
    void       (*tex_func) (diff_context_t* context, node_t* node);

    node_t*    left;
    node_t*    right;
};

//———————————————————————————————————————————————————————————————————//

diff_status_t diff_context_ctor (diff_context_t* ctx, node_allocator_t* node_allocator);
diff_status_t diff_context_dtor (diff_context_t*ctx);
diff_status_t dump              (diff_context_t* ctx, node_t* tree);
diff_status_t optimize_tree     (node_t* tree);
node_t*       copy_tree         (node_t* root);
num_t         calc_tree         (node_t* root);
node_t*       diff_tree         (diff_context_t* ctx, node_t* root);

//———————————————————————————————————————————————————————————————————//

#endif // DIFF_H__
