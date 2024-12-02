#ifndef TREE_DUMP_H__
#define TREE_DUMP_H__

//———————————————————————————————————————————————————————————————————//

#include <stdio.h>
#include <stdlib.h>

#include "diff.h"

//———————————————————————————————————————————————————————————————————//

#define LOGS_DIR "logs"
#define DOTS_DIR "dot_files"
#define IMGS_DIR "images"

//———————————————————————————————————————————————————————————————————//

enum tree_dump_status_t
{
    TREE_DUMP_SUCCESS = 0,
    TREE_DUMP_STRUCT_NULL_PTR_ERROR,
    TREE_DUMP_FILE_OPEN_ERROR,
};

//———————————————————————————————————————————————————————————————————//

const size_t FileNameBufSize   = 64;
const size_t SysCommandBufSize = 278;

//———————————————————————————————————————————————————————————————————//

const char* const BackGroundColor     = "#bcbddc";
const char* const NodeBackGroundColor = "#a1d99b";
const char* const NodeBorderColor     = "#756bb1";
const char* const EdgeColor           = "#006d2c";
const char* const NodeFontColor       = "#ba3d3d";
const char* const EdgeFontColor       = "#49006a";

//———————————————————————————————————————————————————————————————————//

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
                             "\\maketitle \n";

const char* const TexStart = "";

const char* const TexEnd   = "Вот мы и посчитали производную. Кстати,"
                             " уважаемая КВМ, пососите мои яйки.";

const char* const TexOutro = "\n\\end{document}\n";
const char* const PhrasesFile = "phrases.txt";

//———————————————————————————————————————————————————————————————————//

tree_dump_status_t dot_dump                   (diff_context_t* ctx, node_t* node);
diff_status_t      tex_dump                   (diff_context_t* ctx, node_t* node);
diff_status_t      write_derivative_tex_intro (diff_context_t* ctx);
diff_status_t      write_derivative_tex_outro (diff_context_t* ctx);
diff_status_t      print_tex                  (diff_context_t* ctx, const char* str, ...);
diff_status_t      read_phrases               (dump_info_t* dump_info, FILE* fp);
diff_status_t      renames_encrypt            (diff_context_t* ctx, node_t* node);


//———————————————————————————————————————————————————————————————————//

#endif // TREE_DUMP_H__
