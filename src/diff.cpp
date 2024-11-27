#include "node_allocator.h"
#include "diff.h"
#include "operations.h"
#include "custom_assert.h"
#include "dsl.h"
#include "tree_dump.h"

//———————————————————————————————————————————————————————————————————//

const int nAllocatedNodes = 1024;

//-------------------------------------------------------------------//

const char* const TexFile  = "diff.tex";

const char* const TexIntro = "\\documentclass{article}\n"
                             "\\begin{document}\n";

const char* const TexOutro = "\n\\end{document}\n";

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

    FILE* tex_file = fopen(TexFile, "w");
    VERIFY(!tex_file,
           return DIFF_FILE_OPEN_ERROR);

    ctx->tex_file_name = TexFile;
    ctx->tex_file      = tex_file;

    fprintf(tex_file, "%s", TexIntro);

    //-------------------------------------------------------------------//

    ctx->n_dumps = 0;

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//

diff_status_t diff_context_dtor(diff_context_t* ctx)
{
    ASSERT(ctx);
    ASSERT(ctx->node_allocator);
    ASSERT(ctx->tex_file);
    ASSERT(ctx->tex_file_name);

    //-------------------------------------------------------------------//

    node_allocator_dtor(ctx->node_allocator);

    //-------------------------------------------------------------------//

    fprintf(ctx->tex_file, "%s", TexOutro);
    fclose(ctx->tex_file);

    char command[SysCommandBufSize] = {};
    snprintf(command, SysCommandBufSize, "pdflatex %s", ctx->tex_file_name);

    system(command);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//

diff_status_t dump(diff_context_t* ctx, node_t* tree)
{
    ASSERT(ctx);
    ASSERT(tree);

    //-------------------------------------------------------------------//

    VERIFY(tree_dump(ctx) != TREE_DUMP_SUCCESS,
           return DIFF_DOT_DUMP_ERROR);

    //-------------------------------------------------------------------//

    fprintf(ctx->tex_file, "\n\\begin{equation}\n");
    _TEX(tree);
    fprintf(ctx->tex_file, "\n\\end{equation}\n");

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//

diff_status_t optimize_tree(node_t* tree)
{
}

//———————————————————————————————————————————————————————————————————//

num_t calc_tree(node_t* root)
{
    ASSERT(root);

    //-------------------------------------------------------------------//

    num_t val = 0;

    switch (root->arg_type)
    {
        case NUM:
        {
            return root->val.num;
        }

        case OPR:
        {
            return OperationsTable[root->val.opr].calc_func(
                calc_tree(root->left),
                calc_tree(root->right));
        }

        default:
        {
            ASSERT(0);
        }
    }

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//

node_t* diff_tree(diff_context_t* ctx, node_t* root)
{
    ASSERT(ctx);
    ASSERT(root);

    //-------------------------------------------------------------------//

    return _DIFF(root);
}

//———————————————————————————————————————————————————————————————————//

node_t* copy_tree(node_t* root)
{
    ASSERT(root);

    //-------------------------------------------------------------------//

    return root;
}

//———————————————————————————————————————————————————————————————————//
