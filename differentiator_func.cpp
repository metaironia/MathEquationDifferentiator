#include <assert.h>
#include <string.h>

#include "latex_generator/latex_generator.h"

#include "tree/tree_func.h"
#include "tree/tree_log.h"

#include "tree/math_tree/math_tree_func.h"

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

TreeNode *FindNodeDerivative (const TreeNode *math_expression_tree_node) {

    if (!math_expression_tree_node)
        return NULL;

    MATH_TREE_NODE_VERIFY_PTR_FUNC (math_expression_tree_node);

    LatexSeriousQuotationPrint (latex_file_output);

    LatexFormulaCreate (latex_file_output, math_expression_tree_node);

    LatexDerivativeQuotationPrint (latex_file_output);

    TreeNode *output_node = NULL;

    if (math_expression_tree_node -> data -> nodeType == NUMBER)
        output_node = NUM_ (0);

    if (math_expression_tree_node -> data -> nodeType == VARIABLE)
        output_node = NUM_ (1);

    if (output_node) {

        LatexFormulaCreate (latex_file_output, output_node);
        return output_node;
    }

    switch ((math_expression_tree_node -> data -> nodeValue).mathOperator) {

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

            if (math_expression_tree_node -> right_branch -> data -> nodeType == NUMBER) {

                output_node = MUL_ (cR, POW_ (cL, SUB_ (cR, NUM_ (1))));
                break;
            }

            if (math_expression_tree_node -> left_branch -> data -> nodeType == NUMBER) {

                output_node = MUL_ (POW_ (cL, cR), MUL_ (LN_ (cL), dR));
                break;
            }

            output_node = MUL_ (cCUR, ADD_ (MUL_ (dR, LN_ (cL)), DIV_ (MUL_ (cR, dL), cL)));
            break;

        case OPERATOR_LN:
            output_node = MUL_ (DIV_ (NUM_ (1), cL), dL);
            break;

        default:
            LOG_PRINT_TREE_ERROR ("OPERATOR TO TAKE DERIVATIVE WASN'T FOUND\n");
            return NULL;
    }

    if (output_node)
        LatexFormulaCreate (latex_file_output, output_node);
    else
        assert ("UNKNOWN ERROR WHILE TAKING DERIVATIVE\n" && 0);

    LatexSimplifyQuotationPrint (latex_file_output);

    while (MathTreeNodeConstantsSimplify (output_node) == TREE_FUNC_STATUS_OK);

    LatexFormulaCreate (latex_file_output, output_node);

    return output_node;
}

