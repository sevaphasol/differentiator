#ifndef PLOT_DUMP_H__
#define PLOT_DUMP_H__

//———————————————————————————————————————————————————————————————————//

#include <stdio.h>
#include <stdlib.h>

#include "diff.h"

//———————————————————————————————————————————————————————————————————//

const char* const PlotFile        = "plots.txt";

const int ExpressionLengthBufSize = 400;
const int PngCreateCommandBufSize = 600;

const int TaylorPngFileNameSize   = 100;

//———————————————————————————————————————————————————————————————————//

diff_status_t plot_dump (diff_context_t* ctx,
                         node_t* tree,
                         const char* png_file_name);

//———————————————————————————————————————————————————————————————————//

#endif // PLOT_DUMP_H__
