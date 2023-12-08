#ifndef DIFFERENTIATOR_FUNC_H
#define DIFFERENTIATOR_FUNC_H


#include "tree/tree_func.h"
#include "tree/math_tree/math_tree_node_data.h"

#define NAME_OF_VAR(x)          #x

Tree *FindDerivative (const Tree *math_tree_for_derivative);

DifferentiatorFuncStatus DerivativeTreeCtor (const Tree *math_tree_for_take_derivative,
                                             Tree *derivative_tree_to_create);

TreeNode *FindNodeDerivative (const TreeNode *math_expression_tree_node);


#endif
