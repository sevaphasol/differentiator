#include <math.h>

#include "operations.h"

//———————————————————————————————————————————————————————————————————//

num_t calc_add     (num_t n1, num_t n2) { return n1 + n2; }
num_t calc_sub     (num_t n1, num_t n2) { return n1 - n2; }
num_t calc_mul     (num_t n1, num_t n2) { return n1 * n2; }
num_t calc_div     (num_t n1, num_t n2) { return n1 / n2; }
num_t calc_sqrt    (num_t n1, num_t n2) { return sqrt(n1); }
num_t calc_pow     (num_t n1, num_t n2) { return pow(n1, n2); }
num_t calc_log     (num_t n1, num_t n2) { return log(n2) / log(n1); }
num_t calc_ln      (num_t n1, num_t n2) { return log(n1); }
num_t calc_sin     (num_t n1, num_t n2) { return sin(n1); }
num_t calc_cos     (num_t n1, num_t n2) { return cos(n1); }
num_t calc_tan     (num_t n1, num_t n2) { return tan(n1); }
num_t calc_cot     (num_t n1, num_t n2) { return 1 / tan(n1); }
num_t calc_arcsin  (num_t n1, num_t n2) { return asin(n1); }
num_t calc_arccos  (num_t n1, num_t n2) { return acos(n1); }
num_t calc_arctan  (num_t n1, num_t n2) { return atan(n1); }
num_t calc_arccot  (num_t n1, num_t n2) { return M_PI_2 - atan(n1); }
num_t calc_sinh    (num_t n1, num_t n2) { return sinh(n1); }
num_t calc_cosh    (num_t n1, num_t n2) { return cosh(n1); }
num_t calc_tanh    (num_t n1, num_t n2) { return tanh(n1); }
num_t calc_coth    (num_t n1, num_t n2) { return 1 / tanh(n1); }
num_t calc_arcsinh (num_t n1, num_t n2) { return asinh(n1); }
num_t calc_arccosh (num_t n1, num_t n2) { return acosh(n1); }
num_t calc_arctanh (num_t n1, num_t n2) { return atanh(n1); }
num_t calc_arccoth (num_t n1, num_t n2) { return 0.5 * (log(1 + 1 / n1) - log(1 - 1 / n1)); }

//———————————————————————————————————————————————————————————————————//
