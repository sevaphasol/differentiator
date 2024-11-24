#include "operations.h"
#include "math.h"
#include "dsl.h"
#include "custom_assert.h"

//———————————————————————————————————————————————————————————————————//

node_t* diff_const(node_allocator_t* node_allocator, node_t* node1, node_t* node2)
{
    return _NUM(0);
}

//===================================================================//

node_t* diff_var(node_allocator_t* node_allocator, node_t* node1, node_t* node2)
{
    return _NUM(1);
}

//===================================================================//

num_t calc_add(num_t n1, num_t n2)
{
    return n1 + n2;
}

//-------------------------------------------------------------------//

node_t* diff_add(node_allocator_t* node_allocator, node_t* node1, node_t* node2)
{
    return _ADD(node1->diff_func(node_allocator, node1->left, node1->right),
                node2->diff_func(node_allocator, node2->left, node2->right));
}

//===================================================================//

num_t calc_sub(num_t n1, num_t n2)
{
    return n1 - n2;
}

//-------------------------------------------------------------------//

node_t* diff_sub(node_allocator_t* node_allocator, node_t* node1, node_t* node2)
{
    return _SUB(node1->diff_func(node_allocator, node1->left, node1->right),
                node2->diff_func(node_allocator, node2->left, node2->right));
}

//===================================================================//

num_t calc_mul(num_t n1, num_t n2)
{
    return n1 * n2;
}

//-------------------------------------------------------------------//

node_t* diff_mul(node_allocator_t* node_allocator, node_t* node1, node_t* node2)
{
    return _ADD(_MUL(node1->diff_func(node_allocator, node1->left, node1->right), node2),
                _MUL(node2->diff_func(node_allocator, node2->left, node2->right), node1));
}

//===================================================================//

num_t calc_div(num_t n1, num_t n2)
{
    return n1 / n2;
}

//-------------------------------------------------------------------//

node_t* diff_div(node_allocator_t* node_allocator, node_t* node1, node_t* node2)
{
    return _DIV(_SUB(_MUL(node1->diff_func(node_allocator, node1->left, node1->right), node2),
                     _MUL(node2->diff_func(node_allocator, node2->left, node2->right), node1)),
                _MUL(node2, node2));
}

//===================================================================//

// num_t my_log(num_t n1, num_t n2)
// {
//     log(n2)/log(n2);
// }
//
// //===================================================================//
//
// num_t my_ln(num_t n)
// {
//     log(n1);
// }
//
// //===================================================================//
//
// num_t my_sin(num_t n)
// {
//     return (num_t) sin((float) n);
// }
//
// //===================================================================//
//
// num_t my_cos(num_t n)
// {
//     return (num_t) cos((float) n);
// }
//
// //===================================================================//
//
// num_t my_tan(num_t n1, num_t n2)
// {
//     return (num_t) tan((float) n);
// }
//
// //===================================================================//
//
// num_t my_cot(num_t n1, num_t n2)
// {
//     return (num_t) cot((float) n);
// }
//
// //===================================================================//
//
// num_t asn(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t acs(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t atg(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t act(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t shn(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t chn(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t thn(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t cth(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t ash(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t ach(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t ath(num_t n1, num_t n2)
// {
//
// }
//
// //===================================================================//
//
// num_t akh(num_t n1, num_t n2)
// {
//
// }
//
//
// //———————————————————————————————————————————————————————————————————//
