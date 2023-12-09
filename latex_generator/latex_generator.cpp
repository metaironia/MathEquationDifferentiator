#include <assert.h>
#include <stdio.h>

#include "../tree/tree_func.h"
#include "../tree/tree_log.h"

#include "../tree/math_tree/math_tree_func.h"
#include "../tree/math_tree/math_tree_node_data.h"

#include "latex_generator.h"


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

LatexFuncStatus LatexFormulaCreate (FILE *latex_file, Tree *math_tree) {

    assert (latex_file);

    MATH_TREE_VERIFY (math_tree, LATEX);

    LatexFormulaBegin          (latex_file);
    LatexFormulaMainBodyCreate (latex_file, math_tree);
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

LatexFuncStatus LatexFormulaMainBodyCreate (FILE *latex_file, Tree *math_tree) {

    assert (latex_file);

    MATH_TREE_VERIFY (math_tree, LATEX);

    LatexFormulaNodePrint (latex_file, math_tree -> root);

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexFormulaNodePrint (FILE *latex_file, TreeNode *math_tree_node) {

    assert (latex_file);

    if (!math_tree_node)
        return LATEX_FUNC_STATUS_OK;

    MATH_TREE_NODE_VERIFY (math_tree_node, LATEX);

    MathNodeType current_node_type = math_tree_node -> data -> nodeType;

    switch (current_node_type) {

        case NUMBER:
            fprintf (latex_file, "%.2lf", (math_tree_node -> data -> nodeValue).mathNodeValue);
            return LATEX_FUNC_STATUS_OK;
            break;

        case VARIABLE:
            fprintf (latex_file, "x");
            return LATEX_FUNC_STATUS_OK;
            break;

        case NODE_TYPE_ERROR:
            fprintf (stderr, "NODE TYPE ERROR");
            return LATEX_FUNC_STATUS_FAIL;
            break;

        default:
            break;
    }

    MathNodeOperator current_node_operator = (math_tree_node -> data -> nodeValue).mathOperator;

    switch (current_node_operator) {

        case OPERATOR_ADD: {

            fprintf (latex_file, "(");

            LatexFormulaNodePrint (latex_file, math_tree_node -> left_branch);

            fprintf (latex_file, "+");

            LatexFormulaNodePrint (latex_file, math_tree_node -> right_branch);

            fprintf (latex_file, ")");

            break;
        }

        case OPERATOR_SUB: {

            fprintf (latex_file, "(");

            LatexFormulaNodePrint (latex_file, math_tree_node -> left_branch);

            fprintf (latex_file, "-");

            LatexFormulaNodePrint (latex_file, math_tree_node -> right_branch);

            fprintf (latex_file, ")");

            break;
        }

        case OPERATOR_DIV: {

            fprintf (latex_file, "\\frac{");

            LatexFormulaNodePrint (latex_file, math_tree_node -> left_branch);

            fprintf (latex_file, "}{");

            LatexFormulaNodePrint (latex_file, math_tree_node -> right_branch);

            fprintf (latex_file, "}");

            break;
        }

        case OPERATOR_MUL: {

            fprintf (latex_file, "(");

            LatexFormulaNodePrint (latex_file, math_tree_node -> left_branch);

            fprintf (latex_file, "*");

            LatexFormulaNodePrint (latex_file, math_tree_node -> right_branch);

            fprintf (latex_file, ")");

            break;
        }

        case OPERATOR_POW: {

            fprintf (latex_file, "(");

            LatexFormulaNodePrint (latex_file, math_tree_node -> left_branch);

            fprintf (latex_file, "^{");

            LatexFormulaNodePrint (latex_file, math_tree_node -> right_branch);

            fprintf (latex_file, "})");

            break;
        }

        case OPERATOR_LN: {

            fprintf (latex_file, "\\ln{");

            LatexFormulaNodePrint (latex_file, math_tree_node -> left_branch);

            fprintf (latex_file, "}");

            break;
        }


        default:

            fprintf (latex_file, "ERROR");
            return LATEX_FUNC_STATUS_FAIL;
            break;
    }

    return LATEX_FUNC_STATUS_OK;
}


