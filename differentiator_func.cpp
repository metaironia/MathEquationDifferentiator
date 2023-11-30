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

MathNodeType IsOperatorUnaryOrBinary (const MathNodeType type_of_node_to_check,
                                      const MathNodeOperator node_operator_to_check) {

    switch (type_of_node_check) {

        case (OPERATOR_ADD):
        case (OPERATOR_SUB):
        case (OPERATOR_DIV):
        case (OPERATOR_MUL):
            return BINARY_OPERATOR;
            break;

        case (OPERATOR_SIN):
        case (OPERATOR_COS):
        case (OPERATOR_LN):
            return UNARY_OPERATOR;
            break;

        default:
            return NODE_TYPE_ERROR;
    }

    return NODE_TYPE_ERROR;
}

TreeNode *FindNodeDerivative (const TreeNode *math_expression_tree_node) {

    MATH_TREE_VERIFY (math_expression_tree);

    if (!math_expression_tree_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree_node -> data -> nodeType == NUMBER)
        return CreateMathTreeNode (NUMBER, 0, NULL, NULL);

    if (math_expression_tree_node -> data -> nodeType == V)

}

unsigned int MathTreeVerify (const Tree *math_expression_tree) {

    unsigned int errors_math_expression_tree = TreeVerify (math_expression_tree);

    if (NodeNumberFindAndCheck (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_NUMBER_WRONG_NO_BRANCH);

    if (NodeBinaryOperatorFindAndCheck (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_BINARY_OP_WRONG_BRANCH);

    if (NodeUnaryOperatorFindAndCheck (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_UNARY_OP_WRONG_BRANCHES);

    if (NodeVariableFindAndCheck (math_expression_tree -> root))
        TREE_ERROR_SET_AND_PRINT (errors_math_expression_tree, MATH_TREE_VARIABLE_WRONG_BRANCHES);

    return errors_math_expression_tree;
}

DifferentiatorFuncStatus NodeBinaryOperatorFindAndCheck (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree -> data -> mathNodeType == BINARY_OPERATOR &&
       (!(math_expression_tree -> left_branch) || !(math_expression_tree -> right_branch)))

       return DIFF_FUNC_STATUS_FAIL;

    if (NodeBinaryOperatorFindAndCheck (math_expression_node -> left_branch)  == DIFF_FUNC_STATUS_FAIL ||
        NodeBinaryOperatorFindAndCheck (math_expression_node -> right_branch) == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}

DifferentiatorFuncStatus NodeUnaryOperatorFindAndCheck (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree -> mathNodeType == UNARY_OPERATOR &&
        ((bool) (math_expression_tree -> left_branch)) == (bool) (math_expression_tree -> right_branch)))

       return DIFF_FUNC_STATUS_FAIL;

    if (NodeUnaryOperatorFindAndCheck (math_expression_node -> left_branch)  == DIFF_FUNC_STATUS_FAIL ||
        NodeUnaryOperatorFindAndCheck (math_expression_node -> right_branch) == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}

DifferentiatorFuncStatus NodeVariableFindAndCheck (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree -> mathNodeType == VARIABLE &&
        (((math_expression_tree -> left_branch)) || (math_expression_tree -> right_branch)))

       return DIFF_FUNC_STATUS_FAIL;

    if (NodeVariableFindAndCheck (math_expression_node -> left_branch)  == DIFF_FUNC_STATUS_FAIL ||
        NodeVariableFindAndCheck (math_expression_node -> right_branch) == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}

DifferentiatorFuncStatus NodeNumberFindAndCheck (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return DIFF_FUNC_STATUS_OK;

    if (math_expression_tree -> mathNodeType == NUMBER &&
        (((math_expression_tree -> left_branch)) || (math_expression_tree -> right_branch)))

       return DIFF_FUNC_STATUS_FAIL;

    if (NodeNumberFindAndCheck (math_expression_node -> left_branch)  == DIFF_FUNC_STATUS_FAIL ||
        NodeNumberFindAndCheck (math_expression_node -> right_branch) == DIFF_FUNC_STATUS_FAIL)

        return DIFF_FUNC_STATUS_FAIL;

    return DIFF_FUNC_STATUS_OK;
}
