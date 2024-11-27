#include <stdio.h>
#include <string.h>
#include <syscall.h>

//-------------------------------------------------------------------//

#include "operations.h"
#include "tree_dump.h"
#include "node_allocator.h"
#include "custom_assert.h"


//———————————————————————————————————————————————————————————————————//

static tree_dump_status_t recursively_make_dot_node(node_t* node, FILE* file, int* node_number);

//———————————————————————————————————————————————————————————————————//

tree_dump_status_t dot_dump(diff_context_t* ctx)
{
    VERIFY(!ctx, return TREE_DUMP_STRUCT_NULL_PTR_ERROR);

    //-------------------------------------------------------------------//

    char dot_file_name[FileNameBufSize] = {};
    snprintf(dot_file_name, FileNameBufSize, LOGS_DIR "/" DOTS_DIR "/" "%03d.dot", ctx->dump_info.n_dumps);
    FILE* dot_file = fopen(dot_file_name, "w");
    VERIFY(!dot_file, return TREE_DUMP_FILE_OPEN_ERROR);

    fprintf(dot_file, "digraph G{\n"
                      "rankdir=HR;\n"
                      "node[style=filled, color=\"%s\", fillcolor=\"%s\","
                      "fontcolor=\"%s\", fontsize=14];\n"
                      "edge[color=\"%s\", fontsize=12, penwidth=1, "
                      "fontcolor = \"%s\"];\n"
                      "bgcolor=\"%s\";\n",
                      NodeBorderColor, NodeBackGroundColor, NodeFontColor,
                      EdgeColor, EdgeFontColor,
                      BackGroundColor);

    //-------------------------------------------------------------------//

    int node_number = 1;
    recursively_make_dot_node(ctx->root, dot_file, &node_number);

    fputs("}\n", dot_file);
    fclose(dot_file);

    //-------------------------------------------------------------------//

    char png_file_name[FileNameBufSize] = {};
    snprintf(png_file_name, FileNameBufSize, LOGS_DIR "/" IMGS_DIR "/" "%03d.png", ctx->dump_info.n_dumps);

    //-------------------------------------------------------------------//

    char command[SysCommandBufSize] = {};
    snprintf(command, SysCommandBufSize, "touch %s; dot %s -Tpng -o %s",
             png_file_name, dot_file_name, png_file_name);

    system(command);

    //-------------------------------------------------------------------//

    ctx->dump_info.n_dumps++;

    //-------------------------------------------------------------------//

    return TREE_DUMP_SUCCESS;
}

//===================================================================//

tree_dump_status_t recursively_make_dot_node(node_t* node, FILE* file, int* node_number)
{
    ASSERT(node);
    ASSERT(file);
    ASSERT(node_number);

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////!!WARNING!COPYPAST!!////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////

    //-------------------------------------------------------------------//

    switch(node->arg_type)
    {
        case NUM:
        {
            fprintf(file, "elem%d["
                "shape=\"Mrecord\", "
                "label= \"{%s | %lg}\""
                "];\n",
                *node_number,
                "NUM",
                node->val.num);
            break;
        }
        case VAR:
        {
            fprintf(file, "elem%d["
                "shape=\"Mrecord\", "
                "label= \"{%s | %s}\""
                "];\n",
                *node_number,
                "VAR",
                "x");
            break;
        }
        case OPR:
        {
            fprintf(file, "elem%d["
                "shape=\"Mrecord\", "
                "label= \"{%s | %s}\""
                "];\n",
                *node_number,
                "OPR",
                OperationsTable[node->val.opr].name);
            break;
        }
        default:
        {
            break;
        }
    }

    //-------------------------------------------------------------------//

    int head_node_number = *node_number;

    if (node->left)
    {
        int left_node_number = ++*node_number;

        fprintf(file, "elem%d->elem%d;",
                      head_node_number, left_node_number);

        recursively_make_dot_node(node->left, file, node_number);
    }

    if (node->right)
    {
        int right_node_number = ++*node_number;

        fprintf(file, "elem%d->elem%d;",
                       head_node_number, right_node_number);

        recursively_make_dot_node(node->right, file, node_number);
    }

    //-------------------------------------------------------------------//

    return TREE_DUMP_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//
