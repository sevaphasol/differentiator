#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

//-------------------------------------------------------------------//

#include "node_allocator.h"
#include "diff.h"
#include "operations.h"
#include "custom_assert.h"
#include "dsl.h"
#include "graph_dump.h"
#include "tex_dump.h"
#include "plot_dump.h"

//———————————————————————————————————————————————————————————————————//

static diff_status_t get_derivaties_in_point(diff_context_t* ctx,
                                             node_t* expression,
                                             const int n,
                                             num_t* coeffs,
                                             num_t point);

static diff_status_t get_taylor_formula     (diff_context_t* ctx,
                                             const int n,
                                             num_t* coeffs,
                                             num_t point);

static diff_status_t count_node             (node_t* node,
                                             num_t l,
                                             num_t r);

static diff_status_t try_calc_opr           (node_t* tree);

//———————————————————————————————————————————————————————————————————//

diff_status_t derivative(diff_context_t* ctx, node_t* root)
{
    ASSERT(ctx);
    ASSERT(root);

    //-------------------------------------------------------------------//

    VERIFY(write_derivative_tex_intro(ctx, root) != DIFF_SUCCESS,
           return DIFF_TEX_ERROR);

    //-------------------------------------------------------------------//

    node_t* diffed = diff_tree(ctx, root);

    graph_dump(ctx, diffed);

    //-------------------------------------------------------------------//

    VERIFY(write_derivative_tex_outro(ctx, diffed) != DIFF_SUCCESS,
           return DIFF_TEX_ERROR);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t diff_context_ctor(diff_context_t*   ctx,
                                node_allocator_t* node_allocator)
{
    ASSERT(ctx);
    ASSERT(node_allocator);

    //-------------------------------------------------------------------//

    VERIFY(node_allocator_ctor(node_allocator, nAllocatedNodes),
           return DIFF_NODE_ALLOCATOR_CTOR_ERROR);

    ctx->node_allocator = node_allocator;

    //-------------------------------------------------------------------//

    ctx->dump_info.tex_file = fopen(TexFile, "w");

    VERIFY(!ctx->dump_info.tex_file,
           return DIFF_FILE_OPEN_ERROR);

    ctx->dump_info.tex_file_name = TexFile;

    fprintf(ctx->dump_info.tex_file, "%s", TexIntro);

    //-------------------------------------------------------------------//

    ctx->dump_info.n_dumps = 0; // needed for dot files naming

    //-------------------------------------------------------------------//

    FILE* phrases_file = fopen(PhrasesFile, "rb");
    VERIFY(!phrases_file,
           return DIFF_FILE_OPEN_ERROR);

    VERIFY(read_phrases(&ctx->dump_info, phrases_file) != DIFF_SUCCESS,
           return DIFF_READ_PHRASES_ERROR);

    srand((unsigned int) time(NULL));

    //-------------------------------------------------------------------//

    ctx->dump_info.plots_file = fopen(PlotFile, "w");

    VERIFY(!ctx->dump_info.plots_file,
           return DIFF_FILE_OPEN_ERROR);

    ctx->dump_info.plots_file_name = PlotFile;

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t diff_context_dtor(diff_context_t* ctx)
{
    ASSERT(ctx);
    ASSERT(ctx->node_allocator);
    ASSERT(ctx->dump_info.tex_file);
    ASSERT(ctx->dump_info.tex_file_name);

    //-------------------------------------------------------------------//

    node_allocator_dtor(ctx->node_allocator);

    //-------------------------------------------------------------------//

    fprintf(ctx->dump_info.tex_file, "%s", TexOutro);
    fclose(ctx->dump_info.tex_file);

    char command[SysCommandBufSize] = {};
    snprintf(command, SysCommandBufSize, "pdflatex -quiet %s; mv diff.aux "
                                         "diff.log diff.tex tex_logs/",
                                         ctx->dump_info.tex_file_name);

    system(command);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t calc_in_point(node_t* tree, num_t point)
{
    ASSERT(tree);

    //-------------------------------------------------------------------//

    switch (tree->arg_type)
    {
        case NUM:
        {
            return DIFF_SUCCESS;
        }
        case VAR:
        {
            tree->arg_type = NUM;
            tree->val.num  = point;

            return DIFF_SUCCESS;
        }
        case OPR:
        {
            return(try_calc_opr_in_point(tree, point));
        }

        default: ASSERT(0);
    }

    return DIFF_TRY_CALC_ERROR;
}

//===================================================================//

diff_status_t try_calc_opr_in_point(node_t* tree, num_t point)
{
    ASSERT(tree);
    ASSERT(tree->left);

    //-------------------------------------------------------------------//

    if (calc_in_point(tree->left, point) != DIFF_SUCCESS)
    {
        return DIFF_NOT_CONSTANT;
    }

    tree->arg_type                 = NUM;
    tree->func_ptrs.diff_func      = &diff_num;
    tree->func_ptrs.tex_func       = &tex_num;
    tree->func_ptrs.simplify_func  = &simplify_num;
    tree->func_ptrs.metric_func    = &metric_num;

    if (OperationsTable[tree->val.opr].binary)
    {
        ASSERT(tree->right);

        if (calc_in_point(tree->right, point) != DIFF_SUCCESS)
        {
                return DIFF_NOT_CONSTANT;
        }

        tree->val.num  = tree->func_ptrs.calc_func(tree->left->val.num,
                                         tree->right->val.num);
        tree->left  = nullptr;
        tree->right = nullptr;

        return DIFF_SUCCESS;
    }
    else
    {
        tree->val.num  = tree->func_ptrs.calc_func(tree->left->val.num, 0);

        tree->left  = nullptr;
        tree->right = nullptr;

        return DIFF_SUCCESS;
    }

    //-------------------------------------------------------------------//

    return DIFF_TRY_CALC_ERROR;
}

//===================================================================//

node_t* diff_tree(diff_context_t* ctx, node_t* root)
{
    ASSERT(ctx);
    ASSERT(root);

    //-------------------------------------------------------------------//

    graph_dump(ctx, root);
    return _DIFF(root);
}

//===================================================================//

node_t* copy_tree(diff_context_t* ctx, node_t* root)
{
    ASSERT(ctx);

    //-------------------------------------------------------------------//

    if (!root) {return nullptr;}

    node_allocator_t* node_allocator = ctx->node_allocator;
    node_t* node = node_ctor(node_allocator,
                             root->arg_type,
                             root->val,
                             { root->func_ptrs.calc_func,
                               root->func_ptrs.diff_func,
                               root->func_ptrs.tex_func,
                               root->func_ptrs.simplify_func,
                               root->func_ptrs.metric_func,
                               root->func_ptrs.plot_func },
                             root->left,
                             root->right);

    *node = *root;

    node->left  = copy_tree(ctx, root->left);
    node->right = copy_tree(ctx, root->right);

    //-------------------------------------------------------------------//

    return node;
}

//===================================================================//

diff_status_t try_calc(node_t* tree)
{
    ASSERT(tree);

    //-------------------------------------------------------------------//

    switch (tree->arg_type)
    {
        case NUM:
        {
            return DIFF_SUCCESS;
        }
        case VAR: return DIFF_NOT_CONSTANT;
        case OPR:
        {
            return try_calc_opr(tree);
        }

        default: ASSERT(0);
    }

    //-------------------------------------------------------------------//

    return DIFF_TRY_CALC_ERROR;
}

//===================================================================//

diff_status_t try_calc_opr(node_t* tree)
{
    ASSERT(tree);

    //-------------------------------------------------------------------//

    if (OperationsTable[tree->val.opr].binary)
    {
        ASSERT(tree->left);
        ASSERT(tree->right);

        //-------------------------------------------------------------------//

        try_calc(tree->left);
        try_calc(tree->right);

        //-------------------------------------------------------------------//

        if (tree->left->arg_type  == NUM &&
            tree->right->arg_type == NUM)
        {
            count_node(tree,
                        tree->left->val.num,
                        tree->right->val.num);

            return DIFF_SUCCESS;
        }

        return DIFF_NOT_CONSTANT;
    }
    else
    {
        ASSERT(tree->left);

        //-------------------------------------------------------------------//

        try_calc(tree->left);

        //-------------------------------------------------------------------//

        if (tree->left->arg_type == NUM)
        {
            count_node(tree,
                        tree->left->val.num,
                        0);

            return DIFF_SUCCESS;
        }

        return DIFF_NOT_CONSTANT;
    }

    //-------------------------------------------------------------------//

    return DIFF_TRY_CALC_ERROR;
}

//===================================================================//

diff_status_t count_node(node_t* node, num_t l, num_t r)
{
    ASSERT(node);

    //-------------------------------------------------------------------//

    node->val.num = node->func_ptrs.calc_func(l, r);

    //-------------------------------------------------------------------//

    node->arg_type                 = NUM;
    node->func_ptrs.calc_func      = nullptr;
    node->func_ptrs.diff_func      = &diff_num;
    node->func_ptrs.tex_func       = &tex_num;
    node->func_ptrs.simplify_func  = &simplify_num;
    node->func_ptrs.metric_func    = &metric_num;
    node->left                     = nullptr;
    node->right                    = nullptr;

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t count_n_vars(diff_context_t* ctx, node_t* node, int* res)
{
    ASSERT(ctx);
    ASSERT(node);
    ASSERT(res);

    //-------------------------------------------------------------------//

    if (node->arg_type == VAR)
    {
        (*res)++;
        return DIFF_SUCCESS;
    }

    if (node->left)
    {
        VERIFY(count_n_vars(ctx, node->left, res) != DIFF_SUCCESS,
               return DIFF_COUNT_N_VARS_ERROR);
    }

    if (node->right)
    {
        VERIFY(count_n_vars(ctx, node->right, res) != DIFF_SUCCESS,
               return DIFF_COUNT_N_VARS_ERROR);
    }

    return DIFF_SUCCESS;
}

//===================================================================//

bool is_equal(num_t n1, num_t n2)
{
    return fabs(n1 - n2) < 0.00001;
}

//===================================================================//

diff_status_t get_derivative_in_point(diff_context_t* ctx,
                                      node_t*         expression,
                                      int             n_memb,
                                      num_t*          coeffs,
                                      num_t           point)
{
    ASSERT(ctx);

    //-------------------------------------------------------------------//

    print_tex(ctx, "\\centerline{Посчитаем %d производную}\n", n_memb);

    expression = _QDIFF(expression);

    //-------------------------------------------------------------------//

    node_t* cp_expression = copy_tree(ctx, expression);

    VERIFY(calc_in_point(cp_expression, 0) != DIFF_SUCCESS,
           return DIFF_CALC_IN_POINT_ERROR);

    print_tex(ctx, "\\centerline{В нуле она равна %lg}", cp_expression->val.num);

    //-------------------------------------------------------------------//

    coeffs[n_memb] = cp_expression->val.num;

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t get_derivaties_in_point(diff_context_t* ctx,
                                      node_t*         expression,
                                      int             n,
                                      num_t*          coeffs,
                                      num_t           point)
{
    ASSERT(ctx);
    ASSERT(expression);
    ASSERT(coeffs);

    //-------------------------------------------------------------------//

    print_tex(ctx, "\\centerline{Разложим в окрестности %lg по формуле"
                   " тейлора до $\\tilde{o}(x^%d)$ вот такую функцию} "
                   "\n\\begin{equation}\n"
                   "f(x) = ", point, n);
    _TEX(expression);
    print_tex(ctx, "\n\\end{equation}\n");

    //-------------------------------------------------------------------//

    for (int i = 0; i < n; i++)
    {
        get_derivative_in_point(ctx, expression, i + 1, coeffs, point);
    }

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t get_taylor_formula(diff_context_t* ctx, const int n, num_t* coeffs, num_t point)
{
    ASSERT(coeffs);

    //-------------------------------------------------------------------//

    print_tex(ctx, "\\centerline{Формула Тейлора}"
                   "\n\\begin{equation}\n"
                   "f(x) = ");

    //-------------------------------------------------------------------//

    node_t* cp_root = copy_tree(ctx, ctx->root);
    calc_in_point(cp_root, coeffs[0]);

    //-------------------------------------------------------------------//

    char  buf[100] = {};
    char* buf_ptr = &buf[0];
    int nchars    = 0;

    print_tex(ctx, "%lg", cp_root->val.num);
    sprintf(buf_ptr, "%lg%n", cp_root->val.num, &nchars);
    buf_ptr += nchars;

    for (int i = 1; i < n + 1; i++)
    {
        print_tex(ctx, " + \\frac{%lg}{%d!}x^%d", coeffs[i], i, i);
        sprintf(buf_ptr, " + (x**%d)/((%lg)*(%d!))%n", i, cp_root->val.num, i, &nchars);
        buf_ptr += nchars;
    }

    print_tex(ctx, "\n\\end{equation}\n");

    //-------------------------------------------------------------------//

    char command[200] = {};
    sprintf(command, "gnuplot -p -e \"set terminal pngcairo; set output 'func.png'; plot %s", buf);

    printf("%s", command);
    system(command);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t taylor(diff_context_t* ctx, node_t* root)
{
    ASSERT(ctx);
    ASSERT(root);

    //-------------------------------------------------------------------//

    const int n         = 3;
    num_t coeffs[n + 1] = {};
    num_t point         = 0;

    node_t* cp_expression = copy_tree(ctx, root);
    coeffs[0] = calc_in_point(cp_expression, 0);

    get_derivaties_in_point(ctx, root, n, coeffs, point);

    get_taylor_formula(ctx, n, coeffs, point);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//
