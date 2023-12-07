#ifndef DIFFERENTIATOR_FUNC_H
#define DIFFERENTIATOR_FUNC_H


#include "tree/tree_func.h"
#include "math_tree_node_data.h"

#define NAME_OF_VAR(x)          #x

DifferentiatorFuncStatus DerivativeTreeCtor (Tree *derivative_tree_to_create);

TreeNode *FindNodeDerivative (const TreeNode *math_expression_tree_node);


#endif
