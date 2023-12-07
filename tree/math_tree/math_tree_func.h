#ifndef MATH_TREE_FUNC_H
#define MATH_TREE_FUNC_H

#include "math_tree_node_data.h"
#include "../tree_func.h"

#define MATH_TREE_VERIFY(math_tree)                                                     \
                                {                                                       \
                                    if (MathTreeVerify (math_tree, __func__) != 0) {    \
                                                                                        \
                                        MathTreeGraphDump (math_tree);                  \
                                                                                        \
                                        return DIFF_FUNC_STATUS_FAIL;                   \
                                    }                                                   \
                                }

#define MATH_TREE_VERIFY_PTR_FUNC(math_tree)                                            \
                                {                                                       \
                                    if (MathTreeVerify (math_tree, __func__) != 0) {    \
                                                                                        \
                                        MathTreeGraphDump (math_tree);                  \
                                                                                        \
                                        return NULL;                                    \
                                    }                                                   \
                                }

#define MATH_TREE_NODE_VERIFY(math_tree_node)                                     \
                                {                                                 \
                                    if (MathTreeNodeVerify (math_tree) != 0) {    \
                                                                                  \
                                        MathTreeGraphDump (math_tree);            \
                                                                                  \
                                        return NULL;                              \
                                    }                                             \
                                }

const int MAX_NUMBER_LENGTH = 30;

MathNodeType IsOperatorUnaryOrBinary (const MathNodeOperator node_operator_to_check);

Tree *MathTreeCopy (const Tree *math_tree_for_copy, Tree *copy_of_math_tree);

TreeNode *MathTreeNodeCopy (const TreeNode *math_tree_node_for_copy);

TreeNode *CreateMathTreeNode (const MathNodeType type_of_node, const int node_value,
                              TreeNode *const ptr_left_branch,
                              TreeNode *const ptr_right_branch);

unsigned int MathTreeNodeVerify (const TreeNode *math_expression_tree_node);

unsigned int MathTreeVerify (const Tree *math_expression_tree,
                             const char* name_parent_func);

unsigned int MathTreeNodeChecker (const TreeNode *math_expression_node);

unsigned int MathNodeTypeCheckError (const TreeNode *math_expression_node);

unsigned int NodeBinaryOperatorCheckErrors (const TreeNode *math_expression_node);

unsigned int NodeUnaryOperatorCheckErrors (const TreeNode *math_expression_node);

unsigned int NodeVariableCheckErrors (const TreeNode *math_expression_node);

unsigned int NodeNumberCheckErrors (const TreeNode *math_expression_node);

const char *NumberToString (const long long number);

const char *MathNodeTypeToString (const TreeNode *math_tree_node);

const char *MathNodeTypeFind (const TreeNode *math_tree_node_for_type_find);

const char *MathNodeNumOrVarToString (const TreeNode *math_tree_node);

const char *MathNodeOperatorToString (const TreeNode *math_tree_node);

#endif
