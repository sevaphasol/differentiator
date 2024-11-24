#ifndef DIFF_H__
#define DIFF_H__

//———————————————————————————————————————————————————————————————————//

#include <stdlib.h>

//———————————————————————————————————————————————————————————————————//

//———————————————————————————————————————————————————————————————————//

enum diff_status_t
{
    DIFF_SUCCESS = 0,
    DIFF_BIG_ARRAY_REALLOC_ERROR,
    DIFF_ARRAYS_CALLOC_ERROR,
};

//———————————————————————————————————————————————————————————————————//

enum arg_type_t
{
    NUM = 0,
    VAR = 1,
    OPR = 2,
};

//———————————————————————————————————————————————————————————————————//

typedef double num_t;

//———————————————————————————————————————————————————————————————————//

const size_t nOperations = 24;

//-------------------------------------------------------------------//

enum opr_t
{
    ADD = 0,    // adding
    SUB = 1,    // subtraction
    MUL = 2,    // multiplication
    DIV = 3,    // divison
    SQR = 4,    // square root
    POW = 5,    // powering
    LOG = 6,    // logarithm
    LNA = 7,    // natural logarithm
    SIN = 8,    // sinus
    COS = 9,    // cosinus
    TAN = 10,   // tangent
    COT = 11,   // cotangent
    ASN = 12,   // arcsinus
    ACS = 13,   // arccosinus
    ATG = 14,   // argctangent
    ACT = 15,   // arccotangent
    SHN = 16,   // hyperbolic sinus
    CHN = 17,   // hyperbolic cosinus
    THN = 18,   // hyperbolic tagent
    CTH = 19,   // hyperbolic cotangent
    ASH = 20,   // hyperbolic arcsinus
    ACH = 21,   // hyperbolic arccosinus
    ATH = 22,   // hyperbolic arctangent
    AKH = 23,   // hyperbolic arccotangent
};

//———————————————————————————————————————————————————————————————————//

const size_t nVars = 3;

enum var_t
{
    X = 0,
    Y = 1,
    Z = 2,
};

struct variable_t
{
    char  name;
    var_t code;
};

const variable_t VarsTable[nVars] = {{.name = 'x', .code = X},
                                     {.name = 'y', .code = Y},
                                     {.name = 'z', .code = Z}};

//———————————————————————————————————————————————————————————————————//

union val_t
{
    num_t num;
    var_t var;
    opr_t opr;
};

//———————————————————————————————————————————————————————————————————//

struct node_allocator_t;

struct node_t
{
    arg_type_t arg_type;
    val_t      val;

    num_t      (*calc_func)(num_t, num_t);
    node_t*    (*diff_func)(node_allocator_t*, node_t*, node_t*);

    node_t*    left;
    node_t*    right;
};

struct node_allocator_t
{
    size_t   n_arrays;
    size_t   array_len;
    node_t** big_array;

    int      free_place;
};

//———————————————————————————————————————————————————————————————————//

num_t   calc_tree(node_t* root);
node_t* diff_tree(node_allocator_t* node_allocator, node_t* root);

//———————————————————————————————————————————————————————————————————//

#endif // DIFF_H__