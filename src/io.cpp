#include <string.h>

#include "io.h"
#include "custom_assert.h"
#include "operations.h"

//———————————————————————————————————————————————————————————————————//

static void read_prefix_token(const char** expression, char* buf);
static arg_type_t token_type(const char* str);
static node_t* get_tree(node_allocator_t* node_allocator, const char** expression, char* buf);
static opr_t get_opr_code(const char* name);
static bool is_num(const char* str);
static bool is_var(const char* str);
static bool is_opr(const char* str);
static var_t get_var_code(const char* name);

//———————————————————————————————————————————————————————————————————//

bool is_num(const char* str) {return ('0' <= str[0]) && (str[0] <= '9');}
bool is_var(const char* str) {return strstr("xy", str);}
bool is_opr(const char* str) {return strstr("+-*/", str);}

//===================================================================//

void read_prefix_token(const char** expression, char* buf)
{
    ASSERT(expression);
    ASSERT(buf);

    //-------------------------------------------------------------------//

    int n = 0;
    sscanf(*expression, "%*[()]%[^()]%n", buf, &n);
    *expression += n;
}

//===================================================================//

arg_type_t token_type(const char* token)
{
    ASSERT(token);

    if (is_num(token))
        return NUM;

    if (is_var(token))
        return VAR;

    if (is_opr(token))
        return OPR;

    ASSERT(0);
}

//===================================================================//

opr_t get_opr_code(const char* name)
{
    ASSERT(name);

    for (int i = 0; i < nOperations; i++)
    {
        if (strcmp(OperationsTable[i].name, name) == 0)
        {
            return OperationsTable[i].code;
        }
    }

    ASSERT(0);
}

//===================================================================//

var_t get_var_code(const char* name)
{
    ASSERT(name);

    for (int i = 0; i < nVars; i++)
    {
        if (VarsTable[i].name == name[0])
        {
            return VarsTable[i].code;
        }
    }

    ASSERT(0);
}

//===================================================================//

node_t* get_tree(node_allocator_t* node_allocator, const char** expression, char* buf)
{
    ASSERT(node_allocator);
    ASSERT(expression);
    ASSERT(*expression);
    ASSERT(buf);

    //--------------------------------------------------------------------//

    read_prefix_token(expression, buf);

    //-------------------------------------------------------------------//

    switch(token_type(buf))
    {
        case NUM:
        {
            return node_ctor(node_allocator,
                             NUM, {.num = strtod(buf, nullptr)},
                             nullptr,
                             &diff_const,
                             nullptr, nullptr);
        }
        case VAR:
        {
            return node_ctor(node_allocator,
                             VAR, {.var = get_var_code(buf)},
                             nullptr,
                             &diff_var,
                             nullptr, nullptr);
        }
        case OPR:
        {
            opr_t opr_code = get_opr_code(buf);

            node_t* left  = get_tree(node_allocator, expression, buf);
            node_t* right = get_tree(node_allocator, expression, buf);

            return node_ctor(node_allocator,
                             OPR, {.opr = opr_code},
                             OperationsTable[opr_code].calc_func,
                             OperationsTable[opr_code].diff_func,
                             left, right);
        }
    }

    //-------------------------------------------------------------------//

    ASSERT(0);
}

//===================================================================//

node_t* prefix_expression_reader(node_allocator_t* node_allocator, const char* expression)
{
    VERIFY(!expression,     return nullptr);
    VERIFY(!node_allocator, return nullptr);

    //-------------------------------------------------------------------//

    char buf[100] = {};

    //-------------------------------------------------------------------//

    return get_tree(node_allocator, &expression, buf);
}

//===================================================================//

node_t* infix_expression_reader(node_allocator_t* node_allocator, const char* expression)
{
    VERIFY(!expression, return nullptr);

    return nullptr;
}
