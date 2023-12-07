#include <assert.h>
#include <string.h>

#include "tree/tree_func.h"
#include "tree/tree_log.h"

#include "differentiator_func.h"
#include "differentiator_commands.h"

Tree *MathTreeCopy (const Tree *math_tree_for_copy, Tree *copy_of_math_tree) {

    assert (math_tree_for_copy);
    assert (copy_of_math_tree);

    MATH_TREE_VERIFY_PTR_FUNC (math_tree_for_copy);

    memset (copy_of_math_tree, 0, sizeof (Tree));

    TreeCtor (copy_of_math_tree);

    (copy_of_math_tree -> root) = MathTreeNodeCopy (math_tree_for_copy -> root);

    return copy_of_math_tree;
}

TreeNode *MathTreeNodeCopy (const TreeNode *math_tree_node_for_copy) {

    if (!math_tree_node_for_copy)
        return NULL;

    TreeNode *copy_of_math_tree_node = (TreeNode *) calloc (1, sizeof (TreeNode));
    assert (copy_of_math_tree_node);

    memcpy (copy_of_math_tree_node, math_tree_node_for_copy, sizeof (TreeNode));

    //MathTreeNodeDataCopy (copy_of_math_tree_node, math_tree_node_for_copy);

    (copy_of_math_tree_node -> left_branch)  = MathTreeNodeCopy (math_tree_node_for_copy -> left_branch);

    (copy_of_math_tree_node -> right_branch) = MathTreeNodeCopy (math_tree_node_for_copy -> right_branch);

    return copy_of_math_tree_node;
}

TreeNode *CreateMathTreeNode (const MathNodeType type_of_node, const int node_value,
                              TreeNode *const ptr_left_branch,
                              TreeNode *const ptr_right_branch) {

    TreeNode *math_tree_node = CreateTreeNode ();
    assert (math_tree_node);

    math_tree_node -> data = (MathNode *) calloc (1, sizeof (MathNode));
    assert (math_tree_node -> data);
fprintf (stderr, "before if\n");
    if ((type_of_node != NUMBER && type_of_node != VARIABLE) &&
        IsOperatorUnaryOrBinary ((MathNodeOperator) node_value) != type_of_node)

        return NULL;
fprintf (stderr, "isdataset\n");
    math_tree_node -> data -> nodeType = type_of_node;
    (math_tree_node -> data -> nodeValue).mathNodeValue = node_value;

    math_tree_node -> left_branch  = ptr_left_branch;
    math_tree_node -> right_branch = ptr_right_branch;

    return math_tree_node;
}

MathNodeType IsOperatorUnaryOrBinary (const MathNodeOperator node_operator_to_check) {

    switch (node_operator_to_check) {

        case OPERATOR_ADD:
        case OPERATOR_SUB:
        case OPERATOR_DIV:
        case OPERATOR_MUL:
        case OPERATOR_POW:
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

        default:
            LOG_PRINT_TREE_ERROR ("OPERATOR TO TAKE DERIVATIVE WASN'T FOUND\n");
            return NULL;
    }

    assert ("UNKNOWN ERROR WHILE TAKING DERIVATIVE\n" && 0);
    return NULL;
}

unsigned int MathTreeVerify (const Tree *math_expression_tree,
                             const char* name_parent_func) {

    unsigned int errors_math_expression_tree = TreeVerify (math_expression_tree, name_parent_func);

    errors_math_expression_tree = MathTreeNodeVerify (math_expression_tree -> root);

    return errors_math_expression_tree;
}

unsigned int MathTreeNodeVerify (const TreeNode *math_expression_tree_node) {

    unsigned int errors_math_tree_node = TreeNodeVerify (math_expression_tree_node);

    if (errors_math_tree_node != 0)
        return errors_math_tree_node;

    errors_math_tree_node = MathTreeNodeChecker (math_expression_tree_node);

    return errors_math_tree_node;
}

unsigned int MathTreeNodeChecker (const TreeNode *math_expression_node) {

    if (!math_expression_node)
        return 0;

    unsigned int errors_in_node_and_subtree = MathNodeTypeCheckError (math_expression_node);

    if (errors_in_node_and_subtree)
        return errors_in_node_and_subtree;

    errors_in_node_and_subtree |= NodeBinaryOperatorCheckErrors (math_expression_node) |
                                  NodeUnaryOperatorCheckErrors (math_expression_node)  |
                                  NodeVariableCheckErrors (math_expression_node)       |
                                  NodeNumberCheckErrors (math_expression_node);

    errors_in_node_and_subtree |= MathTreeNodeChecker (math_expression_node -> left_branch);
    errors_in_node_and_subtree |= MathTreeNodeChecker (math_expression_node -> right_branch);

    return errors_in_node_and_subtree;
}

unsigned int MathNodeTypeCheckError (const TreeNode *math_expression_node) {

    assert (math_expression_node);

    const MathNodeOperator node_operator = (math_expression_node -> data -> nodeValue).mathOperator;
    const MathNodeType current_node_type = (math_expression_node -> data -> nodeType);

    unsigned int is_node_type_error = ((current_node_type != NUMBER   &&
                                      current_node_type != VARIABLE) &&
                                      IsOperatorUnaryOrBinary (node_operator) != current_node_type);

    if (is_node_type_error)
        TREE_ERROR_SET_AND_PRINT (is_node_type_error, MATH_TREE_WRONG_NODE_TYPE);

    return is_node_type_error;
}

unsigned int NodeBinaryOperatorCheckErrors (const TreeNode *math_expression_node) {

    assert (math_expression_node);

    unsigned int is_binary_operator_error = 0;

    is_binary_operator_error = (math_expression_node -> data -> nodeType == BINARY_OPERATOR &&
                               (!(math_expression_node -> left_branch)                      ||
                               !(math_expression_node -> right_branch)));

    if (is_binary_operator_error)
        TREE_ERROR_SET_AND_PRINT (is_binary_operator_error, MATH_TREE_BINARY_OP_WRONG_BRANCH);

    return is_binary_operator_error;
}

unsigned int NodeUnaryOperatorCheckErrors (const TreeNode *math_expression_node) {

    assert (math_expression_node);

    int is_unary_operator_error = 0;

    is_unary_operator_error = (math_expression_node -> data -> nodeType == UNARY_OPERATOR &&
                              (((bool) (math_expression_node -> left_branch))             ==
                              (bool) (math_expression_node -> right_branch)));

    if (is_unary_operator_error)
        TREE_ERROR_SET_AND_PRINT (is_unary_operator_error, MATH_TREE_UNARY_OP_WRONG_BRANCHES);

    return is_unary_operator_error;
}

unsigned int NodeVariableCheckErrors (const TreeNode *math_expression_node) {

    assert (math_expression_node);

    unsigned int is_variable_error = (math_expression_node -> data -> nodeType == VARIABLE &&
                                     (((math_expression_node -> left_branch))              ||
                                     (math_expression_node -> right_branch)));

    if (is_variable_error)
        TREE_ERROR_SET_AND_PRINT (is_variable_error, MATH_TREE_VARIABLE_HAVE_BRANCHES);

    return is_variable_error;
}

unsigned int NodeNumberCheckErrors (const TreeNode *math_expression_node) {

    assert (math_expression_node);

    unsigned int is_number_error (math_expression_node -> data -> nodeType == NUMBER &&
                                 (((math_expression_node -> left_branch))            ||
                                 (math_expression_node -> right_branch)));

    if (is_number_error)
        TREE_ERROR_SET_AND_PRINT (is_number_error, MATH_TREE_NUMBER_HAVE_BRANCH);

    return is_number_error;
}
