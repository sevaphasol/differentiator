#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include <string.h>
#include <sys/stat.h>
#include <stdarg.h>

//-------------------------------------------------------------------//

#include "operations.h"
#include "tex_dump.h"
#include "node_allocator.h"
#include "custom_assert.h"
#include "dsl.h"
#include "plot_dump.h"

//———————————————————————————————————————————————————————————————————//

static diff_status_t phrases_strings_ctor    (dump_info_t* dump_info);

static int           count_number_of_strings (char* text);

static diff_status_t get_file_size           (FILE* fp,
                                              size_t* size);

//———————————————————————————————————————————————————————————————————//

#define _PRINT(...) fprintf(ctx->dump_info.tex_file, ##__VA_ARGS__)
#define _PUTC(symb) fputc(symb, ctx->dump_info.tex_file)

//———————————————————————————————————————————————————————————————————//

diff_status_t renames_encrypt(diff_context_t* ctx, node_t* node)
{
    ASSERT(ctx);
    ASSERT(node);

    //-------------------------------------------------------------------//

    if (node->alias.renamed)
    {
        _PRINT("$$%c = ", node->alias.name);
        node->alias.renamed = false;
        _TEX(node);
        _PRINT("$$\n");
        node->alias.renamed = true;
    }

    if (node->left)  {renames_encrypt(ctx, node->left); }
    if (node->right) {renames_encrypt(ctx, node->right);}

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t print_tex(diff_context_t* ctx, const char* str, ...)
{
    ASSERT(ctx);

    //-------------------------------------------------------------------//

    va_list list;
    va_start(list, str);

    vfprintf(ctx->dump_info.tex_file, str, list);

    va_end(list);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t print_graphic(diff_context_t* ctx,
                            node_t* node,
                            const char* file_name)
{
    ASSERT(ctx);
    ASSERT(node);

    //-------------------------------------------------------------------//

    plot_dump(ctx, node, file_name);
    print_tex(ctx, "\\begin{center}\n"
                   "\\includegraphics[scale=0.5]{%s}\n"
                   "\\end{center}\n", file_name);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t write_derivative_tex_intro(diff_context_t* ctx, node_t* node)
{
    ASSERT(ctx);

    //-------------------------------------------------------------------//

    fprintf(ctx->dump_info.tex_file, "\\centerline{Ща производную"
                                     " такой вот функции за яйца возьмём}"
                                     "\n\\begin{equation}\n"
                                     "f(x) = ");
    _TEX(ctx->root);
    fprintf(ctx->dump_info.tex_file, "\n\\end{equation}\n");

    //-------------------------------------------------------------------//

    print_graphic(ctx, node, "start_func.png");

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t write_derivative_tex_outro(diff_context_t* ctx, node_t* node)
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

#undef _PRINT
#undef _PUTC

//———————————————————————————————————————————————————————————————————//
