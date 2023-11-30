#ifndef DIFFERENTIATOR_FUNC_H
#define DEFFERENTIATOR_FUNC_H

#define MATH_TREE_VERIFY(tree)   {                                       \
                                    if (MathTreeVerify (tree) != 0) {    \
                                                                         \
                                        TreeGraphDump (tree);            \
                                                                         \
                                        return DIFF_FUNC_STATUS_FAIL;    \
                                    }                                    \
                                }

#define dL                      (FindNodeDerivative (math_expression_tree_node -> left_branch))

#define dR                      (FindNodeDerivative (math_expression_tree_node -> right_branch))

#define ADD_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_ADD, __VA_ARGS__))

#define SUB_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_SUB, __VA_ARGS__))

#define MUL_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_MUL, __VA_ARGS__))

#define DIV_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_DIV, __VA_ARGS__))

#define POW_(...)               (CreateNode (BINARY_OPERATOR, OPERATOR_POW, __VA_ARGS__))

#define NUM_(...)               (CreateNode (NUMBER, __VA_ARGS__, NULL, NULL))

enum MathNodeOperator {

    OPERATOR_ADD,
    OPERATOR_SUB,
    OPERATOR_DIV,
    OPERATOR_MUL,
    OPERATOR_POWER
};

union MathNodeData {

    int mathNodeValue;
    MathNodeOperator mathOperator;
};

enum MathNodeType {

    NUM,
    VARIABLE,
    UNARY_OPERATOR,
    BINARY_OPERATOR,
    NODE_TYPE_ERROR
};

struct MathNode {

    MathNodeType nodeType;
    MathNodeData nodeValue;
};

enum DifferentiatorFuncStatus {

    DIFF_FUNC_STATUS_OK,
    DIFF_FUNC_STATUS_FAIL
};

#endif
