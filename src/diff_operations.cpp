#include "operations.h"
#include "math.h"
#include "dsl.h"
#include "custom_assert.h"

//———————————————————————————————————————————————————————————————————//

node_t* diff_const(node_allocator_t* node_allocator, node_t* node)
{
    return _NUM(0);
}

//===================================================================//

node_t* diff_var(node_allocator_t* node_allocator, node_t* node)
{
    return _NUM(1);
}

//===================================================================//

node_t* diff_add(node_allocator_t* node_allocator, node_t* node)
{
    ASSERT(node_allocator);
    ASSERT(node);

    //-------------------------------------------------------------------//

    node_t* left  = node->left;
    node_t* right = node->right;

    //-------------------------------------------------------------------//

    return _ADD(_DIFF(left), _DIFF(right));
}

//===================================================================//

node_t* diff_sub(node_allocator_t* node_allocator, node_t* node)
{
    ASSERT(node_allocator);
    ASSERT(node);

    //-------------------------------------------------------------------//

    node_t* left  = node->left;
    node_t* right = node->right;

    //-------------------------------------------------------------------//

    return _SUB(_DIFF(left), _DIFF(right));
}

//===================================================================//

node_t* diff_mul(node_allocator_t* node_allocator, node_t* node)
{
    ASSERT(node_allocator);
    ASSERT(node);

    //-------------------------------------------------------------------//

    node_t* left  = node->left;
    node_t* right = node->right;

    //-------------------------------------------------------------------//

    return _ADD(_MUL(_DIFF(left),  node->right),
                _MUL(_DIFF(right), node->left));
}

//===================================================================//

node_t* diff_div(node_allocator_t* node_allocator, node_t* node)
{
    ASSERT(node_allocator);
    ASSERT(node);

    //-------------------------------------------------------------------//

    node_t* left  = node->left;
    node_t* right = node->right;

    //-------------------------------------------------------------------//

    return _DIV(_SUB(_MUL(_DIFF(left),  right),
                     _MUL(_DIFF(right), left)),
                _POW(right, 2));
}

//===================================================================//

node_t* diff_sqrt(node_allocator_t* node_allocator, node_t* node)
{
    return _MUL(_DIV(_NUM(1), _MUL(_NUM(2), node1)),
                node1->diff_func(node_allocator, node1->left, node2->right));
}

//===================================================================//

node_t* diff_pow(node_allocator_t* node_allocator, node_t* node)
{
    if (node2->arg_type == NUM)
    {
        return _MUL(_MUL(node2, _POW(node1, _NUM(node2->val.num - 1))),
                    node1->diff_func(node_allocator, node1->left, node2->left));
    }
    else
    {
        node_t* left  = _POW(node1, node2);
        node_t* right = _MUL(_LN(node1), node2);

        return _MUL(left, right->diff_func(right->left, right->right));
    }
}

//===================================================================//

node_t* diff_log(node_allocator_t* node_allocator, node_t* node)
{
    node_t* node = _DIV(_LN(node1), _LN(node2));

    return node->diff_func(node1, node2);
}

//===================================================================//

node_t* diff_ln(node_allocator_t* node_allocator, node_t* node)
{
    node_t* left  = _DIV(_NUM(1), node1);
    node_t* right = node1->diff_func();

    return _DIV(_NUM(1), node1)
}

//===================================================================//

node_t* diff_sin(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_cos(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_tan(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_cot(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_arcsin(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_arccos(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_arctan(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_arccot(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_sinh(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_cosh(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_tanh(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_coth(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_arcsinh(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_arccosh(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_arctanh(node_allocator_t* node_allocator, node_t* node)
{

}

//===================================================================//

node_t* diff_arccoth(node_allocator_t* node_allocator, node_t* node)
{

}

//———————————————————————————————————————————————————————————————————//
