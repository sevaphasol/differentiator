#include <string.h>

//-------------------------------------------------------------------//

#include "custom_assert.h"
#include "expression_reader.h"
#include "operations.h"

//———————————————————————————————————————————————————————————————————//

static void       read_prefix_token (const char** expression, char* buf);
static arg_type_t token_type        (const char* str);
static node_t*    get_tree          (node_allocator_t* node_allocator, const char** expression, char* buf);
static opr_t      get_opr_code      (const char* name);
static bool       try_get_num       (const char* str, val_t* val);
static bool       try_get_var       (const char* str, val_t* val);
static bool       try_get_opr       (const char* str, val_t* val);
static var_t      get_var_code      (const char* name);

//———————————————————————————————————————————————————————————————————//

bool try_get_num(const char* str, val_t* val)
{
    ASSERT(str);
    ASSERT(val);

    //-------------------------------------------------------------------//

    if (('0' <= str[0]) && (str[0] <= '9'))
    {
        val->num = strtod(str, nullptr);

        return true;
    }

    return false;
}

//===================================================================//

bool try_get_var(const char* str, val_t* val)
{
    ASSERT(str);
    ASSERT(val);

    //-------------------------------------------------------------------//

    for (int i = 0; i < nVars; i++)
    {
        if (str[0] == VarsTable[i].name)
        {
            val->var = VarsTable[i].code;

            return true;
        }
    }

    return false;
}

//===================================================================//

bool try_get_opr(const char* str, val_t* val)
{
    ASSERT(str);
    ASSERT(val);

    //-------------------------------------------------------------------//

    for (int i = 0; i < nOperations; i++)
    {
        if (strcmp(str, OperationsTable[i].name) == 0)
        {
            val->opr = OperationsTable[i].code;

            return true;
        }
    }

    return false;
}

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

arg_type_t token_type(const char* token, val_t* val)
{
    ASSERT(token);

    if (try_get_opr(token, val))
    {
        return OPR;
    }

    if (try_get_var(token, val))
    {
        return VAR;
    }

    if (try_get_num(token, val))
    {
        return NUM;
    }

    return INVALID_ARG_TYPE;
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

    val_t val;

    switch(token_type(buf, &val))
    {
        case NUM:
        {
            return node_ctor(node_allocator,
                             NUM, {.num = val.num},
                             nullptr,
                             &diff_num,
                             &tex_num,
                             nullptr, nullptr);
        }
        case VAR:
        {
            return node_ctor(node_allocator,
                             VAR, {.var = val.var},
                             nullptr,
                             &diff_var,
                             &tex_var,
                             nullptr, nullptr);
        }
        case OPR:
        {
            node_t* left  = get_tree(node_allocator, expression, buf);
            node_t* right = nullptr;

            if (OperationsTable[val.opr].binary)
            {
                right = get_tree(node_allocator, expression, buf);
            }

            return node_ctor(node_allocator,
                             OPR, {.opr = val.opr},
                             OperationsTable[val.opr].calc_func,
                             OperationsTable[val.opr].diff_func,
                             OperationsTable[val.opr].tex_func,
                             left, right);
        }
        default:
        {
            fprintf(stderr, "%s:INVALID EXPRESSION SYNTAX\n", buf);
            return nullptr;
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

//———————————————————————————————————————————————————————————————————//
