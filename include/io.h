#ifndef DIFF_IO_H__
#define DIFF_IO_H__

//———————————————————————————————————————————————————————————————————//

#include "node_allocator.h"

//———————————————————————————————————————————————————————————————————//

struct diff_io_context_t
{
    int   n_chars;
    char* buf[10];
    node_allocator_t* node_allocator;
};

//———————————————————————————————————————————————————————————————————//

node_t* prefix_expression_reader (node_allocator_t* node_allocator, const char* expression);
node_t* infix_expression_reader  (node_allocator_t* node_allocator, const char* expression);

//———————————————————————————————————————————————————————————————————//

#endif // DIFF_IO_H__
