#ifndef DIFFERENTIATOR_FUNC_H
#define DIFFERENTIATOR_FUNC_H


#include "tree/tree_func.h"
#include "math_tree_node_data.h"

#define NAME_OF_VAR(x)          #x

#define MATH_TREE_VERIFY(math_tree)                                           \
                                {                                             \
                                    if (MathTreeVerify (math_tree) != 0) {    \
                                                                              \
                                        TreeGraphDump (math_tree);            \
                                                                              \
                                        return DIFF_FUNC_STATUS_FAIL;         \
                                    }                                         \
                                }

#define MATH_TREE_VERIFY_PTR_FUNC(math_tree)                                  \
                                {                                             \
                                    if (MathTreeVerify (math_tree) != 0) {    \
                                                                              \
                                        TreeGraphDump (math_tree);            \
                                                                              \
                                        return NULL;                          \
                                    }                                         \
                                }

#define MATH_TREE_NODE_VERIFY(math_tree_node)

const char *MathNodeTypeFind (const TreeNode *math_tree_node_for_type_find);

Tree *MathTreeCopy (const Tree *math_tree_for_copy, Tree *copy_of_math_tree);

TreeNode *MathTreeNodeCopy (const TreeNode *math_tree_node_for_copy);

TreeNode *CreateMathTreeNode (const MathNodeType type_of_node, const int node_value,
                              TreeNode *const ptr_left_branch,
                              TreeNode *const ptr_right_branch);

MathNodeType IsOperatorUnaryOrBinary (const MathNodeOperator node_operator_to_check);

DifferentiatorFuncStatus DerivativeTreeCtor (Tree *derivative_tree_to_create);

TreeNode *FindNodeDerivative (const TreeNode *math_expression_tree_node);

unsigned int MathTreeNodeVerify (const TreeNode *math_expression_tree_node);

unsigned int MathTreeVerify (const Tree *math_expression_tree);

DifferentiatorFuncStatus NodeFindTypeError (const TreeNode *math_expression_node);

DifferentiatorFuncStatus NodeBinaryOperatorFindAndCheckBranches (const TreeNode *math_expression_node);

DifferentiatorFuncStatus NodeUnaryOperatorFindAndCheckBranches (const TreeNode *math_expression_node);

DifferentiatorFuncStatus NodeVariableFindAndCheckBranches (const TreeNode *math_expression_node);

DifferentiatorFuncStatus NodeNumberFindAndCheckBranches (const TreeNode *math_expression_node);

#endif
