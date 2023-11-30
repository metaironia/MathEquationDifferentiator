#include <assert.h>

#include "../stack/my_stack_func.h"

#include "tree_func.h"
#include "tree_log.h"

TreeNode *CreateMathTreeNode (const MathNodeType type_of_node, const int node_value,
                              const TreeNode *const ptr_left_branch,
                              const TreeNode *const ptr_right_branch) {

    TreeNode *math_tree_node = CreateTreeNode ();
    assert (math_tree_node);

    math_tree_node -> data = (MathNode *) calloc (1, sizeof (MathNode));
    assert (math_tree_node -> data);

    if ((type_of_node != NUMBER && type_of_node != VARIABLE) &&
        IsOperatorUnaryOrBinary (node_operator) != type_of_node)

        return NULL;

    math_tree_node -> data -> nodeType = type_of_node;
    math_tree_node -> data -> nodeValue = node_value;

    return math_tree_node;
}

MathNodeType IsOperatorUnaryOrBinary (const MathNodeOperator node_operator_to_check) {

    switch (node_operator_to_check) {

        case OPERATOR_ADD:
        case OPERATOR_SUB:
        case OPERATOR_DIV:
        case OPERATOR_MUL:
        case OPERATOR_POWER:
            return BINARY_OPERATOR;
            break;

        case OPERATOR_SIN:
        case OPERATOR_COS:
        case OPERATOR_LN:
            return UNARY_OPERATOR;
            break;

        default:
            return NODE_TYPE_ERROR;
    }

    return NODE_TYPE_ERROR;
}

DifferentiatorFuncStatus DerivativeTreeCtor (Tree *derivative_tree_to_create) {

    assert (derivative_tree_to_create);

    TreeCtor (derivative_tree_to_create);

    (derivative_tree_to_create -> root) = FindNodeDerivative (derivative_tree_to_create -> root);

    MATH_TREE_VERIFY (derivative_tree_to_create);

    return DIFF_FUNC_STATUS_OK;
}

TreeNode *FindNodeDerivative (const TreeNode *math_expression_tree_node) {

    if (!math_expression_tree_node)
        return NULL;

    if (math_expression_tree_node -> data -> nodeType == NUMBER)
        return CreateMathTreeNode (NUMBER, 0, NULL, NULL);

    if (math_expression_tree_node -> data -> nodeType == VARIABLE)
        return CreateMathTreeNode (NUMBER, 1, NULL, NULL);

    switch (math_expression_tree_node -> data -> nodeType) {

        case OPERATOR_ADD:
            return ADD_ (dL, dR);
            break;

        case OPERATOR_SUB:
            return SUB_ (dL, dR);
            break;

        case OPERATOR_MUL:
            return ADD_ (MUL_ (dL, cR), MUL_ (cL, dR))
            break;

        case OPERATOR_DIV:
            return DIV_ (SUB_ (MUL_ (dL, cR), MUL_ (cL, dR)), POW_ (cR, 2));

        case OPERATOR_POW:
            return MUL_ (cCUR, ADD_ (MUL_ (dR, LN_ (cL)), MUL_ (cR, LN_ (dL))))
            break;

        default:
            LogPrintTreeError ("OPERATOR TO TAKE DERIVATIVE WASN'T FOUND\n");
            return NULL;
    }

    assert ("UNKNOWN ERROR WHILE TAKING DERIVATIVE\n" && 0);
    return NULL;
}

unsigned int MathTreeVerify (const Tree *math_expression_tree) {

    unsigned int errors_math_expression_tree = TreeVerify (math_expression_tree);

    if (NodeNumberFindAndCheckBranches (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_NUMBER_WRONG_NO_BRANCH);

    if (NodeBinaryOperatorFindAndCheckBranches (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_BINARY_OP_WRONG_BRANCH);

    if (NodeUnaryOperatorFindAndCheckBranches (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_UNARY_OP_WRONG_BRANCHES);

    if (NodeVariableFindAndCheckBranches (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_VARIABLE_WRONG_BRANCHES);

    if (NodeFindTypeError (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_WRONG_NODE_TYPE);

    return errors_math_expression_tree;
}

DifferentiatorFuncStatus NodeFindTypeError (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if ((type_of_node != NUMBER && type_of_node != VARIABLE) &&
        IsOperatorUnaryOrBinary (node_operator) != type_of_node)

       return DIFF_FUNC_STATUS_FAIL;

    if (NodeFindTypeError (math_expression_node -> left_branch)  == DIFF_FUNC_STATUS_FAIL ||
        NodeFindTypeError (math_expression_node -> right_branch) == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}


DifferentiatorFuncStatus NodeBinaryOperatorFindAndCheckBranches (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree -> data -> mathNodeType == BINARY_OPERATOR &&
       (!(math_expression_tree -> left_branch) || !(math_expression_tree -> right_branch)))

       return DIFF_FUNC_STATUS_FAIL;

    if (NodeBinaryOperatorFindAndCheckBranches (math_expression_node -> left_branch)
                                                                        == DIFF_FUNC_STATUS_FAIL ||
        NodeBinaryOperatorFindAndCheckBranches (math_expression_node -> right_branch)
                                                                        == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}

DifferentiatorFuncStatus NodeUnaryOperatorFindAndCheckBranches (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree -> mathNodeType == UNARY_OPERATOR &&
        ((bool) (math_expression_tree -> left_branch)) == (bool) (math_expression_tree -> right_branch)))

       return DIFF_FUNC_STATUS_FAIL;

        if (NodeUnaryOperatorFindAndCheckBranches (math_expression_node -> left_branch)
                                                                        == DIFF_FUNC_STATUS_FAIL ||
            NodeUnaryOperatorFindAndCheckBranches (math_expression_node -> right_branch)
                                                                        == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}

DifferentiatorFuncStatus NodeVariableFindAndCheckBranches (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree -> mathNodeType == VARIABLE &&
        (((math_expression_tree -> left_branch)) || (math_expression_tree -> right_branch)))

       return DIFF_FUNC_STATUS_FAIL;

    if (NodeVariableFindAndCheckBranches (math_expression_node -> left_branch)  == DIFF_FUNC_STATUS_FAIL ||
        NodeVariableFindAndCheckBranches (math_expression_node -> right_branch) == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}

DifferentiatorFuncStatus NodeNumberFindAndCheckBranches (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree -> mathNodeType == NUMBER &&
        (((math_expression_tree -> left_branch)) || (math_expression_tree -> right_branch)))

       return DIFF_FUNC_STATUS_FAIL;

    if (NodeNumberFindAndCheckBranches (math_expression_node -> left_branch)  == DIFF_FUNC_STATUS_FAIL ||
        NodeNumberFindAndCheckBranches (math_expression_node -> right_branch) == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}
