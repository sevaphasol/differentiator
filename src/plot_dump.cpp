#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include <string.h>
#include <sys/stat.h>
#include <stdarg.h>

//-------------------------------------------------------------------//

#include "operations.h"
#include "plot_dump.h"
#include "node_allocator.h"
#include "custom_assert.h"
#include "dsl.h"

//———————————————————————————————————————————————————————————————————//

diff_status_t read_expression_in_string (diff_context_t* ctx,
                                         char* expr);

diff_status_t make_png_file             (const char* expr,
                                         const char* png_file_name);

//———————————————————————————————————————————————————————————————————//

diff_status_t plot_dump(diff_context_t* ctx,
                        node_t* tree,
                        const char* png_file_name)
{
    ASSERT(ctx);
    ASSERT(tree);

    //-------------------------------------------------------------------//

    _PLOT(tree);
    char expr[ExpressionLengthBufSize];

    read_expression_in_string(ctx, expr);

    make_png_file(expr, png_file_name);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t make_png_file(const char* expr,
                            const char* png_file_name)
{
    ASSERT(expr);
    ASSERT(png_file_name);

    //-------------------------------------------------------------------//

    char command[PngCreateCommandBufSize] = {};
    snprintf(command, PngCreateCommandBufSize,
             "gnuplot -p -e \""
             " set terminal pngcairo;"
             " set nokey;"
             " set output '%s';"
             " set multiplot;"
             " set xzeroaxis;"
             " set xtics axis;"
             " set xrange [-15:15];"
             " set yzeroaxis;"
             " set ytics axis;"
             " set yrange [-15:15];"
             " set border 0;"
             " plot %s\"", png_file_name, expr);

    system(command);

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//===================================================================//

diff_status_t read_expression_in_string(diff_context_t* ctx,
                                        char* expr)
{
    ASSERT(ctx);
    ASSERT(ctx->dump_info.plots_file);
    ASSERT(ctx->dump_info.plots_file_name);
    ASSERT(expr);

    //-------------------------------------------------------------------//

    fclose(ctx->dump_info.plots_file);
    fopen (ctx->dump_info.plots_file_name, "r");

    //-------------------------------------------------------------------//

    VERIFY(!fgets(expr, ExpressionLengthBufSize,
                  ctx->dump_info.plots_file),
           return DIFF_TOO_LONG_EXPRESSION_ERROR);

    //-------------------------------------------------------------------//

    fclose(ctx->dump_info.plots_file);
    fopen (ctx->dump_info.plots_file_name, "w");

    //-------------------------------------------------------------------//

    return DIFF_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//
