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

union MathNodeData {

    int mathNodeValue;
    MathNodeOperator mathOperator;
};

enum MathNodeType {

    NUM,
    UNARY_OPERATOR,
    BINARY_OPERATOR
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
