#ifndef DIFF_H__
#define DIFF_H__

//———————————————————————————————————————————————————————————————————//

#include "node_allocator.h"

//———————————————————————————————————————————————————————————————————//

#define _NUM(val)         NodeCtor(node_allocator, NUM, val, nullptr, nullptr)
#define _VAR              NodeCtor(node_allocator, VAR, 1,   nullptr, nullptr)
#define _ADD(left, right) NodeCtor(node_allocator, OPR, ADD, left,    right)
#define _SUB(left, right) NodeCtor(node_allocator, OPR, SUB, left,    right)
#define _MUL(left, right) NodeCtor(node_allocator, OPR, MUL, left,    right)
#define _DIV(left, right) NodeCtor(node_allocator, OPR, DIV, left,    right)

//———————————————————————————————————————————————————————————————————//

enum DiffStatus
{
    DIFF_SUCCESS = 0,
    DIFF_BIG_ARRAY_REALLOC_ERROR,
    DIFF_ARRAYS_CALLOC_ERROR,
};

enum ArgType
{
    NUM = 0,
    VAR = 1,
    OPR = 2,
};

enum Operation : uint64_t
{
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3,
};

//———————————————————————————————————————————————————————————————————//

#endif // DIFF_H__
