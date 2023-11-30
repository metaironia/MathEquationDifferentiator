#include <assert.h>

#include "../stack/my_stack_func.h"

#include "tree_func.h"
#include "tree_log.h"


//DifferentiatorFuncStatus Differentiate (const Tree *math_expression_tree) {
//
//    MATH_TREE_VERIFY (math_expression_tree);
//
//
//
//}

unsigned int MathTreeVerify (const Tree *math_expression_tree) {

    unsigned int errors_math_expression_tree = TreeVerify (math_expression_tree);

    if (math_expression_tree -> mathNodeType == BINARY_OPERATOR &&
        (!(math_expression_tree -> left_branch) || !(math_expression_tree -> right_branch))) {

        errors_in_tree |= MATH_TREE_BINARY_OP_NO_BRANCH;
        LogPrintTreeError ("MATH_TREE_BINARY_NO_BRANCH");
    }

    if (math_expression_tree -> mathNodeType == UNARY_OPERATOR &&
        ((bool) (math_expression_tree -> left_branch)) == (bool) (math_expression_tree -> right_branch))) {

        errors_in_tree |= MATH_TREE_UNARY_OP_WRONG_BRANCHES;
        LogPrintTreeError ("MATH_TREE_UNARY_OP_WRONG_BRANCHES");
    }

    return errors_math_expression_tree;
}
