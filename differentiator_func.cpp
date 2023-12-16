#include <assert.h>
#include <string.h>

#include "latex_generator/latex_generator.h"

#include "tree/tree_func.h"
#include "tree/tree_log.h"

#include "tree/math_tree/math_tree_func.h"
#include "tree/math_tree/math_operation.h"

#include "differentiator_func.h"
#include "differentiator_commands.h"

extern FILE *latex_file_output;

Tree *FindDerivative (const Tree *math_tree_for_take_derivative) {

    assert (math_tree_for_take_derivative);
    assert (math_tree_for_take_derivative -> root);

    Tree *derivative_tree = (Tree *) calloc (1, sizeof (Tree));

    DerivativeTreeCtor (math_tree_for_take_derivative, derivative_tree);

    return derivative_tree;
}

DifferentiatorFuncStatus DerivativeTreeCtor (const Tree *math_tree_for_take_derivative,
                                             Tree *derivative_tree_to_create) {

    assert (derivative_tree_to_create);

    TreeCtor (derivative_tree_to_create);

    (derivative_tree_to_create -> root) = FindNodeDerivative (math_tree_for_take_derivative -> root);

    MATH_TREE_VERIFY (derivative_tree_to_create, DIFF);

    return DIFF_FUNC_STATUS_OK;
}

TreeNode *FindNodeDerivative (const TreeNode *current_node) {

    if (!current_node)
        return NULL;

    MATH_TREE_NODE_VERIFY_PTR_FUNC (current_node);

    LatexSeriousQuotationPrint (latex_file_output);

    LatexFormulaCreate (latex_file_output, current_node);

    TreeNode *output_node = NULL;

    if (NODE_TYPE == NUMBER)
        output_node = NUM_ (0);

    else if (NODE_TYPE == VARIABLE)
        output_node = NUM_ (1);

    else
        switch (NODE_OPERATOR) {

            case OPERATOR_ADD:
                output_node = ADD_ (dL, dR);
                break;

            case OPERATOR_SUB:
                output_node = SUB_ (dL, dR);
                break;

            case OPERATOR_MUL:
                output_node = ADD_ (MUL_ (dL, cR), MUL_ (cL, dR));
                break;

            case OPERATOR_DIV:
                output_node = DIV_ (SUB_ (MUL_ (dL, cR), MUL_ (cL, dR)), POW_ (cR, NUM_ (2)));
                break;

            case OPERATOR_POW:

                if (BRANCH_TYPE (right_branch) == NUMBER) {

                    output_node = MUL_ (dL , MUL_ (cR, POW_ (cL, SUB_ (cR, NUM_ (1)))));
                    break;
                }

                if (BRANCH_TYPE (left_branch) == NUMBER) {

                    output_node = MUL_ (POW_ (cL, cR), MUL_ (LN_ (cL), dR));
                    break;
                }

                output_node = MUL_ (cCUR, ADD_ (MUL_ (dR, LN_ (cL)), DIV_ (MUL_ (cR, dL), cL)));
                break;

            case OPERATOR_LN:
                output_node = MUL_ (DIV_ (NUM_ (1), cL), dL);
                break;

            case OPERATOR_SIN:
                output_node = MUL_ (COS_ (cL), dL);
                break;

            case OPERATOR_COS:
                output_node = MUL_ (NUM_ (-1), MUL_ (SIN_ (cL), dL));
                break;

            default:
                LOG_PRINT_TREE_ERROR ("OPERATOR TO TAKE DERIVATIVE WASN'T FOUND\n");
                return NULL;
        }

    if (output_node) {

        LatexDerivativeQuotationPrint (latex_file_output);

        LatexFormulaCreate (latex_file_output, output_node);
    }

    else
        assert ("UNKNOWN ERROR WHILE TAKING DERIVATIVE\n" && 0);

    LatexSimplifyQuotationPrint (latex_file_output);

    while (MathTreeNodeConstantsSimplify (output_node) == TREE_FUNC_STATUS_OK);

    LatexFormulaCreate (latex_file_output, output_node);

    return output_node;
}

DifferentiatorFuncStatus TaylorTreeCreate (Tree *taylor_tree, const double derivative_value,
                                           const size_t derivative_number) {

    assert (taylor_tree);
    assert (taylor_tree -> root);

    const double coefficient = derivative_value / (double) Factorial (derivative_number);

    if (derivative_number == 1)
        taylor_tree -> root = NUM_ (MathTreeCompute (taylor_tree, 0));

    TreeNode *taylor_tree_root_copy = NULL;
    taylor_tree_root_copy = TreeNodeCopy (taylor_tree_root_copy, taylor_tree -> root, sizeof (MathNode));

    TreeNodeClear (taylor_tree -> root);
    TreeAllNodesDestruct (&(taylor_tree -> root -> left_branch));
    TreeAllNodesDestruct (&(taylor_tree -> root -> right_branch));

    taylor_tree -> root = ADD_ (MUL_ (NUM_ (coefficient), POW_ (VAR_, NUM_ ((double) derivative_number))),
                                taylor_tree_root_copy);

    while (MathTreeNodeConstantsSimplify (taylor_tree -> root) == TREE_FUNC_STATUS_OK);

    MathTreeGraphDump (taylor_tree);

    return DIFF_FUNC_STATUS_OK;
}

