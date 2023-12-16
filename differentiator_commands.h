#ifndef DIFFERENTIATOR_COMMANDS_H
#define DIFFERENTIATOR_COMMANDS_H

#include "differentiator_func.h"

#define cL         (TreeNodeCopy (NULL, current_node -> left_branch, sizeof (MathNode)))

#define cR         (TreeNodeCopy (NULL, current_node -> right_branch, sizeof (MathNode)))

#define cCUR       (TreeNodeCopy (NULL, current_node, sizeof (MathNode)))

#define dL         (FindNodeDerivative (current_node -> left_branch))

#define dR         (FindNodeDerivative (current_node -> right_branch))

#define ADD_(...)  (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_ADD, __VA_ARGS__))

#define SUB_(...)  (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_SUB, __VA_ARGS__))

#define MUL_(...)  (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_MUL, __VA_ARGS__))

#define DIV_(...)  (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_DIV, __VA_ARGS__))

#define POW_(...)  (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_POW, __VA_ARGS__))

#define SIN_(...)  (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_SIN, __VA_ARGS__, NULL))

#define COS_(...)  (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_COS, __VA_ARGS__, NULL))

#define LN_(...)   (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_LN, __VA_ARGS__, NULL))

#define NUM_(...)  (CreateMathTreeNode (NUMBER, __VA_ARGS__, NULL, NULL))

#define VAR_       (CreateMathTreeNode (VARIABLE, 0, NULL, NULL))

#endif
