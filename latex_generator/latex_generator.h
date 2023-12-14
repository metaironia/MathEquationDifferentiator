#ifndef LATEX_GENERATOR_H
#define LATEX_GENERATOR_H

const int MAX_WORD_LENGTH = 64;

enum LatexFuncStatus {

    LATEX_FUNC_STATUS_OK,
    LATEX_FUNC_STATUS_FAIL
};

LatexFuncStatus LatexBegin (FILE* latex_file);

LatexFuncStatus LatexEnd (FILE *latex_file);

LatexFuncStatus LatexFormulaCreate (FILE *latex_file, const Tree *math_tree);

LatexFuncStatus LatexFormulaBegin (FILE *latex_file);

LatexFuncStatus LatexFormulaEnd (FILE *latex_file);

LatexFuncStatus LatexFormulaMainBodyCreate (FILE *latex_file, const Tree *math_tree);

LatexFuncStatus LatexFormulaNodeDataPrint (FILE *latex_file, const TreeNode *math_tree_node,
                                           const MathNodeOperator parent_operator);

LatexFuncStatus LatexExpressionPrint (FILE *latex_file,
                                      const TreeNode *math_tree_node,
                                      const char *before_first_expression,
                                      const char *between_expressions,
                                      const char *after_second_expression);

#endif
