#include "differentiator_func.h"

#include "tree/tree_func.h"
#include "tree/tree_log.h"

#include "tree/math_tree/math_tree_node_data.h"
#include "tree/math_tree/math_tree_func.h"

#include "latex_generator/latex_generator.h"

#include "differentiator_commands.h"

extern FILE *latex_file_output;

int main (const int argc, const char *argv[]) {

    Tree math_equation = {};
    TreeCtor (&math_equation);

    FILE* test = fopen ("test.txt", "r");

    MathTreeNodeRead (test, &(math_equation.root));

    MathTreeGraphDump (&math_equation);

    while (MathTreeNodeConstantsSimplify (math_equation.root) == TREE_FUNC_STATUS_OK); //TODO put this to input

    MathTreeGraphDump (&math_equation);

    LatexBegin (latex_file_output);

    Tree *derivative_tree = &math_equation;

    Tree taylor_tree = {};
    TreeCtor (&taylor_tree);
    taylor_tree.root = math_equation.root;

    for (size_t current_derivative = 1; current_derivative <= MAX_DERIVATIVE; current_derivative++) {

        LatexSectionPrint (latex_file_output, current_derivative);

        derivative_tree = FindDerivative (derivative_tree);

        LatexFormulaOriginalPrint (latex_file_output, math_equation.root);

        LatexDerivativePlotDraw (latex_file_output, derivative_tree, current_derivative);

        TaylorTreeCreate (&taylor_tree, MathTreeCompute (derivative_tree, 0), current_derivative);

        LatexFormulaAndTaylorPlotDraw (latex_file_output, &math_equation, &taylor_tree,
                                       current_derivative);

        LatexFormulaAndTaylorDifferencePlotDraw (latex_file_output, &math_equation, &taylor_tree);

    }

    //if (TreeMathEquationRead (&math_equation, argc, argv) == MATH_EQUATION_ERROR)   //this func non exist
    //    return -1;

    LatexEnd (latex_file_output);

    MathTreeGraphDump (&math_equation);
    MathTreeGraphDump (derivative_tree);

    while (MathTreeNodeConstantsSimplify (derivative_tree -> root) == TREE_FUNC_STATUS_OK);

    MathTreeGraphDump (derivative_tree);

    return 0;
}


