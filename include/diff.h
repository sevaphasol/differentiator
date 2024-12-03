#ifndef DIFF_H__
#define DIFF_H__

//———————————————————————————————————————————————————————————————————//

#include <stdlib.h>
#include <stdio.h>

//———————————————————————————————————————————————————————————————————//

const int CriticalMetricPower = 25;

//———————————————————————————————————————————————————————————————————//

enum exec_mode_t
{
    QUIET = 0,
    LOUD  = 1,
};

//———————————————————————————————————————————————————————————————————//

enum diff_status_t
{
    DIFF_SUCCESS                    = 0,
    DIFF_NODE_ALLOCATOR_CTOR_ERROR  = 1,
    DIFF_FILE_OPEN_ERROR            = 2,
    DIFF_DOT_DUMP_ERROR             = 3,
    DIFF_READ_PHRASES_ERROR         = 4,
    DIFF_ALLOCATE_ERROR             = 5,
    DIFF_FILE_READ_ERROR            = 6,
    DIFF_GET_FILE_SIZE_ERROR        = 7,
    DIFF_PHRASES_STRINGS_CTOR_ERROR = 8,
    DIFF_TEX_DUMP_ERROR             = 9,
    DIFF_NOT_CONSTANT               = 10,
    DIFF_TRY_CALC_ERROR             = 11,
    DIFF_TEX_ERROR                  = 12,
    DIFF_CALC_IN_POINT_ERROR        = 13,
    DIFF_TOO_LONG_EXPRESSION_ERROR  = 14,
    DIFF_COUNT_N_VARS_ERROR         = 15,
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

//-------------------------------------------------------------------//

struct node_allocator_t;
struct node_t;

//-------------------------------------------------------------------//

struct dump_info_t
{
    FILE*             tex_file;
    const char*       tex_file_name;
    int               n_dumps; // for dot files
    char*             phrases_buf;
    char**            phrases;
    int               n_phrases;
    FILE*             plots_file;
    const char*       plots_file_name;
};

//-------------------------------------------------------------------//

struct diff_context_t
{
    node_allocator_t* node_allocator;
    node_t*           root;
    dump_info_t       dump_info;
    int               n_renamed_nodes;
};

//-------------------------------------------------------------------//

struct tex_alias_t
{
    bool renamed;
    int  name; // ascii code of upper eng letter, can overflow
    int  metrics;
};

//-------------------------------------------------------------------//

struct node_func_ptrs_t
{
    num_t      (*calc_func)     (num_t, num_t);
    node_t*    (*diff_func)     (diff_context_t* context, node_t* node, exec_mode_t mode);
    void       (*tex_func)      (diff_context_t* context, node_t* node);
    void       (*simplify_func) (diff_context_t* context, node_t* node, exec_mode_t mode);
    int        (*metric_func)   (diff_context_t* ctx, node_t* node);
    void       (*plot_func)     (diff_context_t* ctx, node_t* node);
};

//———————————————————————————————————————————————————————————————————//

struct node_t
{
    arg_type_t arg_type;
    val_t      val;

    node_func_ptrs_t func_ptrs;

    node_t*    left;
    node_t*    right;

    tex_alias_t alias;

    int depth;
    int replaced_symb;
    int n_replaced_symbs;
};

//———————————————————————————————————————————————————————————————————//

diff_status_t diff_context_ctor     (diff_context_t* ctx, node_allocator_t* node_allocator);
diff_status_t diff_context_dtor     (diff_context_t* ctx);
node_t*       copy_tree             (diff_context_t* ctx, node_t* root);
diff_status_t try_calc              (node_t* tree);
node_t*       diff_tree             (diff_context_t* ctx, node_t* root);
diff_status_t try_calc_opr_in_point (node_t* tree, num_t point);
diff_status_t derivative            (diff_context_t* ctx, node_t* root);
diff_status_t taylor                (diff_context_t* ctx, node_t* root, int n, num_t point);
num_t         calc_in_point         (node_t* tree, num_t point);
bool          is_equal              (num_t n1, num_t n2);
diff_status_t count_n_vars          (diff_context_t* ctx,
                                     node_t* node,
                                     int* res);

//———————————————————————————————————————————————————————————————————//

#endif // DIFF_H__
