#ifndef DIFFERENTIATOR_COMMANDS_H
#define DIFFERENTIATOR_COMMANDS_H

#include "differentiator_func.h"

#define cL                      (MathTreeNodeCopy (math_expression_tree_node -> left_branch))

#define cR                      (MathTreeNodeCopy (math_expression_tree_node -> right_branch))

#define cCUR                    (MathTreeNodeCopy (math_expression_tree_node))

#define dL                      (FindNodeDerivative (math_expression_tree_node -> left_branch))

#define dR                      (FindNodeDerivative (math_expression_tree_node -> right_branch))

#define ADD_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_ADD, __VA_ARGS__))

#define SUB_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_SUB, __VA_ARGS__))

#define MUL_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_MUL, __VA_ARGS__))

#define DIV_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_DIV, __VA_ARGS__))

#define POW_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_POW, __VA_ARGS__))

#define NUM_(...)               (CreateNode (NUMBER, __VA_ARGS__, NULL, NULL))

#endif
