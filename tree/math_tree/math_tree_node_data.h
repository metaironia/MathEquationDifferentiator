#ifndef MATH_TREE_NODE_DATA_H
#define MATH_TREE_NODE_DATA_H


enum MathNodeOperator {

    OPERATOR_ADD = '+',
    OPERATOR_SUB = '-',
    OPERATOR_DIV = '/',
    OPERATOR_MUL = '*',
    OPERATOR_POW = '^',
    OPERATOR_SIN = 's',
    OPERATOR_COS = 'c',
    OPERATOR_LN = 'l'
};

union MathNodeData {

    double mathNodeValue;
    MathNodeOperator mathOperator;
};

enum MathNodeType {

    NUMBER,
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
