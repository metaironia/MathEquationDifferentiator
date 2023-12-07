#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "math_tree/math_tree_node_data.h"
#include "math_tree/math_tree_func.h"

#include "tree_log.h"
#include "tree_func.h"

FILE *TREE_LOG_FILE = CreateLogFile ("tree_log.txt");

FILE *CreateLogFile (const char *log_file_name) {

    assert (log_file_name);

    FILE *log_file_ptr = fopen (log_file_name, "w");
    assert (log_file_ptr);

    atexit (CloseLogFile);

    return log_file_ptr;
}

void CloseLogFile (void) {

    if (TREE_LOG_FILE)
        fclose (TREE_LOG_FILE);

    TREE_LOG_FILE = NULL;
}

enum TreeFuncStatus LogPrintTreeError (const char *error_text) {

    assert (error_text);

    LOG_PRINT (TREE_LOG_FILE, "An error %s occurred.\n ", error_text);

    return TREE_STATUS_OK;
}

enum TreeFuncStatus MathTreeGraphDump (const Tree *tree_for_graph_dump) {

    assert (tree_for_graph_dump);

    FILE *tree_dot_file = fopen (TREE_DOT_FILE_NAME, "w");
    assert (tree_dot_file);

    TreeDotFileBegin (tree_dot_file);

    TreeDotFileCreateElements (tree_dot_file, tree_for_graph_dump -> root);
    TreeDotFileDrawArrows     (tree_dot_file, tree_for_graph_dump -> root);

    TreeDotFileEnd (tree_dot_file);

    TreeImageCreate (tree_dot_file);

    return TREE_STATUS_OK;
}

enum TreeFuncStatus TreeImageCreate (FILE *tree_dot_file) {

    assert (tree_dot_file);

    system (CommandToCreateImageCreate (ImageNameCreate ()));

    return TREE_STATUS_OK;
}

const char *ImageNameCreate (void) {

    static int image_number = 0;
    static char image_name[MAX_IMAGE_NAME_LENGTH + 1] = {};

    memset (image_name, 0, MAX_IMAGE_NAME_LENGTH + 1);

    sprintf (image_name, "math_tree_img_%d.png", image_number++);

    return image_name;
}

const char *CommandToCreateImageCreate (const char *image_name) {

    assert (image_name);

    static char command_to_create_image[MAX_COMMAND_LENGTH + 1] = {};

    memset (command_to_create_image, 0, MAX_COMMAND_LENGTH + 1);

    sprintf (command_to_create_image, "dot tree_dot_dump.dot -T png -o %s", image_name);

    return command_to_create_image;
}

enum TreeFuncStatus TreeDotFileBegin (FILE *tree_dot_file_begin) {

    assert (tree_dot_file_begin);

    LOG_PRINT (tree_dot_file_begin, "digraph AkinatorTree{\n"
                                    "rankdir = TB;\n"
                                    "graph [bgcolor = white];\n");

    return TREE_STATUS_OK;
}

enum TreeFuncStatus TreeDotFileEnd (FILE *tree_dot_file_end) {

    assert (tree_dot_file_end);

    LOG_PRINT (tree_dot_file_end, "\n}\n");

    return TREE_STATUS_OK;
}

enum TreeFuncStatus TreeDotFileSetColorElement (FILE *tree_dot_file_elem_for_set_color,
                                                const TreeNode *tree_node_for_set_color) {

    assert (tree_dot_file_elem_for_set_color);
    assert (tree_node_for_set_color -> data);

    if (tree_node_for_set_color -> data -> nodeType == NUMBER)
        LOG_PRINT (tree_dot_file_elem_for_set_color, "fillcolor = orange, ");

    else if (tree_node_for_set_color -> data -> nodeType == VARIABLE)
        LOG_PRINT (tree_dot_file_elem_for_set_color, "fillcolor = blue, ");

    else if (tree_node_for_set_color -> data -> nodeType == NODE_TYPE_ERROR)
        LOG_PRINT (tree_dot_file_elem_for_set_color, "fillcolor = red, ");

    else
        LOG_PRINT (tree_dot_file_elem_for_set_color, "fillcolor = lightgreen, ");

    return TREE_STATUS_OK;
}

enum TreeFuncStatus TreeDotFileCreateElements (FILE *tree_dot_file_gen_elems,
                                               const TreeNode *tree_node_for_gen_elems) {

    assert (tree_dot_file_gen_elems);

    if (tree_node_for_gen_elems) {

        if (tree_node_for_gen_elems)

        LOG_PRINT (tree_dot_file_gen_elems, NODE_START_SYMBOL "%llx [shape=record, "
                                            "style = filled, ",
                                            (size_t) (tree_node_for_gen_elems));

        TreeDotFileSetColorElement (tree_dot_file_gen_elems, tree_node_for_gen_elems);

        LOG_PRINT (tree_dot_file_gen_elems, "fontsize = 16, fontname = \"times bold\", "
                                            "label = \"");

        MathNodeTypePrint (tree_dot_file_gen_elems, tree_node_for_gen_elems);

        LOG_PRINT (tree_dot_file_gen_elems, "\"];\n");

        TreeDotFileCreateElements (tree_dot_file_gen_elems, tree_node_for_gen_elems -> left_branch);
        TreeDotFileCreateElements (tree_dot_file_gen_elems, tree_node_for_gen_elems -> right_branch);
    }

    return TREE_STATUS_OK;
}

enum TreeFuncStatus TreeDotFileDrawArrows (FILE *tree_dot_file_draw,
                                           const TreeNode *tree_node_for_draw_arrows) {

    assert (tree_dot_file_draw);

    if (tree_node_for_draw_arrows -> left_branch) {

        LOG_PRINT (tree_dot_file_draw, NODE_START_SYMBOL "%llx -> " NODE_START_SYMBOL "%llx;\n",
                                       (size_t) (tree_node_for_draw_arrows),
                                       (size_t) (tree_node_for_draw_arrows -> left_branch));

        TreeDotFileDrawArrows (tree_dot_file_draw, tree_node_for_draw_arrows -> left_branch);
    }

    if (tree_node_for_draw_arrows -> right_branch) {

        LOG_PRINT (tree_dot_file_draw, NODE_START_SYMBOL "%llx -> " NODE_START_SYMBOL "%llx;\n",
                                       (size_t) (tree_node_for_draw_arrows),
                                       (size_t) (tree_node_for_draw_arrows -> right_branch));

        TreeDotFileDrawArrows (tree_dot_file_draw, tree_node_for_draw_arrows -> right_branch);
    }

    return TREE_STATUS_OK;
}
