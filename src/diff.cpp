#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

//-------------------------------------------------------------------//

#include "node_allocator.h"
#include "diff.h"
#include "operations.h"
#include "custom_assert.h"
#include "dsl.h"
#include "tree_dump.h"

//———————————————————————————————————————————————————————————————————//

const int nAllocatedNodes = 1024;

//-------------------------------------------------------------------//

const char* const PhrasesFile = "phrases.txt";

//-------------------------------------------------------------------//

const char* const TexFile  = "diff.tex";

const char* const TexIntro = "\\documentclass[12pt, a4paper]{article}\n"
                             "\\usepackage[T2A]{fontenc}\n"
                             "\\usepackage[utf8x]{inputenc}\n"
                             "\\usepackage[english, russian]{babel}\n"
                             "\\usepackage{mathtools}\n"
                             "\\DeclareMathOperator{\\arcsinh}{arcsinh}\n"
                             "\\DeclareMathOperator{\\arccosh}{arccosh}\n"
                             "\\DeclareMathOperator{\\arctanh}{arctanh}\n"
                             "\\DeclareMathOperator{\\arccoth}{arccoth}\n"
                             "\\begin{document}\n"
                             "\\title{Производная туда сюда\n}"
                             "\\author{Севсоль, 1 курс ЭРТЭ}\n"
                             "\\date{\\today}\n"
                             "\\maketitle Ща проивзодну за яйца возьмём\\\n";

const char* const TexEnd   = "Вот мы и посчитали производную. Кстати,"
                             " уважаемая КВМ, пососите мои яйки.";

const char* const TexOutro = "\n\\end{document}\n";

//———————————————————————————————————————————————————————————————————//

static diff_status_t read_phrases            (dump_info_t* dump_info, FILE* fp);
static diff_status_t phrases_strings_ctor    (dump_info_t* dump_info);
static int           count_number_of_strings (char* text);
static diff_status_t get_file_size(FILE* fp, size_t* size);

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

diff_status_t read_phrases(dump_info_t* dump_info, FILE* fp)
{
    ASSERT(dump_info);
    ASSERT(fp);

    //-------------------------------------------------------------------//

    size_t size = 0;

    VERIFY(get_file_size(fp, &size),
                         return  DIFF_FILE_OPEN_ERROR);

    //-------------------------------------------------------------------//

    dump_info->phrases_buf = (char*) calloc(size, sizeof(char));
    VERIFY(!dump_info->phrases_buf, return DIFF_ALLOCATE_ERROR);

    VERIFY(fread(dump_info->phrases_buf, sizeof(char), size, fp) != size,
           return DIFF_FILE_READ_ERROR);

    //-------------------------------------------------------------------//

    fclose(fp);

    //-------------------------------------------------------------------//

    VERIFY(phrases_strings_ctor(dump_info) != DIFF_SUCCESS,
           return DIFF_PHRASES_STRINGS_CTOR_ERROR);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

diff_status_t phrases_strings_ctor(dump_info_t* dump_info)
{
    ASSERT(dump_info)

    //-------------------------------------------------------------------//

    dump_info->n_phrases = count_number_of_strings(dump_info->phrases_buf);

    dump_info->phrases = (char**) calloc(dump_info->n_phrases, sizeof(char*));
    VERIFY(!dump_info->phrases,
           return DIFF_ALLOCATE_ERROR);

    //-------------------------------------------------------------------//

    dump_info->phrases[0] = strtok(dump_info->phrases_buf, "\n");

    for (int i = 1; i < dump_info->n_phrases; i++)
    {
        dump_info->phrases[i] = strtok(nullptr, "\n");
    }

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

int count_number_of_strings(char* text)
{
    ASSERT(text);

    //-------------------------------------------------------------------//

    int n_strings = 0;

    char* cursor = text;
    while (cursor = strchr(cursor, '\n'))
    {
        n_strings++;
        cursor++;
    }

    //-------------------------------------------------------------------//

    return n_strings;
}

//===================================================================//

diff_status_t get_file_size(FILE* fp, size_t* size)
{
    ASSERT(fp);
    ASSERT(size);

    //-------------------------------------------------------------------//

    struct stat file_status = {};

    VERIFY((fstat(fileno(fp), &file_status) < 0),
                        return DIFF_GET_FILE_SIZE_ERROR);

    *size = file_status.st_size;

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

diff_status_t write_tex_outro(diff_context_t* ctx)
{
    ASSERT(ctx);

    //-------------------------------------------------------------------//

    fprintf(ctx->dump_info.tex_file, "\n\n%s\n", TexEnd);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t tex_dump(diff_context_t* ctx, node_t* tree)
{
    ASSERT(ctx);
    ASSERT(tree);

    //-------------------------------------------------------------------//

    fprintf(ctx->dump_info.tex_file, "\n\\begin{equation}\n");
    _TEX(tree);
    fprintf(ctx->dump_info.tex_file, "\n\\end{equation}\n");

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t dump(diff_context_t* ctx, node_t* tree)
{
    ASSERT(ctx);
    ASSERT(tree);

    //-------------------------------------------------------------------//

    VERIFY(dot_dump(ctx) != TREE_DUMP_SUCCESS,
           return DIFF_DOT_DUMP_ERROR);

    //-------------------------------------------------------------------//

    VERIFY(tex_dump(ctx, tree) != DIFF_SUCCESS,
           return DIFF_TEX_DUMP_ERROR);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t try_calc(node_t** tree)
{
    ASSERT(tree);
    ASSERT(*tree);

    //-------------------------------------------------------------------//

    switch ((*tree)->arg_type)
    {
        case NUM: return DIFF_SUCCESS;
        case VAR: return DIFF_NOT_CONSTANT;
        case OPR:
        {
            if(try_calc(&((*tree)->left)) != DIFF_SUCCESS)
            {
                    return DIFF_NOT_CONSTANT;
            }

            if (OperationsTable[(*tree)->val.opr].binary)
            {
                if (try_calc(&((*tree)->right)) != DIFF_SUCCESS)
                {
                       return DIFF_NOT_CONSTANT ;
                }

                (*tree)->arg_type = NUM;
                (*tree)->val.num  = (*tree)->calc_func((*tree)->left->val.num,
                                                (*tree)->right->val.num);

                return DIFF_SUCCESS;
            }
            else
            {
                (*tree)->arg_type = NUM;
                (*tree)->val.num  = (*tree)->calc_func((*tree)->left->val.num, 0);

                return DIFF_SUCCESS;
            }
        }
        default: ASSERT(0);
    }

    return DIFF_TRY_CALC_ERROR;
}

//===================================================================//

diff_status_t optimize_tree(node_t** root)
{
    ASSERT(*root);
    ASSERT(root);

    VERIFY(try_calc(root) == DIFF_TRY_CALC_ERROR,
           return DIFF_TRY_CALC_ERROR);

    return DIFF_SUCCESS;
}

//===================================================================//

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

//===================================================================//

node_t* diff_tree(diff_context_t* ctx, node_t* root)
{
    ASSERT(ctx);
    ASSERT(root);

    //-------------------------------------------------------------------//

    return _DIFF(root);
}

//===================================================================//

node_t* copy_tree(node_t* root)
{
    ASSERT(root);

    //-------------------------------------------------------------------//

    return root;
}

//===================================================================//
