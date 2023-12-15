#ifndef LATEX_GENERATOR_H
#define LATEX_GENERATOR_H

#define LATEX_FILE_NAME  "shit.tex"

#include <stdio.h>

#include "../tree/tree_func.h"

const int MAX_WORD_LENGTH = 64;

enum LatexFuncStatus {

    LATEX_FUNC_STATUS_OK,
    LATEX_FUNC_STATUS_FAIL
};

FILE *CreateLatexFile (const char *log_file_name);

void CloseLatexFile (void);

LatexFuncStatus LatexBegin (FILE* latex_file);

LatexFuncStatus LatexEnd (FILE *latex_file);

LatexFuncStatus LatexFormulaCreate (FILE *latex_file, const TreeNode *math_tree_node);

LatexFuncStatus LatexFormulaBegin (FILE *latex_file);

LatexFuncStatus LatexFormulaEnd (FILE *latex_file);

LatexFuncStatus LatexFormulaMainBodyCreate (FILE *latex_file, const TreeNode *math_tree_node);

LatexFuncStatus LatexFormulaNodeDataPrint (FILE *latex_file, const TreeNode *math_tree_node,
                                           const MathNodeOperator parent_operator);

LatexFuncStatus LatexExpressionPrint (FILE *latex_file,
                                      const TreeNode *math_tree_node,
                                      const char *before_first_expression,
                                      const char *between_expressions,
                                      const char *after_second_expression);

MathNodeType LatexVarOrNumPrint (FILE *latex_file, const TreeNode *math_tree_node);

LatexFuncStatus LatexSetBeforeExpression (char *before_expression,
                                          const MathNodeOperator current_node_operator,
                                          const MathNodeOperator parent_node_operator);

LatexFuncStatus LatexSetMainExpression (char *before_expression,
                                        char *between_expression,
                                        char *after_expression,
                                        const MathNodeOperator current_node_operator);

LatexFuncStatus LatexSetAfterExpression (char *after_expression,
                                         const MathNodeOperator current_node_operator,
                                         const MathNodeOperator parent_node_operator);

LatexFuncStatus LatexSimplifyQuotationPrint (FILE *latex_file);

LatexFuncStatus LatexSeriousQuotationPrint (FILE *latex_file);

LatexFuncStatus LatexDerivativeQuotationPrint (FILE *latex_file);

#endif
