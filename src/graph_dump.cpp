#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include <string.h>
#include <sys/stat.h>
#include <stdarg.h>

//-------------------------------------------------------------------//

#include "operations.h"
#include "graph_dump.h"
#include "node_allocator.h"
#include "custom_assert.h"
#include "dsl.h"

//———————————————————————————————————————————————————————————————————//

static tree_dump_status_t make_edges     (node_t* node,
                                          FILE*   file,
                                          int*    node_number);

static tree_dump_status_t make_node      (node_t* node,
                                          FILE* file,
                                          int* node_number);

static tree_dump_status_t create_png     (const char* dot_file_name,
                                          const char* png_file_name);

static tree_dump_status_t get_file_name  (char* file_name,
                                          int file_number);

static tree_dump_status_t dot_file_init  (FILE* dot_file);

//———————————————————————————————————————————————————————————————————//

tree_dump_status_t graph_dump(diff_context_t* ctx, node_t* root)
{
    VERIFY(!ctx, return TREE_DUMP_STRUCT_NULL_PTR_ERROR);

    //-------------------------------------------------------------------//

    char dot_file_name[FileNameBufSize] = {};
    get_file_name(dot_file_name, ctx->dump_info.n_dumps);

    FILE* dot_file = fopen(dot_file_name, "w");
    VERIFY(!dot_file, return TREE_DUMP_FILE_OPEN_ERROR);

    dot_file_init(dot_file);

    //-------------------------------------------------------------------//

    int node_number = 1;
    make_edges(root, dot_file, &node_number);

    fputs("}\n", dot_file);
    fclose(dot_file);

    //-------------------------------------------------------------------//

    char png_file_name[FileNameBufSize] = {};
    get_file_name(png_file_name, ctx->dump_info.n_dumps);

    create_png(dot_file_name, png_file_name);

    //-------------------------------------------------------------------//

    ctx->dump_info.n_dumps++;

    //-------------------------------------------------------------------//

    return TREE_DUMP_SUCCESS;
}

//===================================================================//

tree_dump_status_t get_file_name(char* file_name, int file_number)
{
    ASSERT(file_name);

    //-------------------------------------------------------------------//

    snprintf(file_name, FileNameBufSize,
             LOGS_DIR "/" DOTS_DIR "/" "%03d.dot",
             file_number);

    //-------------------------------------------------------------------//

    return TREE_DUMP_SUCCESS;
}

//===================================================================//

tree_dump_status_t dot_file_init(FILE* dot_file)
{
    ASSERT(dot_file);

    //-------------------------------------------------------------------//

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

    return TREE_DUMP_SUCCESS;
}

tree_dump_status_t create_png(const char* dot_file_name,
                              const char* png_file_name)
{
    ASSERT(dot_file_name);
    ASSERT(png_file_name);

    //-------------------------------------------------------------------//

    char command[SysCommandBufSize] = {};
    snprintf(command, SysCommandBufSize, "touch %s; dot %s -Tpng -o %s",
             png_file_name, dot_file_name, png_file_name);

    VERIFY(!system(command),
           return TREE_DUMP_SYSTEM_COMMAND_ERROR);

    //-------------------------------------------------------------------//

    return TREE_DUMP_SUCCESS;
}

//===================================================================//

tree_dump_status_t make_edges(node_t* node, FILE* file, int* node_number)
{
    ASSERT(node);
    ASSERT(file);
    ASSERT(node_number);

    //-------------------------------------------------------------------//

    make_node(node, file, node_number);

    //-------------------------------------------------------------------//

    int head_node_number = *node_number;

    if (node->left)
    {
        int left_node_number = ++*node_number;

        fprintf(file, "elem%p->elem%p;",
                      node, node->left);

        make_edges(node->left, file, node_number);
        fprintf(file, "elem%p->elem%p;",
                       node, node->right);

        make_edges(node->right, file, node_number);
    }

    //-------------------------------------------------------------------//

    return TREE_DUMP_SUCCESS;
}

//===================================================================//

tree_dump_status_t make_node(node_t* node, FILE* file, int* node_number)
{
    ASSERT(node);
    ASSERT(file);
    ASSERT(node_number);

    //-------------------------------------------------------------------//

    switch(node->arg_type)
    {
        case NUM:
        {
            fprintf(file, "elem%d["
                          "shape=\"Mrecord\", "
                          "label= \"{%s | val = %lg |"
                          " metrics = %d | name = %c}\"];\n",
                          *node_number,
                          "NUM",
                          node->val.num,
                          node->alias.metrics,
                          node->alias.name);
            break;
        }
        case VAR:
        {
            fprintf(file, "elem%d["
                          "shape=\"Mrecord\", "
                          "label= \"{%s | val = %s |"
                          " metrics = %d | name = %c}\"];\n",
                          *node_number,
                          "VAR",
                          "x",
                          node->alias.metrics,
                          node->alias.name);
            break;
        }
        case OPR:
        {
            fprintf(file, "elem%d["
                          "shape=\"Mrecord\", "
                          "label= \"{%s | val = %s |"
                          " metrics = %d | name = %c}\"];\n",
                          *node_number,
                          "OPR",
                          OperationsTable[node->val.opr].name,
                          node->alias.metrics,
                          node->alias.name);
            break;
        }
        default:
        {
            ASSERT(!"make node error");

            break;
        }
    }

    //-------------------------------------------------------------------//

    return TREE_DUMP_SUCCESS;
}

//———————————————————————————————————————————————————————————————————//
