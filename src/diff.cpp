#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//-------------------------------------------------------------------//

#include "node_allocator.h"
#include "diff.h"
#include "operations.h"
#include "custom_assert.h"
#include "dsl.h"
#include "tree_dump.h"
#include "tree_dump.h"

//———————————————————————————————————————————————————————————————————//

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

    ctx->dump_info.n_dumps = 0;

    //-------------------------------------------------------------------//

    FILE* phrases_file = fopen(PhrasesFile, "rb");
    VERIFY(!phrases_file,
           return DIFF_FILE_OPEN_ERROR);

    VERIFY(read_phrases(&ctx->dump_info, phrases_file) != DIFF_SUCCESS,
           return DIFF_READ_PHRASES_ERROR);

    srand((unsigned int) time(NULL));

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
    snprintf(command, SysCommandBufSize, "pdflatex %s", ctx->dump_info.tex_file_name);

    system(command);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
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
            return(try_calc_opr(tree));
        }

        default: ASSERT(0);
    }

    return DIFF_TRY_CALC_ERROR;
}

//===================================================================//

diff_status_t try_calc_opr(node_t* tree)
{
    ASSERT(tree);
    ASSERT(tree->left);

    //-------------------------------------------------------------------//

    if (try_calc(tree->left) != DIFF_SUCCESS)
    {
        return DIFF_NOT_CONSTANT;
    }

    tree->arg_type       = NUM;
    tree->diff_func      = &diff_num;
    tree->tex_func       = &tex_num;
    tree->simplify_func  = &simplify_num;

    if (OperationsTable[tree->val.opr].binary)
    {
        ASSERT(tree->right);

        if (try_calc(tree->right) != DIFF_SUCCESS)
        {
                return DIFF_NOT_CONSTANT;
        }

        tree->val.num  = tree->calc_func(tree->left->val.num,
                                            tree->right->val.num);
        tree->left  = nullptr;
        tree->right = nullptr;

        return DIFF_SUCCESS;
    }
    else
    {
        tree->val.num  = tree->calc_func(tree->left->val.num, 0);

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

    return _DIFF(root);
}

//===================================================================//

node_t* copy_tree(diff_context_t* ctx, node_t* root)
{
    ASSERT(ctx);

    //-------------------------------------------------------------------//

    if (!root) {return nullptr;}

    node_allocator_t* node_allocator = ctx->node_allocator;
    node_t* node = _NUM(0);

    *node = *root;

    node->left  = copy_tree(ctx, root->left);
    node->right = copy_tree(ctx, root->right);

    //-------------------------------------------------------------------//

    return node;
}

//———————————————————————————————————————————————————————————————————//
