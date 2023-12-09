#ifndef LATEX_GENERATOR_H
#define LATEX_GENERATOR_H

enum LatexFuncStatus {

    LATEX_FUNC_STATUS_OK,
    LATEX_FUNC_STATUS_FAIL
};

LatexFuncStatus LatexBegin (FILE* latex_file);

LatexFuncStatus LatexEnd (FILE *latex_file);

LatexFuncStatus LatexFormulaCreate (FILE *latex_file, Tree *math_tree);

LatexFuncStatus LatexFormulaBegin (FILE *latex_file);

LatexFuncStatus LatexFormulaEnd (FILE *latex_file);

LatexFuncStatus LatexFormulaMainBodyCreate (FILE *latex_file, Tree *math_tree);

LatexFuncStatus LatexFormulaNodePrint (FILE *latex_file, TreeNode *math_tree_node);

#endif
