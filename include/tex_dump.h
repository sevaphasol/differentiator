#ifndef TEX_DUMP_H__
#define TEX_DUMP_H__

//———————————————————————————————————————————————————————————————————//

#include <stdio.h>
#include <stdlib.h>

#include "diff.h"

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

diff_status_t tex_dump                   (diff_context_t* ctx,
                                          node_t*         node);
diff_status_t write_derivative_tex_intro (diff_context_t* ctx,
                                          node_t*         node);

diff_status_t write_derivative_tex_outro (diff_context_t* ctx,
                                          node_t*         node);

diff_status_t print_tex                  (diff_context_t* ctx, const char* str, ...);
diff_status_t renames_encrypt            (diff_context_t* ctx, node_t* node);
diff_status_t read_phrases               (dump_info_t* dump_info, FILE* fp);

//———————————————————————————————————————————————————————————————————//

#endif // TEX_DUMP_H__
