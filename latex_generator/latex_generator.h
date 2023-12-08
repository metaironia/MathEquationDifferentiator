#ifndef LATEX_GENERATOR_H
#define LATEX_GENERATOR_H

enum LatexFuncStatus {

    LATEX_FUNC_STATUS_OK,
    LATEX_FUNC_STATUS_FAIL
};

LatexFuncStatus LatexBegin (FILE* latex_file);

LatexFuncStatus LatexEnd (FILE *latex_file);

#endif
