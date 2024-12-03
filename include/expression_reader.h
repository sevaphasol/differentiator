#ifndef DIFF_IO_H__
#define DIFF_IO_H__

//———————————————————————————————————————————————————————————————————//

#include "node_allocator.h"

//———————————————————————————————————————————————————————————————————//

// 15*sin(5x^3) + cos^3(15x)

// const char* const Expression = "(/(*(arctan(x))(-(sinh(^(x)(2)))(sqrt(^(x)(2)))))(sinh(cosh(ln(x)))))";
// const char* const Expression = "(sin(x))";
// const char* const Expression = "(^(cos(*(15)(x)))(3))";
// const char* const Expression = "(/(1)(^(x)(1)))";
// const char* const Expression = "(arccoth(x))";
// const char* const Expression = "(^(^(x)(x))(x))";
// const char* const Expression = "(^(x)(5))";
// const char* const Expression = "(log(2)(^(2)(x)))";
// const char* const Expression = "(sin(arcsin(x)))";
// const char* const Expression = "(log(x)(x))";
// const char* const Expression = "(+(+(x)(x))(0))";
// const char* const Expression = "(+(*(2)(x))(*(3)(x)))";
// const char* const Expression = "(sqrt(-(^(x)(2))(1))))";
// const char* const Expression = "(^(*(sqrt(+(1)(x)))(ln(+(1)(x))))(sin(x)))";
// const char* const Expression = "(*(ln(+(1)(x))(sqrt(+(1)(sin(x)))))";
// const char* const Expression = "(sqrt(^(x)(2)))";
const char* const Expression = "(^(2)(-(x)(1))))";
// const char* const Expression = "(*(/(x)(sin(x)))(x))";

//———————————————————————————————————————————————————————————————————//

node_t* prefix_expression_reader (node_allocator_t* node_allocator, const char* expression);
node_t* infix_expression_reader  (node_allocator_t* node_allocator, const char* expression);

//———————————————————————————————————————————————————————————————————//

#endif // DIFF_IO_H__
