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

enum MathNodeOperator {

    OPERATOR_ADD,
    OPERATOR_SUB,
    OPERATOR_DIV,
    OPERATOR_MUL
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
