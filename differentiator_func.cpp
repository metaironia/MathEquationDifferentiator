#include <assert.h>
#include <string.h>

#include "tree/tree_func.h"
#include "tree/tree_log.h"

#include "tree/math_tree/math_tree_func.h"

#include "differentiator_func.h"
#include "differentiator_commands.h"

Tree *FindDerivative (const Tree *math_tree_for_take_derivative) {

    assert (math_tree_for_take_derivative);

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

    MathTreeNodeVerify (math_expression_tree_node);

    if (math_expression_tree_node -> data -> nodeType == NUMBER)
        return CreateMathTreeNode (NUMBER, 0, NULL, NULL);

    if (math_expression_tree_node -> data -> nodeType == VARIABLE)
        return CreateMathTreeNode (NUMBER, 1, NULL, NULL);

    switch ((math_expression_tree_node -> data -> nodeValue).mathOperator) {

        case OPERATOR_ADD:
            return ADD_ (dL, dR);
            break;

        case OPERATOR_SUB:
            return SUB_ (dL, dR);
            break;

        case OPERATOR_MUL:
            return ADD_ (MUL_ (dL, cR), MUL_ (cL, dR));
            break;

        case OPERATOR_DIV:
            return DIV_ (SUB_ (MUL_ (dL, cR), MUL_ (cL, dR)), POW_ (cR, NUM_ (2)));

        case OPERATOR_POW:
            return MUL_ (cCUR, ADD_ (MUL_ (dR, LN_ (cL)), MUL_ (cR, LN_ (dL))));
            break;

        case OPERATOR_LN:
            return MUL_ (DIV_ (NUM_ (1), cL), dL);
            break;

        default:
            LOG_PRINT_TREE_ERROR ("OPERATOR TO TAKE DERIVATIVE WASN'T FOUND\n");
            return NULL;
    }

    assert ("UNKNOWN ERROR WHILE TAKING DERIVATIVE\n" && 0);

    return NULL;
}

