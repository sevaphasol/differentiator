#include "operations.h"
#include "dsl.h"
#include "custom_assert.h"

//———————————————————————————————————————————————————————————————————//

#define _TEX_FUNC(func_name, code)                                      \
void tex_##func_name(diff_context_t* ctx, node_t* node)                 \
{                                                                  \
    ASSERT(ctx);                                                   \
    ASSERT(node);                                                  \
                                                                   \
    node_t* l = node->left;                                        \
    node_t* r = node->right;                                       \
                                                                   \
    if (node->alias.renamed)                                       \
    {                                                              \
        _PUTC(node->alias.name);                                   \
                                                                   \
        return;                                                    \
    }                                                              \
                                                                   \
    code                                                           \
}                                                                  \

//-------------------------------------------------------------------//

#define _PRINT(...) fprintf(ctx->dump_info.tex_file, ##__VA_ARGS__)
#define _PUTC(symb) fputc(symb, ctx->dump_info.tex_file)

//-------------------------------------------------------------------//

#define _IN_BRACES(code) \
    _PUTC('{');          \
    code;                \
    _PUTC('}');          \

#define _IN_PARENT(code) \
    _PUTC('(');          \
    code;                \
    _PUTC(')');          \

//———————————————————————————————————————————————————————————————————//

_TEX_FUNC(num,
    _PRINT("%lg", node->val.num);
)

//===================================================================//

_TEX_FUNC(var,
    _PUTC(VarsTable[node->val.var].name);
)

//===================================================================//

_TEX_FUNC(add,
    _TEX(l);
    _PUTC('+');
    _TEX(r);
)

//===================================================================//

_TEX_FUNC(sub,
    _TEX(l);
    _PUTC('-');
    _TEX(r);
)

//===================================================================//

_TEX_FUNC(mul,
    _TEX(l);
    _PRINT(" \\cdot ");
    _TEX(r);
)

//===================================================================//

_TEX_FUNC(div,
    _PRINT("\\frac");
    _IN_BRACES(_TEX(l));
    _IN_BRACES(_TEX(r));
)

//===================================================================//

_TEX_FUNC(sqrt,
    _PRINT("\\sqrt");
    _IN_BRACES(_TEX(l));
)

//===================================================================//

_TEX_FUNC(pow,
    _IN_BRACES(_IN_PARENT(_TEX(l)));
    _PUTC('^');
    _IN_BRACES(_TEX(r));
)

//===================================================================//

_TEX_FUNC(log,
    _PRINT("\\log_");
    _TEX(l);
    _IN_PARENT(_TEX(r));
)

//===================================================================//

_TEX_FUNC(ln,
    _PRINT("\\ln");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(sin,
    _PRINT("\\sin");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(cos,
    _PRINT("\\cos");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(tan,
    _PRINT("\\tan");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(cot,
    _PRINT("\\cot");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(arcsin,
    _PRINT("\\arcsin");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(arccos,
    _PRINT("\\arccos");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(arctan,
    _PRINT("\\arctan");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(arccot,
    _PRINT("\\arccot");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(sinh,
    _PRINT("\\sinh");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(cosh,
    _PRINT("\\cosh");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(tanh,
    _PRINT("\\tanh");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(coth,
    _PRINT("\\coth");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(arcsinh,
    _PRINT("\\arcsinh");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(arccosh,
    _PRINT("\\arccosh");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(arctanh,
    _PRINT("\\arctanh");
    _IN_PARENT(_TEX(l));
)

//===================================================================//

_TEX_FUNC(arccoth,
    _PRINT("\\arccoth");
    _IN_PARENT(_TEX(l));
)

//———————————————————————————————————————————————————————————————————//

#undef _TEX_FUNC
#undef _PRINT
#undef _PUTC
#undef _IN_BRACES
#undef _IN_PARENT

//———————————————————————————————————————————————————————————————————//
