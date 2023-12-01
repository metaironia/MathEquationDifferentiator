#include "differentiator_func.h"

#include "tree/tree_func.h"
#include "tree/tree_log.h"

int main (const int argc, const char *argv[]) {

    Tree math_equation = {};
    TreeCtor (&math_equation);

    CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_ADD, CreateMathTreeNode (NUMBER, 5, NULL, NULL),
                        CreateMathTreeNode (NUMBER, 10, NULL, NULL));
fprintf (stderr, "lol");
    TreeGraphDump (&math_equation);
fprintf (stderr, "lol1");
    //if (TreeMathEquationRead (&math_equation, argc, argv) == MATH_EQUATION_ERROR)   //this func non exist
    //    return -1;



    return 0;
}


