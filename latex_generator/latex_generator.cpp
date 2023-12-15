#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "../tree/tree_func.h"
#include "../tree/tree_log.h"

#include "../tree/math_tree/math_tree_func.h"
#include "../tree/math_tree/math_tree_node_data.h"

#include "latex_generator.h"
#include "latex_rofls.h"

FILE *latex_file_output = CreateLatexFile (LATEX_FILE_NAME);

FILE *CreateLatexFile (const char *log_file_name) {

    assert (log_file_name);

    srand ((int) time (0));

    FILE *log_file_ptr = fopen (log_file_name, "w");
    assert (log_file_ptr);

    atexit (CloseLogFile);

    return log_file_ptr;
}

void CloseLatexFile (void) {

    if (latex_file_output)
        fclose (latex_file_output);

    latex_file_output = NULL;
}

LatexFuncStatus LatexBegin (FILE* latex_file) {

    assert (latex_file);

    fprintf (latex_file,    "\\documentclass[a4paper,12pt]{article}\n"
                            "\\usepackage{cmap}\n"
                            "\\usepackage{mathtext}\n"
                            "\\usepackage[T2A]{fontenc}\n"
                            "\\usepackage[utf8]{inputenc}\n"
                            "\\usepackage[english,russian]{babel}\n"
                            "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n"
                            "\\usepackage{icomma}\n"

                            "\\DeclareMathOperator{\\sgn}{\\mathop{sgn}}\n"
                            "\\newcommand*{\\hm}[1]{#1\\nobreak\\discretionary{}\n"
                            "{\\hbox{$\\mathsurround=0pt #1$}}{}}\n"

                            "\\usepackage{graphicx}\n"
                            "\\graphicspath{{images/}{images2/}}\n"
                            "\\usepackage{wrapfig}\n"

                            "\\usepackage{array,tabularx,tabulary,booktabs}\n"
                            "\\usepackage{longtable}\n"
                            "\\usepackage{multirow}\n"

                            "\\theoremstyle{plain}\n"
                            "\\newtheorem{theorem}{Теорема}[section]\n"
                            "\\newtheorem{proposition}[theorem]{Утверждение}\n"

                            "\\theoremstyle{definition}\n"
                            "\\newtheorem{corollary}{Следствие}[theorem]\n"
                            "\\newtheorem{problem}{Задача}[section]\n"

                            "\\theoremstyle{remark}\n"
                            "\\newtheorem*{nonum}{Решение}\n"

                            "\\usepackage{etoolbox}\n"

                            "\\usepackage{extsizes}\n"
                            "\\usepackage{geometry}\n"
                            "	\\geometry{top=25mm}\n"
                            "	\\geometry{bottom=35mm}\n"
                            "	\\geometry{left=20mm}\n"
                            "	\\geometry{right=20mm}\n"

                            "\\usepackage{setspace}\n"

                            "\\usepackage{lastpage}\n"

                            "\\usepackage{soul}\n"

                            "\\usepackage{hyperref}\n"
                            "\\usepackage[usenames,dvipsnames,svgnames,table,rgb]{xcolor}\n"
                            "\\hypersetup{\n"
                            "    unicode=true,\n"
                            "    pdftitle={Заголовок},\n"
                            "    pdfauthor={Автор},\n"
                            "    pdfsubject={Тема},\n"
                            "    pdfcreator={Создатель},\n"
                            "    pdfproducer={Производитель},\n"
                            "    pdfkeywords={keyword1} {key2} {key3},\n"
                            "    colorlinks=true,\n"
                            "    linkcolor=black,\n"
                            "    citecolor=black,\n"
                            "    filecolor=magenta,\n"
                            "    urlcolor=cyan\n"
                            "}\n"

                            "\\usepackage{csquotes}\n"

                            "\\usepackage{multicol}\n"

                            "\\usepackage{tikz}\n"
                            "\\usetikzlibrary{calc}\n"
                            "\\usepackage{tkz-euclide}\n"
                            "\\usepackage{pgfplots}\n"
                            "\\pgfplotsset{compat=1.18}\n"
                            "\\usetikzlibrary{pgfplots.polar}\n"
                            "\\usepackage{pgfplotstable}\n"

                            "\\author{Кулагин Сергей}\n"
                            "\\title{Главная дерьмина в моей жизни в \\LaTeX}\n"
                            "\\date{\\today}\n"

                            "\\begin{document}\n");

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexEnd (FILE *latex_file) {

    assert (latex_file);

    fprintf (latex_file,    "\\begin{thebibliography}{}\n"
                            "\\bibitem{Arithmetica} Margin of a copy of Arithmetica --- Diophantus of Alexandria, Pierre de Fermat\n"
                            "\\bibitem{Universe} Kak upravlat Vselennoi, ne privlekaya vnimaniya sanitarov --- Artem Bester\n"
                            "\\bibitem{Ruses} History of ancient Ruses - professor Bagirov\n"

                            "\\end{thebibliography}\n"

                            "\\end{document}\n");

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexFormulaCreate (FILE *latex_file, const TreeNode *math_tree_node) {

    assert (latex_file);

    MATH_TREE_NODE_VERIFY (math_tree_node, LATEX);

    LatexFormulaBegin          (latex_file);
    LatexFormulaMainBodyCreate (latex_file, math_tree_node);
    LatexFormulaEnd            (latex_file);

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexFormulaBegin (FILE *latex_file) {

    assert (latex_file);

    fprintf (latex_file, "$$ ");

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexFormulaEnd (FILE *latex_file) {

    assert (latex_file);

    fprintf (latex_file, " $$\n");

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexFormulaMainBodyCreate (FILE *latex_file, const TreeNode *math_tree_node) {

    assert (latex_file);

    MATH_TREE_NODE_VERIFY (math_tree_node, LATEX);

    LatexFormulaNodeDataPrint (latex_file, math_tree_node, OPERATOR_ADD);

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexFormulaNodeDataPrint (FILE *latex_file, const TreeNode *math_tree_node,
                                           const MathNodeOperator parent_node_operator) {

    assert (latex_file);

    if (!math_tree_node)
        return LATEX_FUNC_STATUS_OK;

    MATH_TREE_NODE_VERIFY (math_tree_node, LATEX);

    MathNodeType latex_var_or_num_status = LatexVarOrNumPrint (latex_file, math_tree_node);

    if (latex_var_or_num_status == NUMBER || latex_var_or_num_status == VARIABLE)
        return LATEX_FUNC_STATUS_OK;

    if (latex_var_or_num_status == NODE_TYPE_ERROR)
        return LATEX_FUNC_STATUS_FAIL;

    MathNodeOperator current_node_operator = (math_tree_node -> data -> nodeValue).mathOperator;

    char before_expression[MAX_WORD_LENGTH]  = "";
    char between_expression[MAX_WORD_LENGTH] = "";
    char after_expression[MAX_WORD_LENGTH]   = "";

    LatexSetBeforeExpression (before_expression, current_node_operator, parent_node_operator);

    LatexSetMainExpression   (before_expression,
                              between_expression,
                              after_expression,  current_node_operator);

    LatexSetAfterExpression  (after_expression,  current_node_operator, parent_node_operator);

    LatexExpressionPrint (latex_file, math_tree_node, before_expression,
                                                      between_expression,
                                                      after_expression);

    return LATEX_FUNC_STATUS_OK;
}

MathNodeType LatexVarOrNumPrint (FILE *latex_file, const TreeNode *math_tree_node) {

    assert (latex_file);

    if (MathTreeNodeVerify (math_tree_node) != 0)
        return NODE_TYPE_ERROR;

    MathNodeType current_node_type = math_tree_node -> data -> nodeType;

    switch (current_node_type) {

        case NUMBER:
            fprintf (latex_file, "%.2lg", (math_tree_node -> data -> nodeValue).mathNodeValue);
            return NUMBER;
            break;

        case VARIABLE:
            fprintf (latex_file, "x");
            return VARIABLE;
            break;

        case NODE_TYPE_ERROR:
            fprintf (stderr, "NODE TYPE ERROR");
            break;

        case BINARY_OPERATOR:
        case UNARY_OPERATOR:
            return current_node_type;

        default:
            break;
    }

    return NODE_TYPE_ERROR;
}

LatexFuncStatus LatexSetBeforeExpression (char *before_expression,
                                          const MathNodeOperator current_node_operator,
                                          const MathNodeOperator parent_node_operator) {

    assert (before_expression);

    switch (current_node_operator) {

        case OPERATOR_ADD:
        case OPERATOR_SUB:
            if (parent_node_operator == OPERATOR_MUL) {

                strncpy (before_expression, "(", MAX_WORD_LENGTH);
                break;
            }
        //fallthrough
        case OPERATOR_MUL:
        case OPERATOR_DIV:
            if (parent_node_operator == OPERATOR_POW)
                strncpy (before_expression, "(", MAX_WORD_LENGTH);

            break;

        default:
            break;
    }

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexSetAfterExpression (char *after_expression,
                                         const MathNodeOperator current_node_operator,
                                         const MathNodeOperator parent_node_operator) {

    assert (after_expression);

    switch (current_node_operator) {

        case OPERATOR_ADD:
        case OPERATOR_SUB:
            if (parent_node_operator == OPERATOR_MUL) {

                strncat (after_expression, ")", MAX_WORD_LENGTH);
                break;
            }
        //fallthrough
        case OPERATOR_MUL:
        case OPERATOR_DIV:
            if (parent_node_operator == OPERATOR_POW)
                strncat (after_expression, ")", MAX_WORD_LENGTH);

            break;

        default:
            break;
    }

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexSetMainExpression (char *before_expression,
                                        char *between_expression,
                                        char *after_expression,
                                        const MathNodeOperator current_node_operator) {

    assert (before_expression);
    assert (between_expression);
    assert (after_expression);

    switch (current_node_operator) {

        case OPERATOR_ADD:
            strncpy (between_expression, "+", MAX_WORD_LENGTH);
            break;

        case OPERATOR_SUB:
            strncpy (between_expression, "-", MAX_WORD_LENGTH);
            break;

        case OPERATOR_DIV:
            strncat (before_expression,  "\\frac{", MAX_WORD_LENGTH / 2);
            strncpy (between_expression, "}{",      MAX_WORD_LENGTH);
            strncpy (after_expression,   "}",       MAX_WORD_LENGTH / 2);
            break;

        case OPERATOR_MUL:
            strncpy (between_expression, "\\cdot", MAX_WORD_LENGTH);
            break;

        case OPERATOR_POW:
            strncat (between_expression, "^{", MAX_WORD_LENGTH / 2);
            strncpy (after_expression,   "}",  MAX_WORD_LENGTH / 2);
            break;

        case OPERATOR_LN:
            strncat (before_expression, "\\ln{", MAX_WORD_LENGTH / 2);
            strncpy (after_expression,  "}",     MAX_WORD_LENGTH / 2);
            break;

        default:
            fprintf (stderr, "ERROR WHILST LATEX GENERATION\n");
            return LATEX_FUNC_STATUS_FAIL;
            break;
    }


    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexExpressionPrint (FILE *latex_file,
                                      const TreeNode *math_tree_node,
                                      const char *before_first_expression,
                                      const char *between_expressions,
                                      const char *after_second_expression) {

    assert (latex_file);
    assert (math_tree_node);
    assert (before_first_expression);
    assert (between_expressions);
    assert (after_second_expression);

    MathNodeOperator parent_operator = (math_tree_node -> data -> nodeValue).mathOperator;


    fprintf (latex_file, "%s", before_first_expression);

    LatexFormulaNodeDataPrint (latex_file, math_tree_node -> left_branch, parent_operator);

    fprintf (latex_file, "%s", between_expressions);

    LatexFormulaNodeDataPrint (latex_file, math_tree_node -> right_branch, parent_operator);

    fprintf (latex_file, "%s", after_second_expression);

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexSimplifyQuotationPrint (FILE *latex_file) {

    assert (latex_file);

    unsigned int rand_index = rand () % LATEX_SIMPLIFY_QUOTATION_NUMBER;

    fprintf (latex_file, "%s", LATEX_SIMPLIFY_QUOTATIONS[rand_index]);

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexSeriousQuotationPrint (FILE *latex_file) {

    assert (latex_file);

    unsigned int rand_index = rand () % LATEX_SERIOUS_QUOTATION_NUMBER;

    fprintf (latex_file, "%s", LATEX_SERIOUS_QUOTATIONS[rand_index]);

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexDerivativeQuotationPrint (FILE *latex_file) {

    assert (latex_file);

    unsigned int rand_index = rand () % LATEX_DERIVATIVE_QUOTATION_NUMBER;

    fprintf (latex_file, "%s", LATEX_DERIVATIVE_QUOTATIONS[rand_index]);

    return LATEX_FUNC_STATUS_OK;
}

//LatexFuncStatus LatexPictureBegin (FILE *latex_file) {
//
//    assert (latex_file);
//
//    fprintf (latex_file, "\\begin{tikzpicture}\n"
//                         "\\begin{axis}[\n"
//                         "x=1.7cm,\n"
//                         "y=0.26cm,\n"
//                         "grid=both,\n"
//                         "grid style={line width=.1pt, draw=gray!10},\n"
//                         "major grid style={line width=.2pt,draw=gray!50},\n"
//                         "axis lines=middle,\n"
//                         "axis line style={line width = .7pt},\n"
//                         "minor tick num=5,\n"
//                         "xmin=-3,\n"
//                         "xmax=3.9,\n"
//                         "ymin=-36,\n"
//                         "ymax=48,\n"
//                         "xtick={-3,-2,...,4},\n"
//                         "ytick={-35,-30,...,50},\n"
//                         "x label style={at={(axis cs:(3.8,2.3)},anchor=north},\n"
//                         "xlabel={\large $x$},\n"
//                         "y label style={at={(axis cs:(0.2,48.4)},anchor=north},\n"
//                         "ylabel={\large $y$},\n"
//                         "clip mode=individual,\n"
//                         "legend style={at={(axis cs:(3.86,44)}}\n"
//                         "]\n");
//
//    return LATEX_FUNC_STATUS_OK;
//}
//
//LatexFuncStatus LatexPictureEnd (FILE *latex_file) {
//
//    assert (latex_file);
//
//    fprintf (latex_file, "\\end{axis}\n"
//                         "\\end{tikzpicture}\n"
//                         "\\end{center}\n");
//
//    return LATEX_FUNC_STATUS_OK;
//}

